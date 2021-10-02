/*
	Issues with the design in 2_ui_1.cpp

		- We have Add() and Remove() methods in the base class. These methods
		  are required by the Composite so that we can add and remove the children
		  at runtime.
		  However the leaf classes can't implement these methods, as they can't have
		  any children.

		  Till now we have kept them empty. But if the client calls Add() method on a
		  button. Nothing will happen but the client isn't aware of it.


		  1.Solution
		  	We remove Add() and Remove() methods from the base class and add them only 
		  	to the Composite class. SO now the leaf class will not implement these.
		  	But the client will have to make a distinction between the frame and the
		  	other UI controls. Now you can  no longer call Add() and Remove() methods
		  	on the widget pointer.

		  	This defeats the whole purpose of the Composite Design pattern because
		  	you are making a distinction between a Composite and the Leaf classes.

		  2.Solution
		  	The Add() and Remove() methods in the Leaf class should throw an exception.
		  	  "Not implemented" exception. This will indicate that the methods can not
		  	  be invoked on the leaf classes.


		  	Suppose the client uses the Add() method using the base class pointer.
		  	There is nothing that would indicate the it may throw exception.
	
					  	void Display(Widget *pWidget) {
							pWidget->Paint();
							pWidget->Add(new Button{});
					  	}

					  	Display(new Button{});

		  	This would cause the program to crash due to an uncaught exception.


		  3.Solution
		  	Next
*/


///////////////////////////////////
//////////////		Widget.h
///////////////////////////////////
class Widget {
protected:
	// to set the visibility of the widget.
	bool m_IsVisible{true};
public:
	// Operations
	virtual void Paint() = 0;
	virtual void SetVisibility(bool visibility) = 0;

	// These methods are required by the composite 
	// (i.e. the frame class to add and remove children at runtime.)
	virtual void Add(Widget *pWidget) = 0;
	virtual void Remove(Widget *pWidget) = 0;

	virtual ~Widget() = default;
};



///////////////////////////////////
//////////////		Button.h
///////////////////////////////////
#include <iostream>
#include <stdexcept>

class Button : public Widget {
public:
	void Paint() override {
		if (m_IsVisible) {
			std::cout << "[Button] Painting...\n";
		}
	}
	void SetVisibility(bool visibility) override {
		std::cout << "[Button] Visibility : " << std::boolalpha << visibility << std::endl;
		m_IsVisible = visibility;
	}

	void Add(Widget *pWidget) override {
		throw std::runtime_error{"Not implemented.\n"};
	}

	void Remove(Widget *pWidget) override {
		throw std::runtime_error{"Not implemented.\n"};
	}
};



///////////////////////////////////
//////////////		Frame.h
///////////////////////////////////
#include <iostream>
#include <vector>

int depth{};

class Frame : public Widget {
	std::vector<Widget*> m_Children;
public:
	void Paint() override {
		if (m_IsVisible) {
			++depth;
			std::cout << "[Painting] Frame\n" ;
			for (auto pChild : m_Children) {
				for (int i = 0; i < depth; ++i)
					std::cout << "\t";
				pChild->Paint();
			}
			--depth;
		}
	}
	void SetVisibility(bool visibility) override {
		++depth ;
		m_IsVisible = visibility ;
		std::cout << "[Frame] Changing visiblity\n" ;
		for(auto pChild : m_Children) {
			for(int i = 0 ; i < depth ; ++i) {
				std::cout << '\t' ;
			}
			pChild->SetVisibility(visibility) ;
		}
		--depth ;
	}

	void Add(Widget *pWidget) override {
		m_Children.push_back(pWidget);
	}

	void Remove(Widget *pWidget) override {
		// Erase-Remove idiom
		m_Children.erase(remove(begin(m_Children), end(m_Children), pWidget), end(m_Children));
	}
};



void Display(Widget *pWidget) {
	pWidget->Paint();
	pWidget->Add(new Button{});
}

  	


int main() {
	Frame mainWindow{};
	Button btnOk{};


	Display(&btnOk);  // this line crashed the program due to uncatched exception.

	mainWindow.Add(&btnOk);
	mainWindow.Paint();

	Frame childWindow{};
	Button btnFind{};
	childWindow.Add(&btnFind);

	mainWindow.Add(&childWindow);

	std::cout << std::endl;
	mainWindow.Paint();


	std::cout << "\nChanging Visibility\n";
	mainWindow.SetVisibility(false);
	mainWindow.Paint();
	return 0;
}