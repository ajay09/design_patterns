// logger.hpp

// #pragma once

#include <cstdio>
#include <string>

// Prefer returning reference instead of pointer
// Pointers can be NULL thus have to be checked everytime before using them
// whereas References can never be NULL.
class Logger {
public:
	~Logger();
	void WriteLog(const char *pMessage);
	void SetTag(const char *pTag);
	static Logger& Instance();
private:
	Logger(); // to prevent instance creation.
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	static Logger *m_pInstance;

	FILE *m_pStream;
	std::string m_Tag;
};

// logger.cpp

#include <iostream>

// initialize the static member variable
Logger *Logger::m_pInstance;

Logger::Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	m_pStream = fopen("5.log", "w");
}

Logger::~Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	fclose(m_pStream);
}

// Instance will be crated only when you call the Instance method for the first time.
Logger& Logger::Instance(){
	if (m_pInstance == nullptr) {
		m_pInstance = new Logger{};
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

void OpenConnection() {
	Logger &lg = Logger::Instance();
	lg.WriteLog("Attempting to write a log");
}

int main() {
	Logger &lg = Logger::Instance();
	lg.SetTag("192.168.0.19");
	lg.WriteLog("Application has started");
	OpenConnection();
	lg.WriteLog("Application is shutting down");
	return 0;
}

/*
	There is still an issue with this implementation.

	We can see the constructor is called. But the destructor is never invoked.
	This is because we have not deleted the m_pInstance.
	We can not delete an instance at the end of the main.
*/