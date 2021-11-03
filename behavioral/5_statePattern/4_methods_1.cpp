/*
	- Another vairation of the State pattern for the table based approach is the "Methods for States".

	- It doesn't use objects for state behavior.

	- Behavior is realized as internal functions within a single object, usually the Context.

	- These functions are grouped together using function pointers in a table to provide
	   behavior.

	- The table created a mapping between the state and these functions. 

	- The state is represented using some value, enum, integer, or string.
	   (instead of an object.)

	- This appraoch works with non OO Languages also.
*/


///////////////////////////////////////
//////////////////// TransitionTable.h
///////////////////////////////////////
/*
	Why use map here instead of unordered_map?
	- Key for an unordered_map must support == and hashing.
	- Pair overloads == operator but doesn't support hashing.
	- We can implement our own hash funciton for the pair and provide it to the unordered map
	- To avoid doing that we can use Map.
	- In Map the key only needs to support the relational operators < or >
	  And Pair already supports that.
*/
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
	LampImpl *m_pImpl;

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


// 	const char *m_LampYellow = 
// R"(
//          |
//  \     _____     /
//      /       \
//     (         )
// -   ( ))))))) )   -  Yellow
//      \ \   / /
//       \|___|/
//   /    |___|    \
//        |___| 
//        |___|
// )";

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
};



Lamp::Lamp() : m_CurrentState{"off_state"}, m_pImpl{new LampImpl{}} {
	auto on_action = std::bind(&LampImpl::SwitchOn, m_pImpl, this);
	auto off_action = std::bind(&LampImpl::SwitchOff, m_pImpl, this);
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
		std::make_pair(nullptr, "on_state")
	);
}

Lamp::~Lamp() {
	delete m_pImpl;
}

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





