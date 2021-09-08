/*
	The design in 2_factoryMethod.cpp was good.
	But if the factory methods get a little bit more coplicated it might be argued that 
	the actual process of creation should be externalized somehow and should be taken into
	a separate component.

	Thus a Fatory would be a separate component that would take care of creation of a particular
	object.

	Factory Method => A function which exists inside the class for which you wish to create
					  an object.

*/

#include <iostream>

class Point {
	// Constructor should be made private

	Point(const float x, const float y) : x{x}, y{y} {}
public:
	float x, y;

	friend std::ostream& operator<<(std::ostream &os, const Point &p) {
		return os
			<< "x : " << p.x
			<< " y : " << p.y;
	}

	friend class PointFactory;
};


class PointFactory {
	PointFactory() {}
public:
	static Point NewCartesian(const float x, const float y) {
		return {x, y};
	}

	static Point NewPolar(const float r, const float theta) {
		return {r * cos(theta), r * sin(theta)};
	}
};


int main() {

	auto c = PointFactory::NewCartesian(1, 2);

	std::cout << c << std::endl;

	auto p = PointFactory::NewPolar(5, M_PI_4); // theta = 45 degree

	std::cout << p << std::endl;

	return 0;
}


/*
A non-static version

class PointFactory {
public:
	Point NewCartesian(const float x, const float y) {
		return {x, y};
	}

	Point NewPolar(const float r, const float theta) {
		return {r * cos(theta), r * sin(theta)};
	}
};


int main() {
	PointFactory pf;

	auto c = pf.NewCartesian(1, 2);

	std::cout << c << std::endl;

	auto p = pf.NewPolar(5, M_PI_4); // theta = 45 degree

	std::cout << p << std::endl;

	return 0;
}

*/