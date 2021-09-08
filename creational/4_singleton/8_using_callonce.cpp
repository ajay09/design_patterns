/*
	std::call_once  from  <mutex>
	
	template<class Callable, class... Args>
	void call_once(std::once_flag&, Callable&& f, Args&&... args);

	Executes the Callable object f exactly once, even if called concurrently
	from several threads.

	We can use this to create only one instance of the Logger Class.
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

	FILE *m_pStream;
	std::string m_Tag;
};

// logger.cpp

#include <iostream>
#include <memory>


Logger *Logger::m_pInstance;

Logger::Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	m_pStream = fopen("8.log", "w");
	atexit([](){
		delete m_pInstance;
	});
}

Logger::~Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	fclose(m_pStream);
}

std::once_flag flag;
Logger& Logger::Instance(){
	std::call_once(flag, []() {
		m_pInstance = new Logger();
	});
	return *m_pInstance;
}
// Similar for windows =>  InitOnceExecuteOnce 
// Similar for Linux(POSIX)  =>  pthread_once
// But prefer Meyer's over call_once


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
