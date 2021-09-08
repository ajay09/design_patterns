/*
	So far we have made a factory class for making points in such a way that it's functions are static,
	i.e. there's no point instantiating the PointFactory as it only has static methods.

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


	This might make sense in some situations e.g. when you wish to send factories across
	to other component.

	But in some scenarios we may not want this to happen. i.e. we wish to separate the 
	process of creation into a separate class but we don't want others to access this factory.

*/

#include <iostream>

class Point {
private:
	// Constructor should be made private
	// otherwise anyone can invoke the constructor to create a Point object
	Point(const float x, const float y) : x{x}, y{y} {}

	// If we kept this public then there would be multiple ways to create Point
	// but we wanted only one way.
	class PointFactory {
	public:
		// This should be static, if we make it non-static the invocation will fail.
		static Point NewCartesian(const float x, const float y) {
			return {x, y};
		}

		static Point NewPolar(const float r, const float theta) {
			return {r * cos(theta), r * sin(theta)};
		}
	};

public:
	float x, y;
	// This will ensure that we have only one PointFactory for every single point.
	static PointFactory Factory;

	friend std::ostream& operator<<(std::ostream &os, const Point &p) {
		return os
			<< "x : " << p.x
			<< " y : " << p.y;
	}
};


int main() {

	// Point p{1, 2}; // won't work
	// Point::PointFactory pf; // won't work
	// auto p = Point::PointFactory::NewCartesian(1, 2); // won't work either

	auto p = Point::Factory.NewCartesian(2, 3);
	std::cout << p << std::endl;

	return 0;
}


