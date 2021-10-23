/*
	Basic implementation of the Template Method design pattern
*/

//////////////////////////////////////////
////////////////////////  AbstractClass.h
//////////////////////////////////////////
class AbstractClass {
protected:
	// Protected so that client might not call the Primitive opertions directly.
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;
	virtual void PrimitiveOperation3();
	void PrimitiveOperation4();
public:
	void TemplateMethod();

	virtual ~AbstractClass() = default;
};



//////////////////////////////////////////
//////////////////////// AbstractClass.cpp
//////////////////////////////////////////
#include <iostream>

void AbstractClass::PrimitiveOperation3() {
	std::cout << "Optional step\n";
}

void AbstractClass::PrimitiveOperation4() {
	std::cout << "Fixed step\n";	
}

void AbstractClass::TemplateMethod() {
	// Varying Steps
	PrimitiveOperation1();
	PrimitiveOperation2();

	// Optional vary step (hook)
	PrimitiveOperation3();

	// Fixed step
	PrimitiveOperation4();
}



//////////////////////////////////////////
////////////////////////  ConcreteClass.h
//////////////////////////////////////////
#include <iostream>

class ConcreteClass : public AbstractClass {
public:
	void PrimitiveOperation1() override {
		std::cout << "Compulsory override step1\n";
	}

	void PrimitiveOperation2() override {
		std::cout << "Compulsory override step2\n";
	}

	void PrimitiveOperation3() override {
		AbstractClass::PrimitiveOperation3();
		std::cout << "Optional step override\n";
	}
};







///////////////////////////////////////
//////////////// Client.cpp
///////////////////////////////////////
int main() {
	ConcreteClass cc;

	cc.TemplateMethod();

	return 0;
}



















