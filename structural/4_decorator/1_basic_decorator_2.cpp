/*
	Decorator Pattern

	When we added the Concreate Decorator's, I had to manually create a pointer of component

and then forward the call to the next component.

To avoid doing that, we can create an abstract Decorator class here.
*/

////////////////////////////////////
////////////  Component.h
////////////////////////////////////

class Component {
public:
	virtual void Operation() = 0;
	~Component() = default;
};


////////////////////////////////////
////////////  ConcreteComponent.h
////////////////////////////////////
#include <iostream>

class ConcreteComponent : public Component {
public:
	void Operation() override {
		std::cout << "[ConcreteComponent] Operation invoked\n";
	}
};


// You are allowed to define any pure virtual member function. 
// However, even though you define Component::Operation, it is still pure, 
// so Component and Decorator are still abstract classes and may not be instantiated.
////////////////////////////////////
////////////  Decorator.h
////////////////////////////////////
class Decorator : public Component {
	Component *m_ptr{};
public:
	Decorator(Component *ptr) : m_ptr{ptr} {}

	virtual void Operation() override = 0;
};


void Decorator::Operation() {
	// std::cout << "[Decorator] Operation invoked\n";
	m_ptr->Operation();
}	


////////////////////////////////////
////////////  ConcreteDecoratorA.h
////////////////////////////////////
class ConcreteDecoratorA : public Decorator {
public:
	using Decorator::Decorator;

	void Operation() override {
		std::cout << "[ConcreteDecoratorA] Operation invoked\n";
		Decorator::Operation();
	}
};


////////////////////////////////////
////////////  ConcreteDecoratorB.h
////////////////////////////////////
class ConcreteDecoratorB : public Decorator {
public:
	using Decorator::Decorator;

	void Operation() override {
		std::cout << "[ConcreteDecoratorB] Operation invoked\n";
		Decorator::Operation();
	}

	void OtherOperations() {
		std::cout << "[ConcreteDecoratorB] Supporting operations\n";
	}
};


void Operate(Component *c) {
	c->Operation();
}


int main() {
	ConcreteComponent component{};
	ConcreteDecoratorA decA{&component};
	decA.Operation();
	
	std::cout << std::endl;

	ConcreteDecoratorB decB{&decA};
	decB.Operation();

	std::cout << std::endl;

	decB.OtherOperations();
	return 0;
}




