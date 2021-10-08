// We will model the states of a telephone.

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum class State {
	OffHook,
	Connecting,
	Connected,
	OnHold
};

inline ostream& operator<<(ostream &os, const State &s) {
	switch (s) {
		case State::OffHook:
			os << "off the hook";
			break;
		case State::Connecting:
			os << "Connecting";
			break;
		case State::Connected:
			os << "Connected";
			break;
		case State::OnHold:
			os << "on hold";
			break;
	}
	return os;
}

enum class Trigger {
	CallDialed,
	HungUp,
	CallConnected,
	PlacedOnHold,
	TakenOffHold,
	LeftMessage
};

inline ostream& operator<<(ostream &os, const Trigger &t) {
	switch (t) {
		case Trigger::CallDialed:
			os << "call dialed";
			break;
		case Trigger::HungUp:
			os << "hung up";
			break;
		case Trigger::CallConnected:
			os << "call connected";
			break;
		case Trigger::PlacedOnHold:
			os << "placed on hold";
			break;
		case Trigger::TakenOffHold:
			os << "taken off hold";
			break;
		case Trigger::LeftMessage:
			os << "left message";
			break;
	}
	return os;
}

int main() {
	// stores the rules of our state machine.
	map<State, vector<pair<Trigger, State>>> rules;

	rules[State::OffHook] = { {Trigger::CallDialed, State::Connecting} };

	rules[State::Connecting] = { {Trigger::HungUp, State::OffHook},
								 {Trigger::CallConnected, State::Connected}
								 };

	rules[State::Connected] = { {Trigger::LeftMessage, State::OffHook},
								{Trigger::HungUp, State::OffHook},
								{Trigger::PlacedOnHold, State::OnHold}
							  };

	rules[State::OnHold] = { {Trigger::TakenOffHold, State::Connected},
							 {Trigger::HungUp, State::OffHook}
							};

	State currentState{ State::OffHook };

	while (true) {
		cout << "The phone is currently " << currentState << endl;
		int input;
		while (true) {
			cout << "Select a trigger : " << endl;
	
			int i = 0;
			for (auto item : rules[currentState]) {
				cout << i++ << ". " << item.first << endl;
			}
	
			cin >> input;
			if (input < 0 || (input + 1) > rules[currentState].size())
				cout << "Incorrect option. Please try again.\n";
			else
				break;
		}

		currentState = rules[currentState][input].second;
	}

	cout << "We are done using the phone\n";

	return 0;
}













