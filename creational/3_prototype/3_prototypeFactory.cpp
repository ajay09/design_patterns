// A simple contact management application

#include <vector>
#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Address {
	string street;
	string city;
	int suite;

	friend ostream& operator<<(ostream &os, const Address &obj) {
		return os
			<< "Street : " << obj.street
			<< "  City : " << obj.city
			<< "  Suite : " << obj.suite;
	}
};

struct Contact {
	string name;
	Address *work_address;

	Contact(const string &name, Address * const work_address) : name{name}, 
												work_address{new Address(*work_address)} {}

	~Contact() {
		delete work_address;
	}

	Contact(const Contact &other) : name{other.name}, work_address(new Address{*other.work_address}) {
	}

	friend ostream& operator<<(ostream &os, const Contact &obj) {
		return os
			<< "Name : " << obj.name
			<< "  Work address : " << *obj.work_address;
	}
};

struct EmployeeFactory {
	static unique_ptr<Contact> NewMainOfficeEmployee() {
		static Contact employee{"", new Address{"123 East Dr", "London", 0}}; // prototype
		return make_unique<Contact>(employee);
	}
};


// A factory which can customise the objects while creating them.
struct EmployeeFactory2 {
	static Contact main, aux;

	static unique_ptr<Contact> NewMainOfficeEmployee(const string &name, int suite) {
		return NewEmployee(name, suite, main);
	}

	static unique_ptr<Contact> NewAuxOfficeEmployee(const string &name, int suite) {
		return NewEmployee(name, suite, aux);
	}
private:
	static unique_ptr<Contact> NewEmployee(string name, int suite, Contact &prototype) {
		auto result = make_unique<Contact>(prototype);
		result->name = name;
		result->work_address->suite = suite;
		return result;
	}
};

Contact EmployeeFactory2::main{"", new Address{"123 East Dr", "London", 0}};
Contact EmployeeFactory2::aux{"", new Address{"123B East Dr", "London", 0}};

int main() {
	// Contact john2{employee};
	// john2.name = "John";
	// john2.work_address->suite = 100;

	// Contact jane2{employee};
	// jane2.name = "Jane";
	// jane2.work_address->suite = 300;

	auto john = EmployeeFactory::NewMainOfficeEmployee();
	john->name = "john";
	john->work_address->suite = 100;

	auto jane = EmployeeFactory2::NewAuxOfficeEmployee("jane", 300);

	cout << *john << endl << *jane << endl;

	return 0;
}