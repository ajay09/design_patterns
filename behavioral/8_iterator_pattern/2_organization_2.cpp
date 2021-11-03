/*
	Create a class Organization
	and the Organization contains Employees.

	The client code should be able to access individual Employee objects without having
	to know how they are stored inside the Organization class.


	Implement an iterator for the Organization such that the Iterator holds the iteration algo.


	Benefit : we can create new iterator classes which can implement different traversal algo.
*/

////////////////////////////////////
////////////////////  Employee.h
////////////////////////////////////
#include <string>
class Employee {
	std::string m_Name;
public:
	Employee() = default;

	Employee(std::string name) : m_Name{std::move(name)} {}

	const std::string& GetName() const {
		return m_Name;
	}

	void SetName(std::string name) {
		m_Name = std::move(name);
	}
};





////////////////////////////////////
////////////////////  Organization.h
////////////////////////////////////
#include <cstddef>
class EmpIterator;

class Organization {
	static constexpr size_t MAX_EMPLOYEES{10};
	Employee m_Employees[MAX_EMPLOYEES];
	size_t m_Size{};
public:
	Organization() : m_Size{0} {}

	void AddEmployee(Employee emp) {
		m_Employees[m_Size++] = std::move(emp);
	}
	
	size_t Size() const {
		return m_Size;
	}

	EmpIterator* CreateIterator() const;
};


////////////////////////////////////////
//////////////////////// EmpIterator.h
////////////////////////////////////////
class EmpIterator {
	const Employee *m_pEmployee;
	const Employee *m_pEnd;
public:
	EmpIterator(const Employee* pEmployee, const Employee *pEnd) : m_pEmployee{pEmployee}, m_pEnd{pEnd} {}

	bool HasNext() const {
		return m_pEmployee != m_pEnd;
	}

	void Next() {
		m_pEmployee++;
	}

	const Employee& CurrentItem() const {
		return *m_pEmployee;
	}
};


EmpIterator* Organization::CreateIterator() const {
	return new EmpIterator{m_Employees, m_Employees + MAX_EMPLOYEES};
}




#include <iostream>

int main() {
	Organization organization ;
	organization.AddEmployee({"ABC"}) ;
	organization.AddEmployee({"Ajay"}) ;
	organization.AddEmployee({"Sandhya"}) ;

	std::unique_ptr<EmpIterator> iterator{organization.CreateIterator()};

	while (iterator->HasNext()) {
		std::cout << iterator->CurrentItem().GetName() << std::endl;
		iterator->Next();
	}

	return 0;
}