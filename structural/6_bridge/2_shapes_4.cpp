/*
	Here we implement the Bridge Design Patter for our Shapes hierarchy.

	We have to implement 2 hierarchies here : 
		- one for the abstraction
		- other for the implementation
*/

struct Point {
	float x{};
	float y{};
};

#include <iostream>

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


////////////////////////////////////
///////////////     Renderer.h
////////////////////////////////////
class Renderer {
public:
	virtual void RenderCircle(Point position, float radius) = 0;
	virtual void RenderLine(Point start, Point end) = 0;
	virtual void Show() = 0;

	virtual ~Renderer() = default;
};



////////////////////////////////////
///////////////     GDI.h
////////////////////////////////////
class GDI : public Renderer {
	Window m_Wind{};
public:
	GDI() {}
	void RenderCircle(Point position, float radius) override {
		m_Wind.DrawCircle(position, radius);
	}

	void RenderLine(Point start, Point end) override {
		m_Wind.DrawLine(start, end);
	}

	void Show() override {
		m_Wind.Show();
	}

};



////////////////////////////////////
///////////////     OpenGL.h
////////////////////////////////////
#include <simple2d.h>
#include <vector>

class OpenGL : public Renderer {
	static std::vector<std::tuple<Point, float>> m_Circles;
	static std::vector<std::tuple<Point, Point>> m_Lines;
	S2D_Window *m_pWindow{};
public:
	OpenGL() {}
	void RenderCircle(Point position, float radius) override {

	}

	void RenderLine(Point start, Point end) override {

	}

	void Show() override {

	}

	static void Render() {

	}
};



std::vector<std::tuple<Point, float>> OpenGL::m_Circles{};
std::vector<std::tuple<Point, Point>> OpenGL::m_Lines{};





////////////////////////////////////
///////////////     Shape.h
////////////////////////////////////
class Shape {
protected:
	// protected because child classes should be able to access it.
	Renderer *m_pRenderer;
public:
	void SetRenderer(Renderer *r) {
		m_pRenderer = r;
	}

	virtual void Draw() = 0;

	virtual ~Shape() = default;
};


// Note that we are not implementing the DrawLine() in the Line class, because the Line class
// only represents the abstraction of the line, and its implementation is in the render hierarchy.
////////////////////////////////////
///////////////     Line.h
////////////////////////////////////
class Line : public Shape {
	Point m_Start;
	Point m_End;
public:
	Line(const Point& start, const Point end) : m_Start{start}, m_End{end} {

	}

	void Draw() override {
		m_pRenderer->RenderLine(m_Start, m_End);
	}
};


////////////////////////////////////
///////////////     Circle.h
////////////////////////////////////
class Circle : public Shape {
	Point m_Center;
	float m_Radius;
public:
	Circle(const Point& center, float radius) : m_Center{center}, m_Radius{radius} {

	}

	void Draw() override {
		m_pRenderer->RenderCircle(m_Center, m_Radius);
	}
};


void RenderShape(Shape *s, Renderer *r) {
	s->SetRenderer(r);
	s->Draw();
	r->Show();
}

int main() {
	Line line{{100, 100}, {100, 300}};
	Circle circle{{400, 400}, 100};

	GDI gdi{};
	OpenGL opengl{};

	RenderShape(&line, &gdi);

	RenderShape(&circle, &gdi);

	return 0;
}


/*

		The connection between the Abstraction and the Implementor is called as the Bridge.


		   Abstraction Hierarchy			          Implementation Hierarchy
    								m_pRenderer
   			|     Shape       |<>-----------------------|    Renderer     |			
			-------------------			    			-------------------			
			| 				  |			    			| 				  |			
			| 				  |			    			| 				  |			
			-------------------			    			-------------------			
				      /_\				    					/_\
				       |				    					 |
			___________|        		    			_________|_______________
			|		   |				    			|			 	        |		
			|		   |				    			|			 	        |		
		| Line |	| Circle |			    		|   GDI       |	    |    OpenGL     |	
		--------	----------			    		---------------	    -----------------	
		|      |	|        |			    		|             |	    |               |	
		|	   |	|	     |			    		|	          |	    |	            |	
		--------	----------			    		---------------	    -----------------	




		Now, in future, if we want to add a new shape, we just have to add a new abstraction.
		We don't have to modify the render hierarchy.

		On the other hand, if we want to add a new API for rendering, we just have to add a 
		new class in the Renderer hierarchy and the Shape hierarchy need not be modified.

		So with this design, we have decoupled the abstraction from its implementation 
		so that we can vary them independently.


		And this is the intent of the bridge design pattern.


*/


