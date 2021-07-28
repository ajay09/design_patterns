#include <iostream>
#include <string>
#include <vector>
#include <boost/any.hpp>

using namespace std;
using boost::any;
using boost::any_cast;

struct Person;

struct PersonListener {
	virtual ~PersonListener() = default;
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
		bool old_can_vote = GetCanVote();

		this->age = age;
		notify("age", this->age);
		
		bool new_can_vote = GetCanVote();
		if (old_can_vote != new_can_vote)
			notify("can vote", new_can_vote);
	}

	/*
		Now you want the ability to get notified exactly when a person attains the voting age.
		i.e. a notification on your ability to vote.
		
		Thus with observer patter :
		- It's very difficult to express the idea of dependencies between properties.
		- or the idea that some properties are effectively read-only. They can't be set
		  they can only be acquired. And if you want notification on them then logic
		  can get pretty complex.
		  This problem can escalate for some other cases.
	*/

	bool GetCanVote() const {
		return age >= 18;
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

struct ConsoleListener : PersonListener {
	void PersonChanged(Person &p, const string &property_name, const any new_value) override {
		cout << "Person's " << property_name << " has been changed to " ;
		if (property_name == "age") {
			cout << any_cast<int>(new_value);
		} else if (property_name == "can vote") {
			cout << any_cast<bool>(new_value);
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
	p.SetAge(18);

	return 0;
}

