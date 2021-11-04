/*
	Benefits of current implementation : 

		- You don't have to deal with manual memory management as we are creating iterators over stack.

		- We can now use the array class with a range based for loop.
		
		- also support polymorphic iteration


	Issue :
	- Name of the iterator classes are distict for Array and List.

	Sol : Since Iterators require access to the Container, so iterators can be defined as
	      nested classes of their corrensponding containers.

	      Provide the same name to both the iterators.
*/





#include <initializer_list>
#include <algorithm>

template<typename T>
class ArrayIterator;

template<typename T>
class Array {
	T *m_pBuffer{} ;
	size_t m_Size{} ;
public:
	Array() = default;

	// The right approach would be to use operator new function and the placement new operator
	Array(const std::initializer_list<T> &elements) : m_pBuffer{new T[elements.size()]} {
		m_Size = 0;
		for (const auto &element : elements) {
			m_pBuffer[m_Size++] = element;
		}
	}

	~Array() {
		delete[] m_pBuffer;
	}

	void Add(const T& element) {
		if (m_Size == 0) {
			m_pBuffer = new T[1]{element};
		} else {
			auto temp = new T[m_Size + 1];
			std::copy(m_pBuffer, m_pBuffer + m_Size, temp);
			temp[m_Size] = element;
			delete []m_pBuffer;
			m_pBuffer = temp;
		}
		m_Size++;
	}
	
	size_t Size() const {
		return m_Size;
	}

	T& operator[](int index) {
		assert(index < m_Size);
		return m_pBuffer[index];
	}

	const T& operator[](int index) const {
		assert(index < m_Size);
		return m_pBuffer[index];
	}

	class Iterator {
		T *m_pBegin{};
		// T *m_pEnd{};
	public:
		Iterator(T *pBegin) : m_pBegin{pBegin} {}
		
		// pre-increment
		Iterator operator ++() {
			++m_pBegin;
			return *this;
		}

		// post-increment
		Iterator operator ++(int) {
			auto temp(*this);
			++m_pBegin;
			return temp;
		}
		
		T& operator *() {
			return *m_pBegin;
		}

		bool operator ==(const Iterator &other) const {
			return m_pBegin != other.m_pBegin;
		}

		bool operator !=(const Iterator &other) const {
			return !(m_pBegin == other.m_pBegin);
		}
	};

	Iterator begin() const {
		return Iterator{m_pBuffer};
	}
	Iterator end() const {
		return Iterator{m_pBuffer + m_Size};
	}
};







template<typename T>
class List {
	struct Node {
		T m_Data;
		Node *m_pNext;

		Node(const T& data, List<T>::Node* pNext = nullptr) : m_Data{data}, m_pNext{pNext} {}
	};

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

	void Add(const T& element) {
		if (m_Size == 0) {
			m_pHead = new Node{element};
		} else {
			// add the new node to the front.
			auto temp = new Node{element, m_pHead};
			m_pHead = temp;
		}
		m_Size++;
	}
	
	size_t Size() const {
		return m_Size;
	}

	class Iterator {
		typename List::Node*  m_pHead;
	public:
		Iterator(typename List::Node*  pHead) : m_pHead{pHead} {}
		
		Iterator operator ++() {
			m_pHead = m_pHead->m_pNext;
			return *this;
		}

		Iterator operator ++(int) {
			auto temp(*this);
			m_pHead = m_pHead->m_pNext;
			return temp;
		}
		
		T& operator *() {
			return m_pHead->m_Data;
		}

		bool operator ==(const Iterator& other) const {
			return m_pHead == other.m_pHead;
		}

		bool operator !=(const Iterator& other) const {
			return !(*this == other);
		}
	};


	Iterator begin() const {
		return Iterator{m_pHead};
	}

	Iterator end() const {
		return Iterator{nullptr};
	}



private:
	Node *m_pHead ;
	size_t m_Size{} ;
};



#include <iostream>


template <typename Container>
void Print(Container &container) {
	for (auto x : container) {
		std::cout << x << " ";
	}

	std::cout << std::endl;
}


int main() {
	Array<int> numbers {1,2,3,4};
	numbers.Add(5);
	numbers.Add(6);
	numbers.Add(7);

	Array<int>::Iterator itr = numbers.begin();
	while (itr != numbers.end()) {
		std::cout << *itr++ << " ";
	}

	std::cout << std::endl;

	for (auto x : numbers) {
		std::cout << x << " ";
	}

	std::cout << std::endl;


	List<int> listnumbers {1,2,3,4};
	listnumbers.Add(5);
	listnumbers.Add(6);
	listnumbers.Add(7);


	for (auto x : listnumbers) {
		std::cout << x << " ";
	}

	std::cout << std::endl;
	std::cout << std::endl;

	Print<Array<int>>(numbers);
	std::cout << std::endl;

	Print<List<int>>(listnumbers);
	std::cout << std::endl;

	return 0;
}













