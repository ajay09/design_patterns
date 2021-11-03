/*
	Another way of implementing the State Design Pattern is using the Transition tables.

		- The transition table maps the inputs to state transitions.
		  The input is the State and the action invoked.
		  The table maps it to the succeeding state and the operation to execute.

		- Thus transition tablet converts the virtual function mechanism into table look-up.

		Current State    | 	Event    |  	 Action	   |   	  Next State
		---------------- | --------- |  -------------  | -----------------------
		off_state		 | SwitchOff |  No action      | 		off_state			
						 | 			 |  		       | 					
		off_state		 | SwitchOn  |  Switch on lamp | 		on_state			
						 | 			 |  			   | 					
		on_state		 | SwitchOn  |  No action      | 		on_state			
						 | 			 |  		       | 					
		on_state		 | SwitchOff | Switch off lamp | 		off_state	

	
	Now let's implement the Lamp using the state-transition table.

*/


//////////////////////////////////////
//////////////////////   State.h
//////////////////////////////////////
class Lamp;

class State {
public:
	virtual void SwitchOn(Lamp *pLamp) = 0;
	virtual void SwitchOff(Lamp *pLamp) = 0;

	virtual ~State() = default;
};







//////////////////////////////////////
//////////////////////   OnState.h
//////////////////////////////////////
class OnState : public State {
public:
	void SwitchOn(Lamp *pLamp) override;

	void SwitchOff(Lamp *pLamp) override;

};


//////////////////////////////////////
//////////////////////   YellowState.h
//////////////////////////////////////
class YellowState : public State {
public:
	void SwitchOn(Lamp *pLamp) override;

	void SwitchOff(Lamp *pLamp) override;

};





//////////////////////////////////////
//////////////////////   OffState.h
//////////////////////////////////////
class OffState : public State {
public:
	void SwitchOn(Lamp *pLamp) override;

	void SwitchOff(Lamp *pLamp) override;
};





///////////////////////////////////////
//////////////////// TransitionTable.h
///////////////////////////////////////
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <string>

using ActionInfo = std::tuple<std::string, State*>;

class TransitionTable {
	std::unordered_map<State*, std::vector<ActionInfo>> m_Table;
	State *m_DefaultState;
public:
	TransitionTable() {
		m_DefaultState = new OffState{};
		auto offState = m_DefaultState;
		auto onState = new OnState{};
		auto yellowState = new YellowState{};

		// transition table consits of 
		// key    event    action    next_state
		// but the action will be automatically performed by the state.
		// Thus the table here only requires  key, event, next_state.

		m_Table[offState].push_back(std::make_tuple("SwitchOff", offState));
		m_Table[offState].push_back(std::make_tuple("SwitchOn", onState));

		m_Table[onState] = {
			std::make_tuple("SwitchOff", offState),
			std::make_tuple("SwitchOn", yellowState)
		};

		m_Table[yellowState].push_back(std::make_tuple("SwitchOff", offState));
		m_Table[yellowState].push_back(std::make_tuple("SwitchOn", onState));
	}

	State* GetDefaultState() {
		return m_DefaultState;
	}

	~TransitionTable() {
		for (auto state : m_Table) {
			delete state.first;
		}
	}

	State* DoTransition(State *currentState, const std::string &event) {
		auto &vec_action = m_Table[currentState];
		auto found = std::find_if(begin(vec_action), 
				    			   end(vec_action), 
				    			   [&event](const ActionInfo& entry) {
				    			   		return event == std::get<0>(entry);
				    			   });

		if (found == vec_action.end()) {
			throw std::runtime_error{"Invalid transition."};
		}
		return std::get<1>(*found);
	}
};


////////////////////////////////////////////////////
////////////////////////////  Lamp.h
////////////////////////////////////////////////////
#include <iostream>

// class TransitionTable;

class Lamp {
	State *m_pState;
	TransitionTable m_Table;

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

	// invoked when state has to be changed.
	void SetState(State *pState) {
		m_pState = pState;
	}

	// provide access to lamp image. (read only access)
	const char* GetOnLamp() {
		return m_LampOn;
	}

	const char* GetYellowLamp() {
		return m_LampYellow;
	}

	const char* GetOffLamp() {
		return m_LampOff;
	}

	void SwitchOn();

	void SwitchOff();
};



Lamp::Lamp() {
	m_pState = m_Table.GetDefaultState();
}

void Lamp::SwitchOn() {
	system("clear");
	m_pState->SwitchOn(this);
	m_pState = m_Table.DoTransition(m_pState, "SwitchOn");
}

void Lamp::SwitchOff() {
	system("clear");
	m_pState->SwitchOff(this);
	m_pState = m_Table.DoTransition(m_pState, "SwitchOff");
}




void OnState::SwitchOff(Lamp *pLamp) {
	std::cout << pLamp->GetOffLamp() << std::endl;
	std::cout << "Turned Off\n";
}

void OnState::SwitchOn(Lamp *pLamp) {
	std::cout << pLamp->GetYellowLamp() << std::endl;
	std::cout << "Turned On Yellow\n";
}




void YellowState::SwitchOn(Lamp *pLamp) {
	std::cout << pLamp->GetOnLamp() << std::endl;
	std::cout << "Turned On White\n";
}

void YellowState::SwitchOff(Lamp *pLamp) {
	std::cout << pLamp->GetOffLamp() << std::endl;
	std::cout << "Turned Off\n";
}




void OffState::SwitchOn(Lamp *pLamp) {
	std::cout << pLamp->GetOnLamp() << std::endl;
	std::cout << "Turned On\n";
}

void OffState::SwitchOff(Lamp *pLamp) {
	std::cout << "Already Off\n";
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