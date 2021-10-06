/*
	Till now we have implemented the Shapes hierarchy which uses software-rendering
	to print the shapes.


	What if we also want to use hardware-rendering to print the shapes.
	Because that will take the advantaget of the hardware capabilities and the
	drawing performance will improve.


	For hardware rendering we will use the OpenGL library. Obviously we don't want to 
	implement the functionality and existing line and circle classes.
	So that's why I'm going to add new classes that will have the implementation
	of drawing through openGL.

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


// Since both software and harware rendering clasess will now inherit from the
// shape class thus we move the window pointer to the classes instead.
////////////////////////////////////
///////////////     Shape.h
////////////////////////////////////
class Shape {
public:
	virtual void Draw() = 0;
	virtual ~Shape() = default;
};


////////////////////////////////////
///////////////     Line.h
////////////////////////////////////
class Line : public Shape {
	Window *m_Window;
	Point m_Start{};
	Point m_End{};
public:
	Line(const Point &start, const Point &end, Window *window)
		: m_Window{window}, m_Start{start}, m_End{end} {
	}

	void Draw() override {
		m_Window->DrawLine(m_Start, m_End);
		m_Window->Show();
	}
};


////////////////////////////////////
///////////////     Line_OpenGL.h
////////////////////////////////////
#include <simple2d.h>

class Line_OpenGL : public Shape {
	static Point m_Start;
	static Point m_End;
	S2D_Window *m_pWindow{};
public:
	Line_OpenGL(const Point &start, const Point &end, S2D_Window *window)
		: m_pWindow{window} {
			m_Start = start; 
			m_End = end;
	}

	static void Render() {
		S2D_DrawLine(m_Start.x, m_Start.y, m_End.x, m_End.y, 1,
					 1, 1, 1, 1,
					 1, 1, 1, 1,
					 1, 1, 1, 1,
					 1, 1, 1, 1
					);
	}

	void Draw() override {
	}
};

Point Line_OpenGL::m_Start = {0, 0};
Point Line_OpenGL::m_End = {0, 0};


////////////////////////////////////
///////////////     Circle.h
////////////////////////////////////
class Circle : public Shape {
	Window *m_Window;
	Point m_Center{};
	float m_Radius{};
public:
	Circle(const Point &center, float radius, Window *window)
		: m_Window{window}, m_Center{center}, m_Radius{radius} {
	}

	void Draw() override {
		m_Window->DrawCircle(m_Center, m_Radius);
		m_Window->Show();
	}
};




////////////////////////////////////
///////////////     Circle_OpenGL.h
////////////////////////////////////
#include <simple2d.h>

class Circle_OpenGL : public Shape {
	static Point m_Center;
	static float m_Radius;
	S2D_Window *m_pWindow{};
public:
	Circle_OpenGL(const Point &start, const Point &end, S2D_Window *window)
		: m_pWindow{window} {
			m_Center = start; 
			m_Radius = end;
	}

	static void Render() {
		S2D_DrawCircle(m_Center.x, m_Center.y, m_Radius, 1,
					 1, 1, 1, 1);
	}

	void Draw() override {
	}
};

Point Circle_OpenGL::m_Center = {0, 0};
Point Circle_OpenGL::m_Radius = 0;








void RenderShape(Shape *pShape) {
	pShape->Draw();
}


void Software() {
	// This will work from C++14
	Window window;
	window.Show();

	Line l{{100, 100}, {300, 300}, &window};
	// l.Draw();

	Circle c{{400, 400}, 5, &window};
	// c.Draw();

	RenderShape(&l);
	RenderShape(&c);
}

void OpenGL() {
	S2D_Window *pWin = S2D_CreateWindow("Shapes", 800, 600, nullptr, 
										&Line_OpenGL::Render, S2D_RESIZABLE);

	Line_OpenGL l {{100, 100}, {300, 300}, pWin};
	l.Draw();
	S2D_Show(pWin);
	S2D_FreeWindow(pWin);
}


int main() {
	OpenGL();

	return 0;
}



/*



	Issues with the above implementation.



							    |     Shape       |
								-------------------
								| 				  |
								| 				  |
								-------------------
									    /_\
									     |
			_____________________________|__________________________
			|		   |			|			 	   |		
			|		   |			|			 	   |		
		| Line |	| Circle |	| Line_OpenGL |	 | Circle_OpenGL |	
		--------	----------	---------------	 -----------------	
		|      |	|        |	|             |	 |               |	
		|	   |	|	     |	|	          |	 |	             |	
		--------	----------	---------------	 -----------------	


		In similar way we can keep on adding more types of shapes.


		- Suppose we want to add support for drawing rectangle.
			We would have to add 2 classes : Rectangle and Rectangle_OpenGL

			Thus for adding one shape, we have to add two classes. One will draw
			through software rendering and the other through hardware rendering
			using OpenGL.


		- What if we want to add support for drawing the shpaes using the DirectX API ?
		   We would have to add correspoding classes for each of the shape.

		   And if now we want to add support for one more shape, then we will have to
		   add new 3 classes.
		   e.g. If we want to add support for triangle, then 3 new classes will be
		        Triangle,  Triangle_OpenGL,  Triangle_DirectX.


		- Thus the number of new classes we have to add on adding a new shape increases
			exponentially. This will lead to large number of classes in our application
			rendering it unmaintainable and difficult to modify.



		Problem : Proliferation of classes in the application.

		Solution : 
				   First we need to understand that all of these classes represent the
				   Shape abstraction. Consider the Line class, the line represents an
				   abstraction of a line and it also contains the implementation
				   of drawing the line.

				   So the implementation of the abstraction is in the same class.

				   If we want a different implementation of the same abstraction, then
				   we will have to create another class e.g Line_OpenGL. This also 
				   represents the same line abstraction and it has its own implementation.
				   Similaryly for Line_DirectX.

				   So if we want to change the implementaiton of an abstraction, we have
				   to create a new class and that new class also constains the same 
				   abstraction but a new implementation.


				   What we want is that if we add a new way of drawing a line, we should
				   just add a new implementation and not a new abstraction. And a single
				   abstraction should be used along different implementations.


				   Why we are not able to avoid creating multiple abstractions of the line
				   or any other shape class?
				   The reason is all of these abstractions and implementations are in the 
				   same class hierarchy.


		So to avoid having to repeat an abstraction and its implementation, we will separate
		out the abstraction and its implementation. So instead of inheriting all the classes
		from shape we will split them out into their own hierarchies.
		Thus we will have 2 hierarchies, the shape hierarchy and the drawing API hierarchy.



		   Abstraction Hierarchy				  Implementation Hierarchy

   			|     Shape       |<>-------------------|    Renderer     |			
			-------------------						-------------------			
			| 				  |						| 				  |			
			| 				  |						| 				  |			
			-------------------						-------------------			
				      /_\									/_\
				       |									 |
			___________|        					_________|_______________
			|		   |							|			 	        |		
			|		   |							|			 	        |		
		| Line |	| Circle |					|   GDI       |	    |    OpenGL     |	
		--------	----------					---------------	    -----------------	
		|      |	|        |					|             |	    |               |	
		|	   |	|	     |					|	          |	    |	            |	
		--------	----------					---------------	    -----------------	



		- GDI will take care of software rendering and OpenGL will use an API that 
		  internally uses hardware rendering and Shape will hold a reference of the 
		  renderer so the child classes of Shape can now use any of the renderer.

		  So for example, we want to draw a line using software rendering.
		  Then once we instantiate line, we will specify GDI as the render.
		  And when we invoke the Draw() method of Line, it will internally 
		  use the capabilities of this class for drawing in the same way.

		  
		  If we want to draw a line using OpenGL, then while instantiating line 
		  we can pass an instance of this OpenGL renderer and when the line is 
		  drawn, it will use the API from OpenGL.



	Does this really solve a problem? What if we add a new shape?

	e.g. we add a rectangle and this will only represent the abstraction of a rectangle.
		 It will not contain any drawing implementation because the basic drawing 
		 implementation will be in the second hierarchy. So we can easily draw a 
		 rectangle using either GDI class or the OpenGL class.



So this design is nothing but the Bridge design pattern.
*/