/*
Liskov Substitution Principle (LSP)
	Objects should be replaceable with instances of their subtyes without altering program correctness

*/

#include <iostream>

// example where it is violated
class Rectangle {
protected:
	int width, height;
public:
	Rectangle(const int w, const int h) : width(w), height(h) {}

	virtual int GetWidth() const { return width; }
	virtual int GetHeight() const { return height; }

	virtual void SetWidth(const int width) { this->width = width; }
	virtual void SetHeight(const int height) { this->height = height; }

	int Area() const { return width * height; }
};

// This function is correct for Rectangle.
// But later when we use the same code for a sub-class of Rectangle
// it gives incorrect results. Thus violates the LSP.
void process(Rectangle &r) {
	int w = r.GetWidth();
	r.SetHeight(10);

	std::cout << "Expected area = " << (w * 10) << ", got " << r.Area() << std::endl;
}

class Square : public Rectangle {
public:
	Square(int size) : Rectangle{size, size} {}

	void SetWidth(const int width) override {
		this->width = height = width;
	}

	void SetHeight(const int height) override {
		this->height = width = height;
	}
};

int main() {
	Rectangle r{5, 5};
	process(r);

	Square s{5};
	process(s);

	return 0;
}


/*
Fix for the above problem.

- No need of having the square class.
- Instead use a Rectangle Factory which would create both Rectangle and Square

struct RectangleFactory {
	static Rectangle CreateRectangle(int w, int h);
	static Rectangle CreateSquare(int size);	
};

*/