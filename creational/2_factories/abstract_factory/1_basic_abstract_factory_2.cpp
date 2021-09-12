/*
	Now we will design an Abstract Factory for the example.
*/


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



////////////////////////////////////
////////////////  AbstractFactory.h
////////////////  Base class to define the interfaces for creating the products
////////////////////////////////////
// #pragma once
class AbstractFactory {
public:
	virtual AbstractProductA* CreateProductA() = 0;
	virtual AbstractProductB* CreateProductB() = 0;
	virtual ~AbstractFactory() = default;
};


////////////////////////////////////
////////////////  ConcreteFactory1.h
////////////////////////////////////
// #pragma once
class ConcreteFactory1 : public AbstractFactory{
public:
	AbstractProductA* CreateProductA() override;
	AbstractProductB* CreateProductB() override;
};

////////////////////////////////////
////////////////  ConcreteFactory1.cpp
////////////////////////////////////

AbstractProductA* ConcreteFactory1::CreateProductA() {
	return new ProductA1{};
}

AbstractProductB* ConcreteFactory1::CreateProductB() {
	return new ProductB1{};
}



////////////////////////////////////
////////////////  ConcreteFactory2.h
////////////////////////////////////
// #pragma once
class ConcreteFactory2 : public AbstractFactory{
public:
	AbstractProductA* CreateProductA() override;
	AbstractProductB* CreateProductB() override;
};

////////////////////////////////////
////////////////  ConcreteFactory2.cpp
////////////////////////////////////

AbstractProductA* ConcreteFactory2::CreateProductA() {
	return new ProductA2{};
}

AbstractProductB* ConcreteFactory2::CreateProductB() {
	return new ProductB2{};
}





////////////////////////////////////
////////////////  client.cpp
////////////////////////////////////

void UsePattern(AbstractFactory *pFactory) {
	AbstractProductA *pA = pFactory->CreateProductA();
	AbstractProductB *pB = pFactory->CreateProductB();

	pA->ProductA();
	pB->ProductB();

	delete pA;
	delete pB;
}


int main() {
	AbstractFactory *pFactory = new ConcreteFactory1{};
	UsePattern(pFactory);
	delete pFactory;

	pFactory = new ConcreteFactory2{};
	UsePattern(pFactory);
	delete pFactory;

	return 0;
}
