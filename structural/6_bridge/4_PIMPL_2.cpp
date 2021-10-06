/*
	In PIMPL, we take out the implementation of the class and put in a
	separate class.


	Now if we have to add one more component to the salary, we can see if we compile
	the project only Employee.cpp is compiled. Other files which depends upon Employee.h
	are not compiled.


	Thus modifying the EmployeeImpl class will not affect the clients. This helps
	preserve the binary compatibility between the libraries and their clients.
	The reason is, the clients depends upon the Employee class and not the
	EmployeeImpl.
*/

//////////////////////////////////////
/////////////////////  Employee.h
//////////////////////////////////////
#include <string>

class Employee {
	class EmployeeImpl; // forward declare inside the class itself, 
					    // so clients are not exposed to it.
	EmployeeImpl *m_pEmp;
public:
	Employee(const std::string& name, int basic);

	int GetTotalSalary() const;
	int ComputeTaxLiability() const;
	const std::string GetName() const;

	~Employee() {
		delete m_pEmp;
	}
};




//////////////////////////////////////
/////////////////////  Employee.cpp
//////////////////////////////////////
#include <string>


// This is the implementation class of the Employee and will contain the attributes 
// required by the Employee class. This class will implement the functionality of 
// the Employee class that's why we will add the methods to the class.
class Employee::EmployeeImpl {
	std::string m_Name;
	int m_BasicSalary;
	int m_HRA, m_LTA, m_CA;
public:
	EmployeeImpl(const std::string& name, int basic) :
		m_Name{name}, m_BasicSalary{basic} {
		m_HRA = 0.10 * basic;
		m_LTA = 0.05 * basic;
		m_CA = 0.07 * basic;
	}

	int GetTotalSalary() { return m_BasicSalary + m_HRA + m_LTA + m_CA; }
	int ComputeTaxLiability() const { return 0.20 * m_BasicSalary; }
	const std::string GetName() const { return m_Name; }
};

Employee::Employee(const std::string& name, int basic) {
	m_pEmp = new EmployeeImpl{name, basic};
}

int Employee::GetTotalSalary() const {
	return m_pEmp->GetTotalSalary();
}

int Employee::ComputeTaxLiability() const {
	return m_pEmp->ComputeTaxLiability();
}

const std::string Employee::GetName() const {
	return m_pEmp->GetName();
}




//////////////////////////////////////
/////////////////////  Client.cpp
//////////////////////////////////////
#include <iostream>

int main() {
	Employee a{"A", 1000};

	std::cout << "Name : " << a.GetName() << std::endl;
	std::cout << "Total Salary : " << a.GetTotalSalary() << std::endl;
	std::cout << "Tax : " << a.ComputeTaxLiability() << std::endl;

	return 0;
}