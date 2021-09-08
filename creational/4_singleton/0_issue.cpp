// logger.hpp

// #pragma once

#include <cstdio>
#include <string>

class Logger {
public:
	Logger();
	~Logger();
	void WriteLog(const char *pMessage);
	void SetTag(const char *pTag);
private:
	FILE *m_pStream;
	std::string m_Tag;
};

// logger.cpp

Logger::Logger() {
	m_pStream = fopen("issue.log", "w");
}

Logger::~Logger() {
	fclose(m_pStream);
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
	Logger lg;
	lg.WriteLog("Attempting to write a log");
}

int main() {
	Logger lg;
	lg.SetTag("192.168.0.19");
	lg.WriteLog("Application has started");
	OpenConnection();
	lg.WriteLog("Application is shutting down");
	return 0;
}

/*
		Line : 50 => 
			OpenConnection();

		causes the undefined behaviour in the log file we see here.

		The problem is due to the fact that two instances are created and the constructor
		of each instance attempts to open the file in write mode. Since the dtream is already
		open in write mode when another instance tries to open it, it may either fail or
		succeed, the behavior is undefined.

		So, we need to ensure that there is only one instance of the logger.

		You may think we can create a global instance of the logger and use it everywhere.
		That may work but it will not prevent the user from creating multiple instances
		of the logger.

		So the first thing we need to do is to preven the user from creating instances of this class.
	
*/