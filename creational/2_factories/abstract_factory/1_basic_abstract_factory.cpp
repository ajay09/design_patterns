////////////////////////////////////
////////////////  AbstractProductA.h
////////////////////////////////////
// #pragma once
class AbstractProductA {
public:
	virtual void ProductA() = 0;
	virtual ~AbstractProductA() = default;
};


////////////////////////////////////
////////////////  AbstractProductB.h
////////////////////////////////////
// #pragma once
class AbstractProductB {
public:
	virtual void ProductB() = 0;
	virtual ~AbstractProductB() = default;
};


////////////////////////////////////
////////////////  Set1.h
////////////////  Variation of Products for Set1
////////////////////////////////////
// #pragma once
#include <iostream>

class ProductA1 : public AbstractProductA {
public:
	void ProductA() override {
		std::cout << "[1] Product A\n";
	}
};

class ProductB1 : public AbstractProductB {
public:
	void ProductB() override {
		std::cout << "[1] Product B\n";
	}
};


////////////////////////////////////
////////////////  Set2.h
////////////////  Variation of Products for Set2
////////////////////////////////////
// #pragma once
#include <iostream>

class ProductA2 : public AbstractProductA {
public:
	void ProductA() override {
		std::cout << "[2] Product A\n";
	}
};

class ProductB2 : public AbstractProductB {
public:
	void ProductB() override {
		std::cout << "[2] Product B\n";
	}
};



int main() {
	AbstractProductA *pA = new ProductA1{};
	AbstractProductB *pB = new ProductB1{};

	pA->ProductA();
	pB->ProductB();

	delete pA;
	delete pB;
	return 0;
}
