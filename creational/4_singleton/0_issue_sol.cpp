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

	// If we don't delete the copy constructor the
	// Logger lg = Logger::Instance(); will create a copy of the Logger object
	// thus again we will have multiple copies of the logger.
	// Since we have not defined a copy constructor so it will use the default copy constructor
	// which will create a shallow copy of the object thus would create other issues also.
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	static Logger m_Instance;
	// The m_Instance will be created even before main is invoked i.e. as and when the program is invoked.
	// This may not be desirable.
	// This is Eager instance, because as soon as program is loaded a file stream will be opened.
	// If you don't want eager instance you can go with lazy instance.
	// In lazy instantiation the instance will be created only when Instance() is called.
	FILE *m_pStream;
	std::string m_Tag;
};

// logger.cpp

// initialize the static member variable
Logger Logger::m_Instance;

Logger::Logger() {
	m_pStream = fopen("issue_2.log", "w");
}

Logger::~Logger() {
	fclose(m_pStream);
}

Logger& Logger::Instance(){
	return m_Instance;
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