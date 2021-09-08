/*
	DCLP
	Double-Checked Locking Pattern

	To reduce the number of processes waiting on the mutex we
	try using the DCLP but it has its own issues.
*/

// logger.hpp

// #pragma once

#include <cstdio>
#include <string>
#include <mutex>

// Prefer returning reference instead of pointer
// Pointers can be NULL thus have to be checked everytime before using them
// whereas References can never be NULL.
class Logger {
public:
	void WriteLog(const char *pMessage);
	void SetTag(const char *pTag);
	static Logger& Instance();
private:
	static std::mutex m_Mtx;
	Logger(); // to prevent instance creation.
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	~Logger(); // To prevent the users to call delete.

	static Logger *m_pInstance;
	//c++17
	// inline static Logger *m_pInstance{};
	// This will initialize the static variable in the class itself (from c++17)

	FILE *m_pStream;
	std::string m_Tag;
};

// logger.cpp

#include <iostream>
#include <memory>

// initialize the static member variable
Logger* Logger::m_pInstance;

// initialize the static mutex member variable
std::mutex Logger::m_Mtx;

Logger::Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	m_pStream = fopen("7_2.log", "w");
	// When the main returns the run-time will automatically invoke this lambda.
	// and delete will get executed.
	// This will delete the instance and invoke the destructor of Logger
	atexit([](){
		delete m_pInstance;
	});
}

Logger::~Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	fclose(m_pStream);
}

/*
// DCLP
But DCLP may not always work.
As we are modifying the instance variable inside a critial section.
What will happen if one thread modifies the instance and the other thread reads from it.

The operations on the instance pointer are not atomic. So it may happen while one thread is
modifying the m_pInstance variable the other thread may read from it (line-76 outside the critical section)
Thus the thread may read from it while the other thread has not written to it. Thus it may read
an invalid value. And invalid value is not null, thus an invalid value will be returned to the caller.
And when a method is called on the instance that has an invalid value, the application
may crash.

Logger& Logger::Instance(){
	if (m_pInstance == nullptr) {
		m_Mtx.lock();
		if (m_pInstance == nullptr) {
			m_pInstance = new Logger;
		}
		m_Mtx.unlock();
	}	
	return *m_pInstance;
}
*/

// Expanded version to understand the issue.
/*
	m_pInstance = new Logger;
	This involves 3 instructions 1. allocate memory
								 2. initialize memory
								 3. assign the memory address to the pointer.
	Thus above is equivalent to :
	void *p = operator new (sizeof(Logger));
	new(p)Logger{};
	m_pInstance = static_cast<Logger*>(p);

	If the instructions are exactly in this order there won't be any issue.
	But compiler is allowed to generate instructions in any order as long as it doesn't have
	any side-effects. In a single-threaded application this can go unnoticed. But in case of
	multiple threads and multiple CPUs there are 2 things to consider.
	1. the compiler will re-order the instructions.
	2. At runtime, the CPU may reorder the reads and writes to a memory location.
	And if this reordering is not considered by the programmer, then the application
	will have UB at runtime.
*/
Logger& Logger::Instance(){
	if (m_pInstance == nullptr) {
		m_Mtx.lock();
		if (m_pInstance == nullptr) {
			// m_pInstance = new Logger;
			// Suppose the instructions are reordered as below. This is correct for a single-thread.
			// But in multi-threaded application it can cause problem.
			void *p = operator new (sizeof(Logger));
			m_pInstance = static_cast<Logger*>(p); // when a thread reads m_pInstance just after a thread writes here.
			new(p)Logger{};                        // thus it will read an un-initialized object and return, which will crash the application.
		}
		m_Mtx.unlock();
	}	
	return *m_pInstance;
}


void Logger::WriteLog(const char *pMessage) {
	fprintf(m_pStream, "[%s] %s\n", m_Tag.c_str(), pMessage);
	fflush(m_pStream); // flush the stream because if the app crashes the runtime
					   // may not get a chance to flush the stream.
}

void Logger::SetTag(const char* pTag) {
	m_Tag = pTag;
}

// client.cpp
#include <thread>

void OpenConnection() {
	Logger &lg = Logger::Instance();
	lg.WriteLog("Attempting to write a log");
}

int main() {
	std::thread t1{[](){
		Logger &lg = Logger::Instance();
		lg.WriteLog("Thread 1 has started");
	}};

	std::thread t2{[](){
		Logger &lg = Logger::Instance();
		lg.WriteLog("Thread 2 has started");
	}};

	t1.join();
	t2.join();

	return 0;
}
