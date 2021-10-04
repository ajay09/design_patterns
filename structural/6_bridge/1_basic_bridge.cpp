


////////////////////////////////////////
// ------------------------------------------  Implementation Hierarchy
////////////////////////////////////////


////////////////////////////////////////
///////////////////  Implementor.h
////////////////////////////////////////
class Implementor {
public:
	virtual void OperationImpl() = 0;
	virtual ~Implementor() = default;
};







////////////////////////////////////////////
///////////////////  ConcreteImplementorA.h
////////////////////////////////////////////
#include <iostream>

class ConcreteImplementorA : public Implementor {
public:
	void OperationImpl() override {
		std::cout << "[ConcreteImplementorA] Implementation invoked\n";
	}
};




////////////////////////////////////////////
///////////////////  ConcreteImplementorB.h
////////////////////////////////////////////
#include <iostream>

class ConcreteImplementorB : public Implementor {
public:
	void OperationImpl() override {
		std::cout << "[ConcreteImplementorB] Implementation invoked\n";
	}
};





////////////////////////////////////////
// ------------------------------------------  Abstraction Hierarchy
////////////////////////////////////////

// Abstraction base class will contain a pointer to the implementor.
////////////////////////////////////////
///////////////////  Abstraction.h
////////////////////////////////////////
class Abstraction {
protected:
	// we may need this in the child classes also thus make it protected.
	// alternatively we could use a getter method as well.
	Implementor *m_pImpl{};
public:
	explicit Abstraction(Implementor *impl)
		 : m_pImpl{impl} {

	}

	virtual void Operation() = 0;

	virtual ~Abstraction() = default;
};





////////////////////////////////////////
///////////////////  RefinedAbstraction.h
////////////////////////////////////////
class RefinedAbstraction : public Abstraction {
	using Abstraction::Abstraction;
public:
	void Operation() {
		std::cout << "[RefinedAbstraction] => ";
		m_pImpl->OperationImpl();
	}
};






////////////////////////////////////////
///////////////////  	 client
////////////////////////////////////////
int main() {
	ConcreteImplementorA impl;
	Abstraction *a = new RefinedAbstraction(&impl);

	a->Operation();

	ConcreteImplementorB impl2;
	Abstraction *b = new RefinedAbstraction(&impl2);

	b->Operation();

	return 0;
}

