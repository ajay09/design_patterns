////////////////////////////////////////////////////////
///////////////////////  Builder.h
////////////////////////////////////////////////////////
class Builder {
public:
	virtual void BuildPart() = 0;
	virtual ~Builder = default;
};

////////////////////////////////////////////////////////
///////////////////////  ConcreteBuilder.h
////////////////////////////////////////////////////////
#include <iostream>
class Product;
class ConcreteBuilder : public Builder{
	Product *m_pProduct;
public:
	ConcreteBuilder() {
		std::cout << "[ConcreteBuilder] Created\n";
	}
	void BuildPart() override {
		std::cout << "[ConcreteBuilder] Building...\n";
		std::cout << "\t Part A\n";
		std::cout << "\t Part B\n";
		std::cout << "\t Part C\n";
	}

	Product* GetResult() {
		std::cout << "[ConcreteBuilder] Returning result\n";
		rerturn product;
	}
};


////////////////////////////////////////////////////////
///////////////////////  Product.h
///////////////////////  The class whose construction process is complex.
///////////////////////  or we may to create different instances of class with different states.
////////////////////////////////////////////////////////

class Product {
};


////////////////////////////////////////////////////////
///////////////////////  Director.h
///////////////////////  The director will use the Builder to construct the object in
///////////////////////  steps.
////////////////////////////////////////////////////////
class Director {
	Builder *builder;
public:
	Director(Builder *builder) : builder{builder} {}
	
	void Construct() {
		std::cout << "[Director] Construction process started\n";
		builder->BuildPart();
	}
};








int main() {
	ConcreteBuilder builder;
	Director director(&builder);
	director->Construct();
	Product *p = builder.GetResult();
	return 0;
}