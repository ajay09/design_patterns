/*
*/


///////////////////////////////////
//////////////		Strategy.h
///////////////////////////////////
class Strategy {
public:
	virtual void AlgorithmInterface() = 0;
	virtual ~Strategy() = default;
};




///////////////////////////////////
//////////////		Context.h
///////////////////////////////////
#include <iostream>

class Context {
	Strategy *m_pStrategy;
public:
	void ContextInterface() {
		if (m_pStrategy) {
			m_pStrategy->AlgorithmInterface();
		}
		else {
			std::cout << "Default behavior\n";
		}
	}

	// You can set the Strategy using a setter function or using a constructor
	// depending on the situation.
	void SetStrategy(Strategy *p) {
		m_pStrategy = p;
	}
};



////////////////////////////////////////
//////////////		ConcreteStrategyA.h
///////////////////////////////////////
class ConcreteStrategyA : public Strategy {
public:
	void AlgorithmInterface() {
		std::cout << "[ConcreteStrategyA]\n";
	}
};


////////////////////////////////////////
//////////////		ConcreteStrategyB.h
///////////////////////////////////////
class ConcreteStrategyB : public Strategy {
public:
	void AlgorithmInterface() {
		std::cout << "[ConcreteStrategyB]\n";
	}
};




////////////////////////////////////////
//////////////		ConcreteStrategyC.h
///////////////////////////////////////
class ConcreteStrategyC : public Strategy {
public:
	void AlgorithmInterface() {
		std::cout << "[ConcreteStrategyC]\n";
	}
};




int main() {
	Context c{};

	c.ContextInterface();

	ConcreteStrategyA sA;
	c.SetStrategy(&sA);

	c.ContextInterface();
	return 0;
}



