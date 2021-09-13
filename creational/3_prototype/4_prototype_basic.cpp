//////////////////////////////////////////
/////////////////////  Prototype.h
//////////////////////////////////////////
// #pragma once

class Prototype {
public:
	virtual Prototype *Clone() = 0;
	virtual ~Prototype() = default;

	virtual void DoSomething() = 0;
};


//////////////////////////////////////////
/////////////////////  ConcretePrototype1.h
//////////////////////////////////////////
// #pragma once
#include <iostream>

class ConcretePrototype1 : public Prototype {
public:
	// covariant return type
	ConcretePrototype1 *Clone() override {
		std::cout << "[ConcretePrototype1] A clone has been created.\n";
		return new ConcretePrototype1(*this); // this will use the default copy-constructor.
		                                     // currently we are not dealing with shallow and deep copy.
	}
	void DoSomething() override {}
};


//////////////////////////////////////////
/////////////////////  ConcretePrototype2.h
//////////////////////////////////////////
// #pragma once

class ConcretePrototype2 : public Prototype {
public:
	// covariant return type
	ConcretePrototype2 *Clone() override {
		std::cout << "[ConcretePrototype2] A clone has been created.\n";
		return new ConcretePrototype2(*this);
	}
	void DoSomething() override {}
};


//////////////////////////////////////////
/////////////////////  Client.h
//////////////////////////////////////////
// #pragma once
class Client {
	Prototype *prototype;
public:
	void SetPrototype(Prototype *p) {
		prototype = p;
	}
	// An operation where the clone will be created.
	void Operation() {
		auto p = prototype->Clone();
		// if DoSomething is not a virtual function.
		// (static_cast<ConcretePrototype2*>(p))->DoSomething();
		p->DoSomething();
	}
};



int main() {
	Client c;
	c.SetPrototype(new ConcretePrototype2);
	c.Operation();
	return 0;
}