 /*

	- Instead of the Receiver implementing the Command interface we can
	  create a new class which will implement the Command interface.

	- In this way we can store the state before invoking the actual
	  action in the receiver.

	                 --------------     m_pCmd   --------------
	                 |   Invoker  |<>----------->| Command    |
	                 --------------              --------------
	  								      	  	 | Execute()  |
	           						      	  	 --------------
	  								      		      /_\
	  								      		       |
	  								      		       |
				----------------   m_pRec	 -----------------------
				|   Receiver   |<------------|   ConcreteCommand   |
				----------------		     -----------------------
				|  Action()    |		     |   Execute()    	   |
				----------------             -----------------------
								  						

	
	
*/
///////////////////////////////////////////////////////
////////////////////////////// 		Receiver.h
///////////////////////////////////////////////////////
#include <iostream>

class Receiver {
public:
	void Action() {
		std::cout << "[Receiver] Action performed.\n";
	}
};



///////////////////////////////////////////////////////
////////////////////////////// 		Command.h
///////////////////////////////////////////////////////
class Command {
public:
	virtual void Execute() = 0;
};


// The ConcreteCommand class can store the state before 
// action is performed.
///////////////////////////////////////////////////////
////////////////////////////// 		ConcreteCommand.h
///////////////////////////////////////////////////////
class ConcreteCommand : public Command {
	Receiver *m_pRec;
public:
	ConcreteCommand(Receiver *mPRec) : m_pRec{mPRec} {
	}

	void Execute() override {
		m_pRec->Action();
	}
};







///////////////////////////////////////////////////////
////////////////////////////// 		Invoker.h
///////////////////////////////////////////////////////
class Invoker {
	Command *m_pCommand;
public:
	// From the Invoke() we want to call the method Action()
	void Invoke() {
		m_pCommand->Execute();
	}

	void SetCommand(Command *pCmd) {
		m_pCommand = pCmd;
	}
};









int main() {
	Receiver rec;
	ConcreteCommand cmd{&rec};
	Invoker inv;

	inv.SetCommand(&cmd); // set command using any class that implements the command interface
	                      // here the ConcreteCommand implements the command interface.

	inv.Invoke();

	return 0;
}




