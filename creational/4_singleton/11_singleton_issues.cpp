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
//////////////////////  LocalPrinter.h
//////////////////////  This class manages the printer that
//////////////////////  is connected to the machine, thus it
//////////////////////  must be singleton.
///////////////////////////////////////////////////////////
// #pragma once
#include <string>

class LocalPrinter {
	LocalPrinter() = default;
	static LocalPrinter m_Instance; // here we are using Eager instantiation.
public:
	LocalPrinter(const LocalPrinter&) = delete;
	LocalPrinter& operator=(const LocalPrinter&) = delete;

	static LocalPrinter& GetInstance();
	void Print(const std::string&);
};


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
	LocalPrinter::GetInstance().Print("Sales data");
}

int main() {
	auto &p = LocalPrinter::GetInstance();
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
*/
