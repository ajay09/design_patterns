/*
	Adding more flexibility to the UI design.

	GetParent()  => would help client to know whether a particular UI component
					has a parent or not. This would assist them in moving up
					the hierarchy.

	
	Caveat :
		- This implementation still has memory leaks.

		Suppose you remove a Widget from the Frame. Now deleting the Frame won't delete it.
		Moreover as per our current implementation of Remove() method that pointer will
		be lost forever.

		Creating a vector of smartpointers to store components might help 
		but it will also introduce an overhead.

*/

///////////////////////////////////
//////////////		Widget.h
///////////////////////////////////
class Frame;

class Widget {
	Widget *m_pParent{};
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

	void SetParent(Widget *p) { m_pParent = p; }
	Widget* GetParent() const { return m_pParent; }
	bool HasParent() const {return m_pParent !=nullptr ;}
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
		pWidget->SetParent(this);
	}

	void Remove(Widget *pWidget) override {
		// Erase-Remove idiom
		m_Children.erase(remove(begin(m_Children), end(m_Children), pWidget), end(m_Children));
		pWidget->SetParent(nullptr);
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