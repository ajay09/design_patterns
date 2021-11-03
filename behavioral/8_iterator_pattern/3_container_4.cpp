/*
	Containers with iterators.
	

	List
*/

////////////////////////////////////////
///////////////////////// Iterator.h
////////////////////////////////////////
template <typename T>
class Iterator {
public:
	virtual void Next() = 0;
	virtual bool HasNext() = 0;
	virtual const T& CurrentItem() = 0;

	virtual ~Iterator() = default;
};

//////////////////////////////////////////
///////////////////////////  Container.h
//////////////////////////////////////////
#include <cstddef>
template<typename Item>
class Container {
public:
	virtual void Add(const Item& element) = 0;
	virtual size_t Size() const = 0;
	virtual ~Container() = default;

	virtual Iterator<Item>* CreateIterator() const = 0;
};


#include <initializer_list>
#include <algorithm>

template<typename T>
class ListIterator;

template<typename T>
class List : public Container<T> {
	struct Node {
		T m_Data;
		Node *m_pNext;

		Node(const T& data, List<T>::Node* pNext = nullptr) : m_Data{data}, m_pNext{pNext} {}
	};

	friend class ListIterator<T>;
public:

	List() = default;

	// The right approach would be to use operator new function and the placement new operator
	List(const std::initializer_list<T> &elements) :  m_Size{elements.size()} {
		// construct the List in the order in which elements were provided.
		auto itr = elements.begin();
		Add(*itr++);
		auto temp = m_pHead;
		while (itr != elements.end()) {
			temp->m_pNext = new Node{*itr++};
			temp = temp->m_pNext;
		}
	}

	~List() {
		auto temp = m_pHead;
		do {
			m_pHead = m_pHead->m_pNext;
			delete temp;
			temp = m_pHead;
		} while(temp != nullptr);
	}

	void Add(const T& element) override {
		if (m_Size == 0) {
			m_pHead = new Node{element};
		} else {
			// add the new node to the front.
			auto temp = new Node{element, m_pHead};
			m_pHead = temp;
		}
		m_Size++;
	}
	
	size_t Size() const override {
		return m_Size;
	}

	Node* GetHead() {
		return m_pHead;
	}

	// co-variant return type.
	ListIterator<T>* CreateIterator() const override;
private:
	Node *m_pHead ;
	size_t m_Size{} ;
};



template <typename T>
class ListIterator : public Iterator<T> {
	typename List<T>::Node*  m_pHead;
public:
	ListIterator(typename List<T>::Node*  pHead) : m_pHead{pHead} {}
	
	void Next() override {
		m_pHead = m_pHead->m_pNext;
	}

	bool HasNext() override {
		return m_pHead != nullptr;
	}
	
	const T& CurrentItem() override {
		return m_pHead->m_Data;
	}
};

template <typename T>
ListIterator<T>* List<T>::CreateIterator() const {
	return new ListIterator<T>{m_pHead};
}





#include <iostream>


// Polymorphic traversal : can traverse any container.
void Print(Iterator<int> *itr) {
	while(itr->HasNext()) {
		std::cout << itr->CurrentItem() << ' ';
		itr->Next() ;
	}
	std::cout << '\n' ;
	delete itr ;
}

int main() {
	List<int> numbers {1,2,3,4} ;
	numbers.Add(5) ;
	numbers.Add(6) ;
	numbers.Add(7) ;

	Print(numbers.CreateIterator()) ;

	std::cout << std::endl;

	return 0;
}