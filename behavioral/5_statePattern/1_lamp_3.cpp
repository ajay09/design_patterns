/*
	Lamp using the State Desing Pattern

	- Use the state pattern instead of managing the state through enums.

	- We need to create classes to represent the behavior of each state.
	  Thus we need to convert the enum members into classes.
	  State class will be the base class and OnState and OFfState will 
	  represent the two behaviors.



			Context
			------------							   -------------
			|   Lamp   |---------m_pState------------->|   State   |
			------------  							   ------------- 
															/_\
															 |
												   __________|___________
												   |					|
											-------------          -------------
											|  OnState  |          |  OffState |
											-------------          -------------
                                                    Object for States

	Benefits of State Design Patter :
	- Switch cases are now gone.
	- Transitions are handled by the state class only.

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





////////////////////////////////////////////////////
////////////////////////////  Lamp.h
////////////////////////////////////////////////////
#include <iostream>

class Lamp {
	State *m_pState;

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

	~Lamp() {
		delete pState;
	}

	// invoked when state has to be changed.
	void SetState(State *pState) {
		delete pState
		m_pState = pState;
	}

	// provide access to lamp image. (read only access)
	const char* GetOnLamp() {
		return m_LampOn;
	}

	const char* GetOffLamp() {
		return m_LampOff;
	}

	void SwitchOn() {
		m_pState->SwitchOn(this);
	}

	void SwitchOff() {
		m_pState->SwitchOff(this);
	}
};






//////////////////////////////////////
//////////////////////   OnState.h
//////////////////////////////////////
class OnState : public State {
public:
	void SwitchOn(Lamp *pLamp) override {
		std::cout << "Lamp is already On\n";
	}

	void SwitchOff(Lamp *pLamp) override;

};





//////////////////////////////////////
//////////////////////   OffState.h
//////////////////////////////////////
class OffState : public State {
public:
	void SwitchOn(Lamp *pLamp) override;

	void SwitchOff(Lamp *pLamp) override {
		std::cout << "Lamp is already Off\n";
	}

};


void OnState::SwitchOff(Lamp *pLamp) {
	system("clear");
	std::cout << pLamp->GetOffLamp() << std::endl;
	std::cout << "Turned Off\n";
	pLamp->SetState(new OffState{});
}

void OffState::SwitchOn(Lamp *pLamp) {
	system("clear");
	std::cout << pLamp->GetOnLamp() << std::endl;
	std::cout << "Turned On\n";
	pLamp->SetState(new OnState{});
}

Lamp::Lamp() : m_pState{new OffState{}} {}

int main() {
	Lamp lamp;
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















