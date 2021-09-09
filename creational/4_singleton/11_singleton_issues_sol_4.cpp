/*
	In the previous implementations of the Multitons
	we use eager instantiation but that may not be desirable.
	So here we will use lazy instantiation.

	PrinterProvider will check if a printer with a key is available or not.
	If it is available then it returns otherwise it tries to instantiate a Printer
	with that key and it to map and return the instance.
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

	virtual ~Printer() = default;

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

using PrinterPtr = std::shared_ptr<Printer>;

class LocalPrinter : public Printer{
	LocalPrinter() = default;
public:
	// No longer required
	// LocalPrinter(const LocalPrinter&) = delete;
	// LocalPrinter& operator=(const LocalPrinter&) = delete;

	static PrinterPtr GetInstance();
	void Print(const std::string&) override;
};


// Lets try adding a new class to our new design
///////////////////////////////////////////////////////////
//////////////////////  PdfPrinter.h
///////////////////////////////////////////////////////////
// #pragma once
class PdfPrinter : public Printer{
	PdfPrinter() = default;
public:
	static PrinterPtr GetInstance();
	void Print(const std::string&) override;
};



///////////////////////////////////////////////////////////
//////////////////////  PrinterProvider.h
//////////////////////  Registry of Singletons. Multiton
///////////////////////////////////////////////////////////
// #pragma once
#include <string>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <functional>

using PrinterPtr = std::shared_ptr<Printer>;
// the Printer class will have to implement a function that returns a PrinterPtr
using Creator = std::function<PrinterPtr()>;
class PrinterProvider {
	struct InstanceInfo {
		PrinterPtr m_Printer{};
		Creator m_Creator{};
	};
	static std::unordered_map<std::string, InstanceInfo> m_Printers;
	static std::mutex m_mtx;
	PrinterProvider() = default;
public:
	static void RegisterCreator(const std::string&, Creator creator);
	static PrinterPtr GetPrinter(const std::string&);
};


///////////////////////////////////////////////////////////
//////////////////////  PrinterProvider.cpp
///////////////////////////////////////////////////////////
#include <iostream>

std::unordered_map<std::string, PrinterProvider::InstanceInfo> PrinterProvider::m_Printers;
std::mutex PrinterProvider::m_mtx;

void PrinterProvider::RegisterCreator(const std::string&key, Creator creator) {
	std::lock_guard lock(m_mtx);
	if (auto it = m_Printers.find(key); it == end(m_Printers))
		m_Printers[key].m_Creator = creator;
	else
		std::cout << "Already Registered\n";
}

PrinterPtr PrinterProvider::GetPrinter(const std::string&key) {
	std::lock_guard lock(m_mtx);
	if (auto it = m_Printers.find(key); it != end(m_Printers)) {
		if (!m_Printers[key].m_Printer) {
			m_Printers[key].m_Printer = m_Printers[key].m_Creator();
		}
		return m_Printers[key].m_Printer;
	}
	std::cout << key << " printer not found!\n";
	return nullptr;
}


///////////////////////////////////////////////////////////
//////////////////////  PdfPrinter.cpp
///////////////////////////////////////////////////////////

PrinterPtr PdfPrinter::GetInstance() {
	return std::shared_ptr<PdfPrinter>{new PdfPrinter()};
}

void PdfPrinter::Print(const std::string &data) {
	std::cout << "[PdfPrinter] " << data << std::endl;
}


///////////////////////////////////////////////////////////
//////////////////////  LocalPrinter.cpp
///////////////////////////////////////////////////////////
#include <iostream>

PrinterPtr LocalPrinter::GetInstance() {
	// This is amazing. Here the restriction is through the use of map in PrinterProvider.
	// Map lookup will ensure singularity as the instance will be created only if
	// it is not found in the map.
	return std::shared_ptr<LocalPrinter>{new LocalPrinter()};
	/*
	// Meyer's
		static std::shared_ptr<LocalPrinter> instance;
		instance.reset(new LocalPrinter());
		return instance;
	*/
}

void LocalPrinter::Print(const std::string &data) {
	std::cout << "[LocalPrinter] " << data << std::endl;
}


///////////////////////////////////////////////////////////
//////////////////////  client.cpp
///////////////////////////////////////////////////////////
// #include "LocalPrinter.h"

void PrintSales() {
	auto p = PrinterProvider::GetPrinter("local");
	if (p)
		p->Print("Sales data");
}

int main() {
	PrinterProvider::RegisterCreator("local", LocalPrinter::GetInstance);
	PrinterProvider::RegisterCreator("pdf", PdfPrinter::GetInstance);
	auto p = PrinterProvider::GetPrinter("pdf");
	if (p)
		p->Print("Printing data to the printer.");
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
