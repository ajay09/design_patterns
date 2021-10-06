/*
	

	If you do not want the flexibility of choosing the implementer of an abstraction at runtime,
	then you can also create a bridge at compile time.

	This can be done through multiple inheritance. So if we want to draw a line abstruction 
	using software rendering, then we can inherit from the Line and the GDI class.


	Use multiple inheritance to create a Bridge.

	- Create a class called Line_GDI and this will inherit from the Line class and from the GDI class.

	- We don't want to expose the implementation of how the shape is actually rendered, that is why
	  we will inherit Line_GDI privately from the GDI class.
	  Thus the client's of Line_GDI will not be able to see the methods of the base class GDI.


*/

class Line_GDI : public Line, private GDI {
	using Line::Line;
public :
	void Draw() override {
		RenderLine(GetStart(), GetEnd()); // this will call the inherited mentod of GDI class
		Show();
	};
};