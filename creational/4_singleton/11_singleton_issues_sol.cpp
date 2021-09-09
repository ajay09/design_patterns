/*
	- When you use Singleton you have to use the name of the class directly.
	  Since class name is used directly, this violates the dependency inversion principle,
	  which states program to interface not to implementation.
	  Since we are directly using the name of the class, it will be very difficult if we
	  need to change it with some other class in future.
	  This also make unit testing difficult, because you cannot replace the usage of the Singleton
	  class with the mock object.
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

	// there can be different kinds of printer, we have to select based on some parameter.
	static Printer& GetInstance(const std::string&);
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
	LocalPrinter() = default;
public:
	// No longer required
	// LocalPrinter(const LocalPrinter&) = delete;
	// LocalPrinter& operator=(const LocalPrinter&) = delete;

	static LocalPrinter& GetInstance();
	void Print(const std::string&) override;
};


///////////////////////////////////////////////////////////
//////////////////////  Printer.cpp
///////////////////////////////////////////////////////////

Printer& Printer::GetInstance(const std::string &type) {
	if (type == "local") {
		return LocalPrinter::GetInstance();
	}
	// return LocalPrinter by default.
	return LocalPrinter::GetInstance();
}


///////////////////////////////////////////////////////////
//////////////////////  LocalPrinter.cpp
///////////////////////////////////////////////////////////
#include <iostream>

LocalPrinter LocalPrinter::m_Instance;

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
	Printer::GetInstance("local").Print("Sales data");
}

int main() {
	auto &p = Printer::GetInstance("local");
	p.Print("Printing data to local printer.");
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
}

*/
