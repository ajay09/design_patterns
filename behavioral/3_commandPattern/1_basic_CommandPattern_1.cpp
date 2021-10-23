/*

	                 --------------     m_pCmd   --------------
	                 |   Invoker  |<>----------->| Command    |
	                 --------------              --------------
	  								      	  	 | Execute()  |
	           						      	  	 --------------
	  								      		      /_\
	  								      		       |
	  								      		       |
									  	      	  ----------------
										          |   Receiver   |
										          ----------------
										          |  Action()    |
								            	  ----------------
								  						

	
	- The Receiver class has the methods that the Invoker has to invoke.

	- From the Invoke() we want to call the method Action()

	- The easy way would be to keep a pointer of Receiver in Invoker and call the Action method.
	   But this will create dependency between the Invoker and the Receiver. And Invoker will get
	   tightly coupled with the Receiver and it won't be able to call Action() of another kind of
	   Receiver.

	- Thus we use the Command Design Pattern.

	- The Invoker doesn't know the object that handles its request.
	  Thus at runtime we can change the receiver.
	  The Invoker is not directly coupled with its receivers.
*/

///////////////////////////////////////////////////////
////////////////////////////// 		Command.h
///////////////////////////////////////////////////////
class Command {
public:
	virtual void Execute() = 0;
};



///////////////////////////////////////////////////////
////////////////////////////// 		Receiver.h
///////////////////////////////////////////////////////
#include <iostream>

class Receiver : public Command {
public:
	void Action() {
		std::cout << "[Receiver] Action performed.\n";
	}

	void Execute() override {
		Action();
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
	Invoker inv;

	inv.SetCommand(&rec); // set command using any class that implements the command interface
	                      // here the receiver implements the command interface.

	inv.Invoke();

	return 0;
}




