/////////////////////////////////////
/////////////////  Product.h
/////////////////////////////////////
// #pragma once
class Product {
public:
	virtual void Operation() = 0; // pure virtual function => need a virtual destructor as well
	virtual ~Product() = default;
};

/////////////////////////////////////
/////////////////  ConcreteProduct.h
/////////////////////////////////////
// #pragma once
#include <iostream>
class ConcreteProduct : public Product {
public:
	void Operation() override;
};


/////////////////////////////////////
/////////////////  ConcreteProduct.cpp
/////////////////////////////////////
// #include "ConcreteProduct.h"
void ConcreteProduct::Operation() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

/////////////////////////////////////
/////////////////  Creator.h
/////////////////////////////////////
// #pragma once
class Creator {
	Product *m_pProduct;
public:
	// This will create an instance of concrete product.
	void AnOperation();
};

/////////////////////////////////////
/////////////////  Creator.cpp
/////////////////////////////////////
void Creator::AnOperation() {
	m_pProduct = new ConcreteProduct{}; // this is tight coupling
	m_pProduct->Operation();
}


// client code

int main() {
	Creator ct;
	ct.AnOperation();
	return 0;
}


/*
	This is fine.
	But what will happen if we want the creator to use a different Concrete Product?
	The problem here is that we have hardcoded the code that creates instance of Concrete Product
	If we wish to create an instance of a different Concrete Product, we will have to
	modify this code. But modifying existing code is a bad idea.

	So this is a situation where we would like to implement a Factory Method
*/