/*
	DCLP
	Double-Checked Locking Pattern

	A solution to DCLP problem is "Meyer's Singleton"

	Benefits :
	- It's lazy instantialization
	- "static Logger instance" => instance is not allocated memory over
	   the heap thus we don't have to call delete on it.
	   It is stored in the data section.
	   The instance will automatically be destroyed by the runtime after
	   main returns.
	- From C++11 onwards static variable construction is thread-safe.
	- Another problem with the normal static member instance type singleton is that
	  in a program with multiple files the order of instantiasation can't be ascertained.
	  Thus it can happen that some file might try to use the singleton object before
	  it is instantiated. Meyer's singleton solves this issue. Here the Singleton will
	  be  instantiated at the time of its first use.

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


	FILE *m_pStream;
	std::string m_Tag;
};

// logger.cpp

#include <iostream>
#include <memory>


Logger::Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	m_pStream = fopen("7_2.log", "w");
}

Logger::~Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	fclose(m_pStream);
}

Logger& Logger::Instance(){
	static Logger instance;
	return instance;
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
