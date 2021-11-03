/*
	Methods for States.

	- Forgoing manual memory management

*/


///////////////////////////////////////
//////////////////// TransitionTable.h
///////////////////////////////////////
#include <map>
#include <vector>
#include <stdexcept>
#include <string>
#include <functional>
#include <iostream>

using StateInfo = std::pair<std::string, std::string>; // current_state and event
using ActionInfo = std::pair<std::function<void()>, std::string>; // action and the next_state
							// we can use a lamda funciton, a function pointer,
							// or a member funciton as a callback here.	

class TransitionTable {
	std::map<StateInfo, ActionInfo> m_Table;
public:
	const std::string& DoTransition(const std::string& currentState, const std::string &event) {
		auto &action = m_Table[std::make_pair(currentState, event)];
		
		if (action.first) // using the bool operator of std::function
			action.first();
		else
			std::cout << "Nothing to do\n";

		return action.second;
	}

	void AddEntry(const StateInfo &stateInfo, const ActionInfo &actionInfo) {
		m_Table.insert(std::make_pair(stateInfo, actionInfo));
	}
};


////////////////////////////////////////////////////
////////////////////////////  Lamp.h
////////////////////////////////////////////////////
#include <iostream>

// class TransitionTable;

class Lamp {
	TransitionTable m_Table;
	std::string m_CurrentState;
	struct LampImpl;
	std::unique_ptr<LampImpl> m_pImpl;

	const char *m_LampOn = 
R"(
         |
 \     _____     /
     /       \
    (         )
-   ( ))))))) )   -
     \ \   / /
      \|___|/
  /    |___|    \
       |___| 
       |___|
)";


	const char *m_LampYellow = 
R"(
         |
 \     _____     /
     /       \
    (         )
-   ( ))))))) )   -  Yellow
     \ \   / /
      \|___|/
  /    |___|    \
       |___| 
       |___|
)";

	const char *m_LampOff = 
R"(
          
       _____      
     /       \
    (         )
    ( ))))))) )    
     \ \   / /
      \|___|/
       |___|     
       |___| 
       |___|
)";

public:
	// default state is off
	Lamp();

	~Lamp();

	void SwitchOn();

	void SwitchOff();
};

// use struct as we want all it methods to be public
// This class will provide the behavior of the states.
struct Lamp::LampImpl {
	void SwitchOn(Lamp *pLamp) {
		std::cout << pLamp->m_LampOn << std::endl;
	}
	void SwitchOff(Lamp *pLamp) {
		std::cout << pLamp->m_LampOff << std::endl;
	}
	void SwitchYellow(Lamp *pLamp) {
		std::cout << pLamp->m_LampYellow << std::endl;
	}
};



Lamp::Lamp() : m_CurrentState{"off_state"}, m_pImpl{new LampImpl{}} {
	auto on_action = std::bind(&LampImpl::SwitchOn, m_pImpl.get(), this);
	auto off_action = std::bind(&LampImpl::SwitchOff, m_pImpl.get(), this);
	auto yellow_action = std::bind(&LampImpl::SwitchYellow, m_pImpl.get(), this);
	m_Table.AddEntry(
		std::make_pair("off_state", "SwitchOff"), // StateInfo [current_state, event]
		std::make_pair(nullptr, "off_state")  // ActionInfo [action, next_state]
	);

	m_Table.AddEntry(
		std::make_pair("off_state", "SwitchOn"),
		std::make_pair(on_action, "on_state")  // if we directly pass &LampImpl::SwitchOn it won't work because in reality it has 2 parameters.
	);

	m_Table.AddEntry(
		std::make_pair("on_state", "SwitchOff"),
		std::make_pair(off_action, "off_state")
	);

	m_Table.AddEntry(
		std::make_pair("on_state", "SwitchOn"),
		std::make_pair(yellow_action, "yellow_state")
	);

	m_Table.AddEntry(
		std::make_pair("yellow_state", "SwitchOff"),
		std::make_pair(off_action, "off_state")
	);

	m_Table.AddEntry(
		std::make_pair("yellow_state", "SwitchOn"),
		std::make_pair(on_action, "on_state")
	);
}

Lamp::~Lamp() = default;
// because the lamp destructor will call the deleter of the smart pointer and if we don't define it here (i.e. after defining LampImpl)
// then it might complain of incomplete type for LampImpl.

void Lamp::SwitchOn() {
	system("clear");
								  // current_state,  event
	m_CurrentState = m_Table.DoTransition(m_CurrentState, "SwitchOn");
}

void Lamp::SwitchOff() {
	system("clear");
	m_CurrentState = m_Table.DoTransition(m_CurrentState, "SwitchOff");
}




int main() {
	Lamp lamp;
	lamp.SwitchOn();
	getchar();
	lamp.SwitchOn();
	getchar();
	lamp.SwitchOn();
	getchar();
	lamp.SwitchOff();
	getchar();
	lamp.SwitchOff();
	getchar();
	return 0;

}





