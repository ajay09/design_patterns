/*
	In this file we implemented the hierarchy of shapes.
	We draw the shapes using  "Software Rendering"

	The hierarchy represents the abstraction of a Shape, but the implementations
	of different shapes is in their own classes.

	In the same way we can add support for dreawing more shpaes, using software redering.
	e.g. if we want to draw a rectangel, we simply have to inherite a class from Shape
	and implement the functionality of drawing the rectangle using software rendereing.


							    |     Shape       |
								-------------------
								| 				  |
								| 				  |
								-------------------
									    /_\
									     |
				_________________________|____________...............
				|						 |							|
				|						 |							|
		|     Line        |		  |     Circle    |         |   Rectangle     |
		-------------------		  -----------------         -------------------
		| 				  |		  | 			  |         | 				  |
		| 				  |		  | 			  |         | 				  |
		-------------------		  -----------------         -------------------


		So we can say,  an abstraction and its implementation is in the same hierarchy.
						The entire hierarchy represents the abstraction and the implementation
						of refined abstractions is in the same hierarchy.

		

		But in some cases we may have to modify an abstraction and its implementation 
		independently.
		---------------------- NEXT -------------------

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
		m_Win.str("");
		m_Win.clear();
	}

};


// Since we will use the same window for drawing different kinds of shapes.
// Thus we will store a window pointer in the Shape class and this window
// pointer will be shared by all the child classes. That's why it needs to 
// be accessible by them  =>  so we make it protected.
////////////////////////////////////
///////////////     Shape.h
////////////////////////////////////
class Shape {
protected:
	Window *m_Window;
public:
	Shape(Window *window) : m_Window{window} {

	}
	virtual void Draw() = 0;
	virtual ~Shape() = default;
};


////////////////////////////////////
///////////////     Line.h
////////////////////////////////////
class Line : public Shape {
	Point m_Start{};
	Point m_End{};
public:
	Line(const Point &start, const Point &end, Window *window)
		: Shape{window}, m_Start{start}, m_End{end} {
	}

	void Draw() override {
		m_Window->DrawLine(m_Start, m_End);
		m_Window->Show();
	}
};




////////////////////////////////////
///////////////     Circle.h
////////////////////////////////////
class Circle : public Shape {
	Point m_Center{};
	float m_Radius{};
public:
	Circle(const Point &center, float radius, Window *window)
		: Shape{window}, m_Center{center}, m_Radius{radius} {
	}

	void Draw() override {
		m_Window->DrawCircle(m_Center, m_Radius);
		m_Window->Show();
	}
};







void RenderShape(Shape *pShape) {
	pShape->Draw();
}





int main() {
	// This will work from C++14
	Window window;
	window.Show();

	Line l{{100, 100}, {300, 300}, &window};
	// l.Draw();

	Circle c{{400, 400}, 5, &window};
	// c.Draw();

	RenderShape(&l);
	RenderShape(&c);
	return 0;
}