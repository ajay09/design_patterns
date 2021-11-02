/*

	---------------		m_pState				---------------
	|   Context   |<>---------------------------|   State     |
	---------------								---------------
	| Request()   |                             | Handle()    |
	---------------                             ---------------
		m_pState->Handle();					         /_\
													  |
											__________|___________
											|		  		     |
								  --------------------    --------------------
								  |  ConcreteStateA  |    |  ConcreteStateA  |
								  --------------------    --------------------
								  | Handle()         |    | Handle()         |
								  --------------------    --------------------

	- The Context class is split into many classes.
	  The state remains with the Context classes.
	  But the state related behavior goes to ConcreteStateA and ConcreteStateB classes (State classes)

	- Instance of ConcreteStateA and ConcreteStateB classes are called objects for the state.



	Issue with the current implementation : 
	- We are not deleting the instances that are created on the heap by the Handle method.
	  This can be taked care of by using smart pointers or making these classes singleton.

	- 
*/



///////////////////////////////////////
////////////////////////  State.h
///////////////////////////////////////
class State {
public:
	// provides the behavior and returns the state to which context must transition.
	virtual State* Handle() = 0;
	virtual ~State() = default;
};

///////////////////////////////////////
////////////////////////  Context.h
///////////////////////////////////////
class Context {
	State *m_pState;
public:
	Context(State *pState) : m_pState{pState} {}
	
	void Request() {
		m_pState = m_pState->Handle();
	}
};





///////////////////////////////////////////
////////////////////////  ConcreteStateA.h
///////////////////////////////////////////
#include <iostream>
class ConcreteStateB;

class ConcreteStateA : public State {
public:
	State* Handle() override;
	
};


///////////////////////////////////////////
////////////////////////  ConcreteStateB.h
///////////////////////////////////////////
#include <iostream>

class ConcreteStateB : public State {
public:
	State* Handle() override;
	
};



State* ConcreteStateA::Handle() {
	std::cout << "[ConcreteStateA] State A behavior\n";
	return new ConcreteStateB{};
}


State* ConcreteStateB::Handle() {
	std::cout << "[ConcreteStateB] State B behavior\n";
	return new ConcreteStateA{};
}




int main() {
	ConcreteStateA stateA{};
	Context ctx{&stateA}; 	// assume that the state A is the default state.

	ctx.Request();
	ctx.Request();
	ctx.Request();

	return 0;
}




