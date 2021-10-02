/*
	3.Solution

	Add a virtual function GetFrame() to the base class
	and the default implementation would return a null pointer.

	This will be only implemented by the Frame class and not by
	the leaf classes.


	When a client wishes to add a new widget to the existing widgets
	he/she must first call GetFrame() method and call the Add method
	only if GetFram() return a non-null object.



	Another problem that needs solution : 
				  pWidget->Add(new Button{});

		- We have created a button on the heap, but we are not deleting the instance.
		  So who should delete this instance, ideally, when we create UI components, 
		  we create them on the heap. This is due to the nature of a UI based application.

		 Different UI controls may be created in different functions and they may be 
		 used across the application. That is why we generally create UI components 
		 on the heap.

		- We can even make all the objecs on the heap

			But who will be responsible of deleting these objects.


	
	The responsibility of deleting the children inside a composite lies with the
	composite itself.
	We should at least delete the main window and it should in turn delete its
	children. Using the destructor in the Frame class.
*/

///////////////////////////////////
//////////////		Widget.h
///////////////////////////////////
class Frame;

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

	virtual Frame* GetFrame() { return nullptr ;}
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

	Frame* GetFrame() override { return this; }

	~Frame() {
		for (auto pChild : m_Children) {
			delete pChild;
		}
	}
};



void Display(Widget *pWidget) {
	pWidget->Paint();
	auto pFrame = pWidget->GetFrame();
	if (pFrame)
		pWidget->Add(new Button{});
	else
		std::cout << "Can not add a child\n";
}

  	


int main() {
	Frame *mainWindow = new Frame{};
	Button *btnOk = new Button{};


	Display(btnOk); // now this won't crash the program

	mainWindow->Add(btnOk);
	Display(mainWindow);

	Frame *childWindow = new Frame{};
	Button *btnFind = new Button{};
	childWindow->Add(btnFind);

	mainWindow->Add(childWindow);

	std::cout << std::endl;
	mainWindow->Paint();


	std::cout << "\nChanging Visibility\n";
	mainWindow->SetVisibility(false);
	mainWindow->Paint();

	delete mainWindow;


	return 0;
}