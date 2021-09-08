// A simple contact management application

#include <vector>
#include <iostream>
#include <string>

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

// Since we wish to copy the entire object
// We would have a prototype Contact which would have a pre-initialized address
// and we would make copies of this contact and customize it.
// And for that we need to define Copy-Constructor rather than using the default one.

int main() {
	Address *addr = new Address{"342 SS", "Banglore"};
	Contact john{"John Doe", addr};
	john.work_address->suite = 100;
	Contact jane{"Jane Doe", addr};
	jane.work_address->suite = 300;

	Contact jill(jane);
	jill.work_address->suite = 444;

	cout << john << endl << jane << endl << jill << endl;



	Contact employee{"", new Address{"123 East Dr", "London", 0}}; // prototype
	Contact john2{employee};
	john2.name = "John";
	john2.work_address->suite = 100;

	Contact jane2{employee};
	jane2.name = "Jane";
	jane2.work_address->suite = 300;

	cout << john2 << endl << jane2 << endl;

// Problem with this is we have a memory leak at line-49 and line-33

	return 0;
}