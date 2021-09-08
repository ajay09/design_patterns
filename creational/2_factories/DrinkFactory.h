#pragma once
#include <string>
#include <map>
#include <memory>
#include "HotDrinkFactory.h"
#include "CoffeeFactory.h"
#include "TeaFactory.h"

#include <functional>

using std::string;
using std::map;
using std::unique_ptr;
using std::make_unique;
using std::function;

class HotDrink;

class DrinkFactory {
	map<string, unique_ptr<HotDrinkFactory>> factories;
public:
	DrinkFactory() {
		factories["coffee"] = make_unique<CoffeeFactory>();
		factories["tea"] = make_unique<TeaFactory>();
	}

	unique_ptr<HotDrink> make_drink(const string &name) {
		auto drink = factories[name]->make();
		drink->prepare(200); // if placed here we can't modify it based on the drink type.
							 // to do this we need to move it to the actual drink class.
		return drink;
	}
};


// for 6_functionalFactory.cpp
class DrinkWithVolumeFactory {
	map<string, function<unique_ptr<HotDrink>()>> factories;
public:
	DrinkWithVolumeFactory() {
		factories["tea"] = [] {
			auto tea = make_unique<Tea>();
			tea->prepare(100);
			return tea;
		};
		factories["coffee"] = [] {
			auto coffee = make_unique<Coffee>();
			coffee->prepare(100);
			return coffee;
		};
	}

	unique_ptr<HotDrink> make_drink(const string &name) {
		return factories[name]();
	}
};

