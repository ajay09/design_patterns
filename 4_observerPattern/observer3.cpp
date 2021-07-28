// Making the observer pattern thread safe
//  vector<PersonListener*> listeners;   is the point of interest for different threads
//  Add lock guard at each location where the collection is modified 

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <boost/any.hpp>

using namespace std;
using boost::any;
using boost::any_cast;

struct Person;

static mutex mtx;

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
		lock_guard<mutex> guard{ mtx };
		// To prevent multiple substriptions by the same listener.
		if (find(begin(listeners), end(listeners), pl) == end(listeners))
			listeners.push_back(pl);
	}

	// To unsubscribe don't delete the entry just make it null
	void unsubscribe(PersonListener *pl) {
		lock_guard<mutex> guard{ mtx };
		for (auto it = listeners.begin(); it != listeners.end(); ++it) {
			if (*it == pl)
				*it = nullptr;
		}
	}

	// Whenever someone calls notify then we actually erase the null values.
	void notify(const string &property_name, const any new_value) {
		lock_guard<mutex> guard{ mtx };
		for (const auto listener : listeners) {
			if (listener != nullptr)
				listener->PersonChanged(*this, property_name, new_value);
		}

		listeners.erase(
			remove(listeners.begin(), listeners.end(), nullptr), listeners.end()
		);
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
	p.subscribe(&cl);
	p.subscribe(&cl);

	p.SetAge(15);
	p.SetAge(16);

	return 0;
}