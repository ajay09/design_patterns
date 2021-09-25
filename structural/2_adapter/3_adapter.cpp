/*
	The client uses the Target
	But it wants to invoke the functionality of Adaptee.
	But Adaptee has a different interface.

	So we will create a wrapper class that will have the same interface as Target
	but it will internally use the functionality of Adaptee.
*/

////////////////////////////////////////
////////////////////  Target.h
////////////////////////////////////////
class Target {
public:
	virtual void Request() = 0;
	virtual ~Target() = default;
};


////////////////////////////////////////
////////////////////  Adaptee.h
////////////////////////////////////////
#include <iostream>

class Adaptee {
public:
	void SpecificRequest() {
		std::cout << "[Adaptee] SpecificRequest" << std::endl;
	}
};



//             1. Object Adapter
////////////////////////////////////////
////////////////////  Adapter.h
////////////////////////////////////////
class Adapter : public Target {
	// compose an instance of Adaptee
	Adaptee m_Adaptee;
public:
	void Request() override {
		std::cout << "[Adapter] Calling SpecificRequest\n";
		m_Adaptee.SpecificRequest();
	}
};



//             2. Class Adapter
////////////////////////////////////////
////////////////////  Adapter2.h
////////////////////////////////////////
class Adapter2 : public Target, public Adaptee {
public:
	void Request() override {
		std::cout << "[Adapter2] Calling SpecificRequest\n";
		SpecificRequest();
	}
};





void client(Target *pTarget) {
	pTarget->Request();
}

int main() {
	Adapter a;
	client(&a);

	Adapter2 a2;
	client(&a2);
	return 0;
}