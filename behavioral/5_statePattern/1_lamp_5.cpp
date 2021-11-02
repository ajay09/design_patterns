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



					Add one more state to the lamp and see what changes have to make!


	- Yellow State : 
			State-ON  <----Switch-On------> State-Yellow
		   /|\    | 							  |
			|     |								  |
		switch-on |								  |								
			|     |								  |
			|   Switch-off						  |			
			|     |								  |	
			|    \|/							  |		
			State-Off  <--------switch-off--------^


	Issue :
		Tight coupling between the state classes.
		The header of one state class is included in all the other state-class implementation file.
		If one of the state class is modified then other state class may also be impacted.


		Cause of Dependency =>  The new opearator used inside  pLamp->SetState
								When we create an object using the new operator we have to use the name of
								the class, this causes a dependency on that name.

								To reduce this dependency we can replace the new method with the Factory Method.
																								 (Parameterized Factory.)


	Still one issue :
			Repetitive construction and destruction of objects, might lead to fragmentation of the heap.
			And will affect the performance of the applicaiton over time.

			Solution : Since the state classes here don't carry any state.
					   Thus we can make them Singleton.

					   Thus the factory need not create a new instance everytime and the
					   factory can behave like a registry of Singletons.

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

	~Lamp() {
		delete m_pState;
	}

	// invoked when state has to be changed.
	void SetState(State *pState) {
		delete m_pState;
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

	void SwitchOff(Lamp *pLamp) override {
		std::cout << "Lamp is already Off\n";
	}

};


////////////////////////////////////
////////////////////  StateFactory.h
////////////////////////////////////
#include <string>

// You can use enum to represent the type of the State.
// But if you use enum and a new state is added, then you'll
// have to modify the enum type and add a new member.
// This may cause a recompilation in all the other files.
// Thus using string will prevent that recompilation.

class StateFactory {
public:
	static State* GetState(const std::string &stateType) {
		if (stateType == "ON_STATE") {
			return new OnState{};
		} else if (stateType == "YELLOW_STATE") {
			return new YellowState{};
		} else if (stateType == "OFF_STATE") {
			return new OffState{};
		}
		return nullptr;
	}
};


void OnState::SwitchOff(Lamp *pLamp) {
	system("clear");
	std::cout << pLamp->GetOffLamp() << std::endl;
	std::cout << "Turned Off\n";m
	pLamp->SetState(StateFactory::GetState("OFF_STATE"));
}

void OnState::SwitchOn(Lamp *pLamp) {
	system("clear");
	std::cout << pLamp->GetYellowLamp() << std::endl;
	std::cout << "Turned On Yellow\n";
	pLamp->SetState(StateFactory::GetState("YELLOW_STATE"));
}

void YellowState::SwitchOn(Lamp *pLamp) {
	system("clear");
	std::cout << pLamp->GetOnLamp() << std::endl;
	std::cout << "Turned On White\n";
	pLamp->SetState(StateFactory::GetState("ON_STATE"));
}

void YellowState::SwitchOff(Lamp *pLamp) {
	system("clear");
	std::cout << pLamp->GetOffLamp() << std::endl;
	std::cout << "Turned Off\n";
	pLamp->SetState(StateFactory::GetState("OFF_STATE"));
}


void OffState::SwitchOn(Lamp *pLamp) {
	system("clear");
	std::cout << pLamp->GetOnLamp() << std::endl;
	std::cout << "Turned On\n";
	pLamp->SetState(StateFactory::GetState("ON_STATE"));
}

Lamp::Lamp() : m_pState{new OffState{}} {}

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















