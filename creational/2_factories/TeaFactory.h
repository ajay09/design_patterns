#pragma once
#include "HotDrink.h"
#include "HotDrinkFactory.h"

class HotDrink;

class TeaFactory : public HotDrinkFactory {
	std::unique_ptr<HotDrink> make() override {
		return std::make_unique<Tea>();
	}
};