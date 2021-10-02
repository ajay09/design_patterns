/*
	User Interface

	This is how many user interfaces are implemented in C++, Java, C#

										Whole 
										 \/
			|-----------------------------------------------------------|
			|							Frame 							|
			|-----------------------------------------------------------|
			|	--------		--------	--------		--------    |
			|	 Button 		ListBox 	TextEdit 	      Image  <--|-------Part
			|	--------		--------	--------		--------	|
			|															|
			|  |------------------------------------------------------| |
			|  |                         Frame 						  | |
			|  |------------------------------------------------------| |
			|  |  		--------	--------		--------		  | |
			|  |  		ListBox 	CheckBox 	      Image  	      | |
			|  |  		--------	--------		--------		  | |
			|  -------------------------------------------------------- |
			-------------------------------------------------------------

		A typical UI based application has a main window.
			- Let's call this Frame, this Frame will internally host different 
			  kinds of UI controls, such as a button listbox, combo box, radio buttons, 
			  checkboxes, etc. 
			- And the frame may also contain a child frame, which in turn may contain 
			  other UI controls.

		There are different kinds of operations that we would like to perform on the 
		frame and its children,
		e.g. when you open the application, the frame has to be displayed on the screen 
		     and in turn it has to display all its children.
			 This is done through a process called as painting.

			So as soon as the frame is painted so that it can be displayed on the screen, 
			in turn it should send the paint message to all its children and they should
			paint themselves. So the programmer should not have to individually call paint
			on the child components of the frame.

			Similarly we may also have to perform other operations on the freame and 
			those operations may have to be in turn performed on its children
			e.g. resizing, change visibility, etc.


	If we don't use the Composite design pattern then we will have to individually call
	these operations on the children of the freame and the client will have to deal with
	individual objects directly and this will lead to tight coupling.
	So to avoid the coupling between the client code and the UI components inside the frame
	we would use the Composite Design Pattern.


	This will allow us to treat the frame and the individual component uniformally.
	The client will not have to make any distinction between these two.
    This perfectly symbolizes the part-whole or whole-part relationship 
    in this example, this frame is the hole and these industrial UI components are the parts.

	And the Composite design pattern is used when you want to represent whole-part 
	relationship.

	Note that an individual part may itself act as a whole, like in this example, 
	a child frame is a part of the outer frame, but it acts as a hole for these 
	individual components.

	So when we have a situation where we want to represent whole part hierarchies, 
	we should implement the Composite design pattern. It will help us treat the whole
	and the part uniformly.




				base class represents all kinds of UI controls.

			  |   Widget          |
			  ---------------------
			  | Operation()       |<----------------------------------------------;
			  | Add(Component)    |							      				  |
			  | Remove(Component) |							      				  |
			  | GetChild(int)     |							      				  |
			  ---------------------							      				  |
		               /_\									      				  |
		                |									      				  |
		________________|________________________________ 					      |
	   |				|	    		 				|						  |
	   |			    |								|				children  |
|    Button  |    |  ListBox   |         		|     Frame         |<>-----------~
---------------   ---------------  ...      	---------------------
| Operation() |   | Operation() |         		| Operation()       |    forall g in children
|             |   |             |         		| Add(Component)    |        g.Operation();
|             |   |             |         		| Remove(Component) |
| 			  |   | 			|         		| GetChild(int)     |
---------------   ---------------         		---------------------

The Leaf classes will be the UI 		   And their compositions will be represented by
controls e.g. Button, ListBox,				the Frame class.
CheckBox, etc.							   - The Frame class is the Composite here.
										   - It will also inherit from Widget class
											 so that it also becomes a kind of widget for
											 the frame to hold different kinds of widgets
											 which could even be a frame itself.
										   - So this way we can have recursive composition
										     of widgets.
											 
											 
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

	// currently we will keep them empty
	void Add(Widget *pWidget) override {
	}
	void Remove(Widget *pWidget) override {
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




int main() {
	Frame mainWindow{};
	Button btnOk{};
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