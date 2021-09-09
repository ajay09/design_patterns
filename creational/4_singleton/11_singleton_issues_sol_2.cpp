/*
	- When a new printer class is added we should not require to modify the code that
	  returns a singular instance of the printer subclasses (i.e. Printer::GetInstance method)

	 - Instead of giving the responsibility to create the instance to the Printer class
	   we will take it out and put it in its own class. And in this class we will add a map
	   that will create a mapping between a key and a singular instance.
	   Thus when the application loads all the Singleton classes will register themselves
	   in the  PrinterProvider class with a specific key.
	   And when a client needs a Singleton class instance, then it can get it using the key.
*/


///////////////////////////////////////////////////////////
//////////////////////  Printer.h
//////////////////////  Base Printer class for all kinds of printers
///////////////////////////////////////////////////////////
// #pragma once
#include <string>

class Printer {
protected:
	// protected constructor
	Printer() = default;
public:
	// make it non-copy able
	Printer(const Printer&) = delete;
	Printer& operator=(const Printer&) = delete;

	virtual void Print(const std::string&) = 0;
};


///////////////////////////////////////////////////////////
//////////////////////  LocalPrinter.h
//////////////////////  This class manages the printer that
//////////////////////  is connected to the machine, thus it
//////////////////////  must be singleton.
///////////////////////////////////////////////////////////
// #pragma once
#include <string>

class LocalPrinter : public Printer{
	static LocalPrinter m_Instance; // here we are using Eager instantiation.
	// We will register it to PrinterProvider while constructing.
	LocalPrinter();
public:
	// No longer required
	// LocalPrinter(const LocalPrinter&) = delete;
	// LocalPrinter& operator=(const LocalPrinter&) = delete;

	static LocalPrinter& GetInstance();
	void Print(const std::string&) override;
};


///////////////////////////////////////////////////////////
//////////////////////  PrinterProvider.h
//////////////////////  We make it monostate
///////////////////////////////////////////////////////////
// #pragma once
#include <string>
#include <unordered_map>
#include <mutex>

class PrinterProvider {
	// in c++17 we can do it like this and no need of definition then
	// inline static std::unordered_map<std::string, Printer*> m_Printers{};
	static std::unordered_map<std::string, Printer*> m_Printers;
	PrinterProvider() = default;

	static std::mutex m_mtx;
public:
	// allows a printer to register itself using some key.
	static void RegisterPrinter(const std::string&, Printer*);
	static Printer* GetPrinterPtr(const std::string&);
	static Printer& GetPrinterRef(const std::string&);
};
/*
	This is called a Registry of Sinletons : aka Multiton
	It is useful if you have multiple singletons in your program. you can register
	them in one place and from that single place different parts of the program can pick
	up a particular Singleton based on its key.
*/


///////////////////////////////////////////////////////////
//////////////////////  PrinterProvider.cpp
//////////////////////  This is not threadsafe as such, we need to add locks.
///////////////////////////////////////////////////////////
#include <iostream>

std::unordered_map<std::string, Printer*> PrinterProvider::m_Printers;
std::mutex PrinterProvider::m_mtx;

void PrinterProvider::RegisterPrinter(const std::string&key, Printer*p) {
	std::lock_guard lock{m_mtx};
	if (auto it = m_Printers.find(key); it == end(m_Printers))
		m_Printers[key] = p;
	else
		std::cout << "Already Registered\n";
}

Printer* PrinterProvider::GetPrinterPtr(const std::string&key) {
	std::lock_guard lock{m_mtx};
	if (auto it = m_Printers.find(key); it != end(m_Printers))
		return m_Printers[key];
	std::cout << key << " printer not found!\n";
	return nullptr;
}

Printer& PrinterProvider::GetPrinterRef(const std::string&key) {
	std::lock_guard lock{m_mtx};
	auto p = GetPrinterPtr(key);
	if (p) return *p;
	throw std::runtime_error("No such printer exists.");
}



///////////////////////////////////////////////////////////
//////////////////////  LocalPrinter.cpp
///////////////////////////////////////////////////////////
#include <iostream>

LocalPrinter LocalPrinter::m_Instance;

LocalPrinter::LocalPrinter() {
	std::cout << "Registring Local Printer\n";
	PrinterProvider::RegisterPrinter("local", this);
}

LocalPrinter& LocalPrinter::GetInstance() {
	return m_Instance;
}

void LocalPrinter::Print(const std::string &data) {
	std::cout << "[LocalPrinter] " << data << std::endl;
}


///////////////////////////////////////////////////////////
//////////////////////  client.cpp
///////////////////////////////////////////////////////////
// #include "LocalPrinter.h"

void PrintSales() {
	auto p = PrinterProvider::GetPrinterPtr("local");
	if (p)
		p->Print("Sales data");
}

int main() {
	auto p = PrinterProvider::GetPrinterPtr("local");
	if (p)
		p->Print("Printing data to local printer.");
	PrintSales();

	return 0;
}


/*
	Since we are directly using the name of the class(concrete implementation)
	so we are violating the Dependency Inversion Principle.
	So in future if we wish to replace the LocalPrinter with a NetworkPrinter, we won't
	be able to do that.
	Secondly we would also like to unit test our code, so we won't be able to relace
	LocalPrinter with a mock object at line-58 in the client code.


	Instead of using the LocalPrinter directly in our code, we will inherit it from some
	class and then use it through that Class.
	With this approach we can use other printer classes without depending on their concrete
	types. This also makes unit testing easy because we can create a mock object and then
	have Printer::GetInstance() return that mock object.

	Thus the client code is not tightly coupled with the concrete class that it uses and the
	client gets the instance through the base class GetInstance method.

	This introduces one more issue :
	Printer& Printer::GetInstance(const std::string &type) {
		if (type == "local") {
			return LocalPrinter::GetInstance();
		}
		// return LocalPrinter by default.
		return LocalPrinter::GetInstance();
	}

	If we want to add one more printer then we need to modify this code.
	This violates the "Open-Closed  Principle"

	
	Now the responsibility of creating a Singular instance is in the PrinterProvider class.


*/
