/*
	Use of PIMPL : 
		- To implement sharing between the objects. e.g. SharedString
		- To hide implementation details of a class from the clients.
			because when we change the implementation, the client should not be impacted.
*/

#include <string>

class Employee {
	std::string m_Name;
	int m_BasicSalary;
	int m_HRA;
public:
	Employee(const std::string& name, int basic) :
			m_Name{name}, m_BasicSalary{basic} {
			m_HRA = 0.10 * basic;
	}

	int GetTotalSalary() const {
		return m_BasicSalary + m_HRA;
	}

	int ComputeTaxLiability() const {
		return 0.20 * m_BasicSalary;
	}

	const std::string GetName() const {
		return m_Name;
	}
};


/*
	Suppose there are two files  Tax.cpp  and Accounts.cpp which use 
	Employee.h by including it and also links its object file.

	Suppose the complany wants to add more components to the salary.
	e.g. they add LTA to the salary.

	Thus we will have to modify the Employee class to support LTA.

	On building the project all the files that include Employee.h
	will have to be built again. So if the Employee class were in
	a library (dll or shared library) and is used by other applications
	then if you modify this class, it will break the binary
	compatibility of the library.


	This is a common problem in C++, but it can be easily solved
	through the PIMPL idiom.

*/

#include <iostream>

int main() {
	Employee a{"A", 1000};

	std::cout << "Name : " << a.GetName() << std::endl;
	std::cout << "Total Salary : " << a.GetTotalSalary() << std::endl;
	std::cout << "Tax : " << a.ComputeTaxLiability() << std::endl;

	return 0;
}