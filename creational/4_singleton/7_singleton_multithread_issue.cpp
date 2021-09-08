/*
	Caution
	You have to ensure that your logger instances are not used in the destructors of
	global and static objects.
	In C++, The order of construction and destruction of global and static objects across 
	translation units is unspecified.
	So if a logger instance is used in a destructor of a global or static object and during
	termination of the program maybe the logger object gets destroyed first.
	and when the other objects are destroyed, in the destructor they will try to access
	the logger object. So in that case a new instance of the logger may get created
	and may overwrite the log file, thus the existing log may get lost.

	This may also happen in case a constructor of a global or static object is trying to access
	a method of another global or static object.
	In C++, this is called as "Static Initialization Fiasco."
*/

// logger.hpp

// #pragma once

#include <cstdio>
#include <string>

// Prefer returning reference instead of pointer
// Pointers can be NULL thus have to be checked everytime before using them
// whereas References can never be NULL.
class Logger {
public:
	void WriteLog(const char *pMessage);
	void SetTag(const char *pTag);
	static Logger& Instance();
private:
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

Logger::Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	m_pStream = fopen("7_1.log", "w");
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

// Instance will be crated only when you call the Instance method for the first time.
Logger& Logger::Instance(){
	if (m_pInstance == nullptr) {
		m_pInstance = new Logger;
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

	/*
		We can see the issue with this in the output:
		   the constructor gets invoked twice.
		The problem is 2 threads have called Instance at the same time
		And both checked if(m_pInstance == nullptr) which can be true for both of them.
		thus both will end up invoking the Logger constructor.
	*/

	return 0;
}
