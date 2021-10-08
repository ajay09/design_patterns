#include <iostream>
#include <string>
#include <vector>
#include <boost/any.hpp>

using namespace std;
using boost::any;
using boost::any_cast;

struct Person;

// Suppose as a person ages some other component wants to be notified that the
// person is aging
// One way is to define a new interface PersonListner
// PersonListener is a class that can listen to changes in person and respond to them.
struct PersonListener {
	virtual ~PersonListener() = default;
	// This will be the function that will be called whenever something changes in Person.
	// While calling it you will like to provide some info like which person changed.
	// and which property of person changed
	virtual void PersonChanged(Person &p, const string &property_name, const any new_value) = 0;
};

struct Person {
	explicit Person(int age) : age(age) {}

	virtual int GetAge() const {
		return age;
	}

	virtual void SetAge(const int age) {
		if (this->age == age)
			return;
		this->age = age;
		notify("age", this->age);
	}

	void subscribe(PersonListener *pl) {
		listeners.push_back(pl);
	}

	void notify(const string &property_name, const any new_value) {
		for (const auto listener : listeners) {
			listener->PersonChanged(*this, property_name, new_value);
		}
	}
private:
	int age;
	vector<PersonListener*> listeners;
};

// A class that will output to console any changes in person.
// We have a console listener but how do the two of them connect? => for this we need to have a set of listeners inside the Person.
//                                                   				  Person needs to be aware of the components which are listening to it.
struct ConsoleListener : PersonListener {
	void PersonChanged(Person &p, const string &property_name, const any new_value) override {
		cout << "Person's " << property_name << " has been changed to " ;
		if (property_name == "age") {
			cout << any_cast<int>(new_value);
		}
		cout << endl;
	}
};

int main() {
	Person p{14};
	ConsoleListener cl;
	// now we need to connect the two
	p.subscribe(&cl);

	p.SetAge(15);
	p.SetAge(16);

	return 0;
}