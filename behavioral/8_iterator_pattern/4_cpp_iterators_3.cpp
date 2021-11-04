/*
	Constant Iterators for const objects of the Container.

	const overloads for const container objects.
*/

/*
		_cpp_iterators_3.cpp:132:16: error: functions that differ only in their return type cannot be overloaded
	        ConstIterator begin() const {
	        ~~~~~~~~~~~~~ ^
		4_cpp_iterators_3.cpp:125:11: note: previous definition is here
	        Iterator begin() const {
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

	class ConstIterator {
		T *m_pBegin{};
		// T *m_pEnd{};
	public:
		ConstIterator(T *pBegin) : m_pBegin{pBegin} {}
		
		// pre-increment
		ConstIterator operator ++() {
			++m_pBegin;
			return *this;
		}

		// post-increment
		ConstIterator operator ++(int) {
			auto temp(*this);
			++m_pBegin;
			return temp;
		}
		
		const T& operator *() {
			return *m_pBegin;
		}

		bool operator ==(const ConstIterator &other) const {
			return m_pBegin != other.m_pBegin;
		}

		bool operator !=(const ConstIterator &other) const {
			return !(m_pBegin == other.m_pBegin);
		}
	};
/*
		_cpp_iterators_3.cpp:132:16: error: functions that differ only in their return type cannot be overloaded
	        ConstIterator begin() const {
	        ~~~~~~~~~~~~~ ^
		4_cpp_iterators_3.cpp:125:11: note: previous definition is here
	        Iterator begin() const {
*/

	Iterator begin() {
		return Iterator{m_pBuffer};
	}
	Iterator end() {
		return Iterator{m_pBuffer + m_Size};
	}

	ConstIterator begin() const {
		return ConstIterator{m_pBuffer};
	}
	ConstIterator end() const {
		return ConstIterator{m_pBuffer + m_Size};
	}

	// for getting a const-iterator for a non-const container object.
	ConstIterator cbegin() {
		return ConstIterator{m_pBuffer};
	}

	ConstIterator cend() {
		return ConstIterator{m_pBuffer + m_Size};
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

	class ConstIterator {
		typename List::Node*  m_pHead;
	public:
		ConstIterator(typename List::Node*  pHead) : m_pHead{pHead} {}
		
		ConstIterator operator ++() {
			m_pHead = m_pHead->m_pNext;
			return *this;
		}

		ConstIterator operator ++(int) {
			auto temp(*this);
			m_pHead = m_pHead->m_pNext;
			return temp;
		}
		
		const T& operator *() {
			return m_pHead->m_Data;
		}

		bool operator ==(const ConstIterator& other) const {
			return m_pHead == other.m_pHead;
		}

		bool operator !=(const ConstIterator& other) const {
			return !(*this == other);
		}
	};


	Iterator begin() {
		return Iterator{m_pHead};
	}

	Iterator end() {
		return Iterator{nullptr};
	}

	ConstIterator begin() const {
		return ConstIterator{m_pHead};
	}

	ConstIterator end() const {
		return ConstIterator{nullptr};
	}

	ConstIterator cbegin() {
		return ConstIterator{m_pHead};
	}

	ConstIterator cend() {
		return ConstIterator{nullptr};
	}


private:
	Node *m_pHead ;
	size_t m_Size{} ;
};



#include <iostream>


template <typename Container>
void Print(const Container &container) {
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













