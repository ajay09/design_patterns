/*
	Containers without iterators.
	

	Array
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
class Array : public Container<T> {
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

	void Add(const T& element) override {
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
	
	size_t Size() const override {
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
};

#include <iostream>

int main() {
	Array<int> numbers {1,2,3,4} ;
	numbers.Add(5) ;
	numbers.Add(6) ;
	numbers.Add(7) ;

	for (size_t i = 0; i < numbers.Size(); ++i) {
		std::cout << numbers[i] << " ";
	}

	std::cout << std::endl;

	return 0;
}