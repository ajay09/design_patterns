/*
	Lets add a new class ConcreteProduct2
	And see how Factory method will help us create instances of different classes.
*/

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
/////////////////  ConcreteProduct2.h
/////////////////////////////////////
// #pragma once
#include <iostream>
class ConcreteProduct2 : public Product {
public:
	void Operation() override;
};


/////////////////////////////////////
/////////////////  ConcreteProduct2.cpp
/////////////////////////////////////
// #include "ConcreteProduct.h"
void ConcreteProduct2::Operation() {
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

	// This function will return instance of Product.
	// It has to virtual at least (you can make it pure virtual also if you don't wish to create instances of Creator.)
	virtual Product *Create() { return nullptr; } // This is the default implementation
};

/////////////////////////////////////
/////////////////  Creator.cpp
/////////////////////////////////////
// #include "Creator.h"
// #include "Product.h"
void Creator::AnOperation() {
	// m_pProduct = new ConcreteProduct{};
	// Instead of creating products like this we will use our Factory Method.
	m_pProduct = Create(); // 
	m_pProduct->Operation();
}


/////////////////////////////////////
/////////////////  ConcreteCreator.h
/////////////////////////////////////
// #pragma once
class ConcreteCreator : public Creator {
public:
	Product *Create() override;
};

/////////////////////////////////////
/////////////////  ConcreteCreator.cpp
/////////////////////////////////////
// #include "ConcreteCreator.h"
// #include "Product.h"
Product* ConcreteCreator::Create() {
	return new ConcreteProduct{};
}

// To get an instance of ConcreteProduct2 just add a new class
/////////////////////////////////////
/////////////////  ConcreteCreator2.h
/////////////////////////////////////
// #pragma once
class ConcreteCreator2 : public Creator {
public:
	Product *Create() override;
};

/////////////////////////////////////
/////////////////  ConcreteCreator2.cpp
/////////////////////////////////////
// #include "ConcreteCreator2.h"
// #include "Product.h"
Product* ConcreteCreator2::Create() {
	return new ConcreteProduct2{};
}

// client code

int main() {
	// since we need an instance of ConcreteProduct, we will create instance of
	// concrete creator.
	ConcreteCreator cct;
	cct.AnOperation();

	ConcreteCreator2 cct2;
	cct2.AnOperation();
	return 0;
}


/*
	This is fine.
	But what will happen if we want the creator to use a different Concrete Product?
	The problem here is that we have hardcoded the code that creates instance of Concrete Product
	If we wish to create an instance of a different Concrete Product, we will have to
	modify this code. But modifying existing code is a bad idea.

	So this is a situation where we would like to implement a Factory Method.

	Thus we can see above that the Create() method can return instance of any Product class.
	And even when we add new Product classes we can use the same Create() function to
	get their instances also, without modifying the existing code.
*/