/*
	Here we implement an abstraction called Line.

	
	We have issues with the below implementation : 

		- One is the Line class represents an abstraction of a line and the 
		  same class also implements that abstraction.

		  What if we want add support for drawing other kinds of shapes, such as circles 
		  or rectangles? Those are also kinds of shapes just like line.

		  They will also represent shape abstraction, but their implementation will be different.


		So that's why we will have to create separate classes for each shape and all these 
		classes will inherit from a common based class Shape.

		So the entire hierarchy will represent the shape abstraction, although its 
		implementation will be done in separate child classes.

*/


#include <iostream>

// Plain-Old-Type data  =>  can be initialized using constructor syntax
//							even though we have not implemented any
//							parameterized constructor
struct Point {
	float x{};
	float y{};
	// friend std::ostream& operator<<(std::ostream os, const Point& p);
};

std::ostream& operator<<(std::ostream &os, const Point& p) {
	return os << "[" << p.x << ", " << p.y << "]";
}

////////////////////////////////////
///////////////     Window.h
///////////////     Uses software-rendering to draw the shapes
////////////////////////////////////


#include <iostream>
#include <sstream>

class Window {
	std::stringstream m_Win{};
public:
	static void RenderCallBackHandler() {

	}

	Window() {
		m_Win << "\t *** Creating a new Window\n";
	}

	~Window() {
	}

	void DrawCircle(Point position, float radius) {
		m_Win << "\t\t Draw Circle at " << position << " with radius " << radius << std::endl;
	}

	void DrawLine(Point start, Point end) {
		m_Win << "\t\t Draw a Line between " << start << " and " << end << std::endl;
	}
	

	void Show() {
		std::cout << m_Win.str();
		m_Win.str().clear();
	}

};



////////////////////////////////////
///////////////     Line.h
////////////////////////////////////
class Line {
	Point m_Start{};
	Point m_End{};
	Window m_Window{};
public:
	Line(const Point &start, const Point &end)
		: m_Start{start}, m_End{end} {
	}

	void Draw() {
		m_Window.DrawLine(m_Start, m_End);
		m_Window.Show();
	}
};





int main() {
	// This will work from C++14
	Line l{{100, 100}, {300, 300}};
	l.Draw();

	return 0;
}



