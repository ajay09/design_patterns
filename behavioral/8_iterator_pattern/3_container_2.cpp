/*
	Containers without iterators.
	

	List

	Issue :
	 - The implementation details of the Container are exposed.
	   The clients have to deal with the traversal algo.
	   e.g. Array  =>  use index.
	        List   =>  use pointer.

	 - Inconsistent API as each Conatainer will have a different implementation.

	 - Violation of Encapsulation
	    The clients can see the internal state and modify it directly without Object's involvement.
		Thus may corrupt its state.

	Iterator design pattern can help resolve these issues.
*/

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
};


#include <initializer_list>
#include <algorithm>

template<typename T>
class List : public Container<T> {
public:
	struct Node {
		T m_Data;
		Node *m_pNext;

		Node(const T& data, List<T>::Node* pNext = nullptr) : m_Data{data}, m_pNext{pNext} {}
	};

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
private:
	Node *m_pHead ;
	size_t m_Size{} ;
};

#include <iostream>

int main() {
	List<int> numbers {1,2,3,4} ;
	numbers.Add(5) ;
	numbers.Add(6) ;
	numbers.Add(7) ;

	auto item = numbers.GetHead();
	while (item != nullptr) {
		std::cout << item->m_Data << " ";
		item = item->m_pNext;
	}

	std::cout << std::endl;

	return 0;
}