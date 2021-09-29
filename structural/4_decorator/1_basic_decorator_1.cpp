/*
	Decorator Pattern
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


// Lets implement the concrete decorator directly
// to understand the importance of defining a Decorator base class.
////////////////////////////////////
////////////  ConcreteDecoratorA.h
////////////////////////////////////
class ConcreteDecoratorA : public Component {
	Component *m_ptr{};
public:
	ConcreteDecoratorA(Component *cmp) : m_ptr{cmp} {}
	void Operation() override {
		std::cout << "[ConcreteDecoratorA] Operation invoked\n";
		m_ptr->Operation();
	}
};


////////////////////////////////////
////////////  ConcreteDecoratorB.h
////////////////////////////////////
class ConcreteDecoratorB : public Component {
	Component *m_ptr{};
public:
	ConcreteDecoratorB(Component *cmp) : m_ptr{cmp} {}
	void Operation() override {
		std::cout << "[ConcreteDecoratorB] Operation invoked\n";
		m_ptr->Operation();
	}
};



int main() {
	ConcreteComponent component{};
	ConcreteDecoratorA decA{&component};
	decA.Operation();
	
	std::cout << std::endl;

	ConcreteDecoratorB decB{&decA};
	decB.Operation();
	return 0;
}




