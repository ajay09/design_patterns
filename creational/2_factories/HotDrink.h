#pragma once
#include <iostream>

class HotDrink {
public:
	virtual void prepare(int volume) = 0;
	// If you are creating an abstract class then make sure
	// to provide a virtual desturctor with implementation
	virtual ~HotDrink() {}
};

class Tea : public HotDrink {
public:
	void prepare(int volume) override {
		std::cout << "Take tea bag, boil water, pour " << volume << "ml" << std::endl;
	}
};

class Coffee : public HotDrink {
public:
	void prepare(int volume) override {
		std::cout << "Grind some beans, boil water, pour " << volume << "ml" << std::endl;
	}
};