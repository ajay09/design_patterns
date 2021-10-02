/*
	Composite Design Pattern

        	root
        	|
        	|-leaf1
        	|-leaf2
        	|
        	|-subroot
        	    |-leaf3
         
        
*/

////////////////////////////////////
////////////////// Component.h
////////////////////////////////////
class Component {
public:
	virtual void Operation() = 0;
	virtual void Add(Component *pComponent) = 0;
	virtual void Remove(Component *pComponent) = 0;
	virtual Component* GetChild(int index) = 0;

	virtual ~Component() = default;
};


// We won't be able to implement all the methods from Component here
// e.g. you can't add a child to a leaf.
//      So for now we will keep these methods empty.
////////////////////////////////////
////////////////// Leaf.h
////////////////////////////////////
#include <iostream>

class Leaf : public Component {
public:
	void Operation() override {
		std::cout << "[Leaf] Operation invoked\n";
	}

	void Add(Component *pComponent) override {

	}

	void Remove(Component *pComponent) override {

	}

	Component* GetChild(int index) override {
		return nullptr;
	}

};



////////////////////////////////////
////////////////// Leaf.h
////////////////////////////////////
#include <vector>
#include <iostream>

int depth = 0;

class Composite : public Component {
	std::vector<Component*> m_Children;
public:
	void Operation() {
		++depth;
		std::cout << "[composite] operation\n";
		for (auto pChild : m_Children) {
			for (int i = 0; i < depth; ++i)
				std::cout << "\t";
			std::cout << "|-";
			pChild->Operation();
		}
		--depth;
	}

	void Add(Component *pComponent) {
		m_Children.push_back(pComponent);
	}

	void Remove(Component *pComponent) {
		// this will work without using std:: because of  "argument dependent lookup"
		auto newend = remove(begin(m_Children), end(m_Children), pComponent);
		// The remove() function removes the element specified and shilft the elements after it.
		//  and returns an iterator to the last element.
		m_Children.erase(newend, end(m_Children));
	}

	Component* GetChild(int index) {
		return m_Children[index];
	}

};



int main() {
	Leaf leaf1, leaf2, leaf3 ;
	Composite root ;
	root.Add(&leaf1) ;
	root.Add(&leaf2) ;

	Composite subRoot{} ;
	subRoot.Add(&leaf3) ;

	root.Add(&subRoot) ;
	
	root.Operation() ;
}

