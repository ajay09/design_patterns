/*
	Standart C++ doesn't provide any support for writing colored text onto the console.
	Because different OS will have different ways of printing color text on the console
	and some may even not support it.


	We can use the Win32 API to print colored output.
	But our application will be depend on the low level C-API's that are provided
	by the OS. If we want to use a different OS then these API's won't work
	instead we will have to use differnt APIs.

	To use the APIs based upon the OS platform we will have to use Pre-processor Directives.
	These pre-processor directives may get littered throughout our application
	and will increase its complexity. The code will become hard to reuse.

	The other problem with our implementation will be that we are using low level C APIs
	that have complex parameters. This further increases the complexity.
	Also these APIs are not ObjectOriented, thus its difficult to extend their functionality.


	Thus we will use Facade design pattern.
	It will reduce our dependency on the low-level C APIs.
	And also reduce the complexity that is associated with these APIs by providing an
	object oriented interface.


	The Console clas is our Facade.
	What are the advantages of using this console class?
	
	- First of all, we are not directly dependent on the operating system AIP's, 
	  the Console class interact with those API's on our behalf.
	  So this way, even if we change the platform, the client code will not change.
      The only thing we have to do is change the code in the console class and 
      use the API's of the corresponding operating system.
	  So here the dependency on the low level operating system API's is reduced.
	  So we have a loose coupling here.

	- The second thing is it is now easy for the clients to write color text on 
	  the console because we have provided a simple API, so we have converted the 
	  complex interface into a simple interface.

	- And third, we have provided an object oriented interface to the low level API's
*/

#include <iostream>
#include <string>

enum class Color{RED, GREEN, BLUE, WHITE};

class Console {
	virtual void SetColor(Color color) = 0;
	Console(Console&) = delete;
	Console(Console&&) = delete;

	Console& operator=(Console&) = delete;
	Console& operator=(Console&&) = delete;
protected:
	Console() = default;
public:
	virtual void Write(const std::string&, Color) = 0;
	virtual void WriteLine(const std::string&, Color) = 0;
	virtual ~Console() = default;
};


class LinuxConsole : public Console {
	LinuxConsole() = default;
	LinuxConsole(LinuxConsole&) = delete;
	LinuxConsole(LinuxConsole&&) = delete;

	LinuxConsole& operator=(LinuxConsole&) = delete;
	LinuxConsole& operator=(LinuxConsole&&) = delete;

	void SetColor(Color color) override {
		switch (color) {
			case Color::RED :
				std::cout << "\033[31m";
				break;
			case Color::GREEN :
				std::cout << "\033[32m";
				break;
			case Color::BLUE :
				std::cout << "\033[34m";
				break;
			case Color::WHITE :
				std::cout << "\033[00m";
				break;
		}
	}
public:
	static LinuxConsole& GetInstance() {
		static LinuxConsole lConsole;
		return lConsole;
	}

	void Write(const std::string &text, Color color = Color::WHITE) override {
		SetColor(color);
		std::cout << text;
		SetColor(Color::WHITE);
	}

	void WriteLine(const std::string &text, Color color = Color::WHITE) override {
		Write(text + "\n", color);
	}

	~LinuxConsole() = default;
};


#include <exception>
#include <stdexcept>

// These funcitons are defined just to support compilation on Mac
// as I don't have WDK on mac.

using HANDLE = unsigned long;
using DWORD = unsigned long;
#define FOREGROUND_RED 1
#define FOREGROUND_GREEN 2
#define FOREGROUND_BLUE 3
struct CONSOLE_SCREEN_BUFFER_INFO {
	DWORD wAttributes;
};
#define STD_OUTPUT_HANDLE "STD_OUTPUT_HANDLE"
HANDLE GetStdHandle(const std::string& type) {
	// something
	HANDLE h{7777};
	return h;
}
bool GetCosoleScreenBufferInfo(HANDLE &h, CONSOLE_SCREEN_BUFFER_INFO *info) {
	return true;
}
void SetConsoleTextAttribute(HANDLE &m_Std, CONSOLE_SCREEN_BUFFER_INFO *info) {

}
void SetConsoleTextAttribute(HANDLE &m_Std, DWORD color) {

}
void WriteConsoleA(HANDLE m_Std, const char *text, size_t len, DWORD *written, void* unknown) {

}
class WindowsConsole : public Console{
	WindowsConsole() {
		m_Std = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!GetCosoleScreenBufferInfo(m_Std, &m_consolebufferinfo)) {
			throw std::runtime_error("Error while retrieving console information");
		}
	}
	WindowsConsole(WindowsConsole&) = delete;
	WindowsConsole(WindowsConsole&&) = delete;

	WindowsConsole& operator=(WindowsConsole&) = delete;
	WindowsConsole& operator=(WindowsConsole&&) = delete;

	void SetColor(Color color) override {
		switch (color) {
			case Color::RED :
				m_Color = FOREGROUND_RED;
				break;
			case Color::GREEN :
				m_Color = FOREGROUND_GREEN;
				break;
			case Color::BLUE :
				m_Color = FOREGROUND_BLUE;
				break;
			case Color::WHITE :
				m_Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
				break;
		}
	}

	HANDLE m_Std;
	CONSOLE_SCREEN_BUFFER_INFO m_consolebufferinfo{};
	DWORD m_Color;
public:
	static WindowsConsole& GetInstance() {
		static WindowsConsole wConsole;
		return wConsole;
	}

	void Write(const std::string &text, Color color = Color::WHITE) override {
		CONSOLE_SCREEN_BUFFER_INFO csbi{};
		if (!GetCosoleScreenBufferInfo(m_Std, &csbi)) {
			throw std::runtime_error("Error while retrieving console information");
		}
		SetColor(color);
		SetConsoleTextAttribute(m_Std, m_Color);
		DWORD written{};
		WriteConsoleA(m_Std, text.c_str(), text.length(), &written, nullptr);
		SetConsoleTextAttribute(m_Std, csbi.wAttributes);
	}

	void WriteLine(const std::string &text, Color color = Color::WHITE) override {
		Write(text + "\n", color);
	}

	~WindowsConsole() {
		SetConsoleTextAttribute(m_Std, &m_consolebufferinfo);
	}
};


int main() {
	/*
		LinuxConsole::GetInstance().WriteLine("Hello world", Color::RED);
		std::cout << "Using cout\n";
		printf("Using printf\n");
		LinuxConsole::GetInstance().Write("Different color", Color::GREEN);
		std::cout << std::endl;
	*/


	Console &c = LinuxConsole::GetInstance();
	c.WriteLine("Hello world", Color::RED);
	std::cout << "Using cout\n";
	printf("Using printf\n");
	c.Write("Different color", Color::GREEN);
	std::cout << std::endl;

	return 0;
}