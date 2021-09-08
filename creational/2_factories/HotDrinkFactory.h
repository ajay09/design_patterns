#pragma once
#include "HotDrink.h"
#include <memory>

class HotDrinkFactory {
public:
	virtual std::unique_ptr<HotDrink> make() = 0;
	virtual ~HotDrinkFactory() {}
};