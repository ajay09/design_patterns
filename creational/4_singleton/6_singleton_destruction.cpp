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

	class Deleter {
	public:
		void operator()(Logger *p) {
			delete p;
		}
	};

	// static Logger *m_pInstance;
	static std::unique_ptr<Logger, Deleter> m_pInstance;
	//c++17
	// inline static std::unique_ptr<Logger> m_pInstance{};
	// This will initialize the static variable in the class itself (from c++17)

	FILE *m_pStream;
	std::string m_Tag;
};

// logger.cpp

#include <iostream>
#include <memory>

// initialize the static member variable
std::unique_ptr<Logger, Logger::Deleter> Logger::m_pInstance;

Logger::Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	m_pStream = fopen("6.log", "w");
}

Logger::~Logger() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	fclose(m_pStream);
}

// Instance will be crated only when you call the Instance method for the first time.
Logger& Logger::Instance(){
	if (m_pInstance == nullptr) {
		m_pInstance.reset(new Logger());
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

	/*
		If we don't make the destructor private the user can call delete on the Logger instance
		auto *p = &lg;
		delete p;

		To prevent this we need to keep the destructor as private.
		But then the unique_ptr won't be able to delete the Logger instance.
		To circumvent this we need to provide our own deleter to the unique_ptr.
	*/
	// auto *p = &lg;
	// delete p;	

	return 0;
}

/*
	Depending on what the Destructor does, you may not have to call delete on the Singleton
	instance.
	Here the destructor only closes the file handle. When the application terminates, the
	destructor won't be invoked but the application will flush the file buffers and close
	all the file handles. So in this particular example we don't really need to call delete
	on the logger instance.
	Will not calling delete lead to memory leak here?
		=> The logger instance has to be available throughout the program so its lifetime
			will be same as the lifetime of the program. So even if we don't call
			delete it won't be a memory leak.


	But assume your destructor is releasing some important resource e.g. it is setting an 
	event or releasing a semaphore and other applications are waiting on these.
	In those cases if the destructor is not invoked these resources will not be released
	and other applications may get blocked. So we need to ensure the destructor is
	invoked somehow. And it can be invoked only when you delete the Logger instance.
	This can be done in two ways :
		1- using smart pointer  =>   create a static instance of smart pointer.
									and assign the logger instance to it.
									When the program terminates the static smart pointer
									will be destroyed and it will invoke delete on logger instance.

		2- register a callback using atexit()  => atexit() is a CRT
												  and can be used to register a callback
												  function that will get invoked after main
												  returns.
*/