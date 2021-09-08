// Solution to the problem in 1_factoryMethod.cpp

#include <iostream>

class Point {
	// Constructor should be made private
	Point(const float x, const float y) : x{x}, y{y} {}
public:
	float x, y;

	// Factory Method
	static Point NewCartesian(const float x, const float y) {
		return {x, y};
	}

	// Factory Method
	static Point NewPolar(const float r, const float theta) {
		return {r * cos(theta), r * sin(theta)};
	}

	friend std::ostream& operator<<(std::ostream &os, const Point &p) {
		return os
			<< "x : " << p.x
			<< " y : " << p.y;
	}
};

int main() {

	auto c = Point::NewCartesian(1, 2);

	std::cout << c << std::endl;

	auto p = Point::NewPolar(5, M_PI_4); // theta = 45 degree

	std::cout << p << std::endl;

	return 0;
}

// Factory Method
/*
	Factory methods are simply static functions which are going to yield an object.

	You can give factory methods a name while a constructor can't be renamed.

*/