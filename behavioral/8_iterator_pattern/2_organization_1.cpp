/*
	Create a class Organization
	and the Organization contains Employees.

	The client code should be able to access individual Employee objects without having
	to know how they are stored inside the Organization class.


	Current implementation : The Iterator holds only the position while
	          				 The Aggregate implements the traversal algo.

	Issue : To add more traversal algo we have to modify the Organization class.

			The Cursor only holds the state of the iteration. But doesn't have the traversal algo.
			The algo is inside the Aggregate (Organization).
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
////////////////////  Cursor.h
////////////////////////////////////
class Cursor {
	const Employee *m_emp;
	
	Cursor(const Employee *pEmp) : m_emp{pEmp} {}

	friend class Organization;
};

////////////////////////////////////
////////////////////  Organization.h
////////////////////////////////////
#include <cstddef>
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

	Cursor* CreateCursor() const {
		return new Cursor{m_Employees};
	}

	void Next(Cursor*& cursor) const {
		cursor->m_emp++;
	}

	const Employee& GetAt(Cursor *cursor) const {
		return *cursor->m_emp;
	}

	bool HasNext(Cursor *cursor) const {
		return cursor->m_emp != (m_Employees + MAX_EMPLOYEES);
	}
};


#include <iostream>

int main() {
	Organization organization ;
	organization.AddEmployee({"ABC"}) ;
	organization.AddEmployee({"Ajay"}) ;
	organization.AddEmployee({"Sandhya"}) ;

	auto cursor = organization.CreateCursor();

	while (organization.HasNext(cursor)) {
		std::cout << organization.GetAt(cursor).GetName() << std::endl;
		organization.Next(cursor);
	}

	return 0;
}