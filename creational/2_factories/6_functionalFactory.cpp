/*
	It says we don't specifically require a hierarchy of factories.
	We can simply use lambda funcitons instead.
*/
#include <iostream>
#include <memory>
#include <map>
#include "DrinkFactory.h"

using namespace std;

int main() {

	DrinkFactory df;
	df.make_drink("coffee");

	DrinkWithVolumeFactory dvf;
	dvf.make_drink("tea");
	
	return 0;
}