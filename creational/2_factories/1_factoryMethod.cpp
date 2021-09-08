#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

/*
class Point {
public:
	float x, y;

	Point(const float x, const float y) : x{x}, y{y} {}

	// Suppose you want to initialize the point using polar coordinates
	Point(const float r, const float theta) : x{x}, y{y} {}
	// But this will cause error as both the constructors have the same signature.
}
*/

// To solve the above issue
enum class PointType {
	Cartesian,
	Polar
};

class Point {
public:
	float x, y;

	Point(const float a, const float b, const PointType type = PointType::Cartesian) {
		if (type == PointType::Cartesian) {
			x = a;
			y = b;
		} else {
			x = a * cos(b);
			y = a * sin(b);
		}
	}

	// The above design still has one issue.
	// The client would by mistake pass r and theta to forget to set the type to Polar
	// The this design is still having issues.
};

int main() {
	Point p{1, 2};
	return 0;
}