// A simple contact management application

#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Address {
	string street;
	string city;

	friend ostream& operator<<(ostream &os, const Address &obj) {
		return os
			<< "Street : " << obj.street
			<< "  City : " << obj.city;
	}
}

struct Contact {
	string name;
	Address *work_address;

	~Contact() {
		delete work_address;
	}

	friend ostream& operator<<(ostream &os, const Contact &obj) {
		return os
			<< "Name : " << obj.name
			<< "  Work address : " << *obj.work_address;
	}
};

int main() {
	Contact john{"John Doe", new Address{"123 East Dr", "London"}};
	Contact jane{"Jane Doe", new Address{"123 East Dr", "London"}};
	// This is fine

	// But this will be incorrect to do
	Address *addr = new Address{"342 SS", "Banglore"};
	Contact john2{"John Doe", addr};
	Contact jane2{"Jane Doe", addr};

	// The solution to the above issue would be : deep copy.
	// We don't want them to share the same address object.


	return 0;
}