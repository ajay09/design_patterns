/*
	Till now we had factory which made objects of a single type.

	What about several types?

	Instead of specifying explicitly the type of drink we want, take input as a string
	and build a type based on that.
*/

#include <iostream>
#include <memory>
#include <map>
#include "HotDrink.h"
#include "DrinkFactory.h"

using namespace std;

// Issue with this solution is if we keep on adding more types then it would become very messy.
unique_ptr<HotDrink> make_drink(string type) {
	unique_ptr<HotDrink> drink;
	if (type == "tea") {
		drink = make_unique<Tea>(); // requires c++14
		drink->prepare(200);
	} else {
		drink = make_unique<Coffee>();
		drink->prepare(50);
	}
	return drink;
}

// Thus we go for an abstract factory
// For this we add HotDrinkFactory.h  CoffeeFactory.h  TeaFactory.h
// Just like we have a hierarchy of products we would like to have a hierarchies of their factories.

int main() {

	auto d = make_drink("tea");

	DrinkFactory df;
	df.make_drink("coffee");

	return 0;
}