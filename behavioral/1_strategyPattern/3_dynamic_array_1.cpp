/*
	Another way of implementing the Strategy Pattern.

	Suppose we want to use this class in a multi-threaded application
*/

#include <vector>
#include <iostream>

template <typename T>
class Array {
	std::vector<T> m_Vector;
public:
	void Add(const T& element) {
		m_Vector.push_back(element);
	}

	void Insert(size_t index, const T& element) {
		m_Vector.insert(begin(m_Vector) + index, element);
	}

	void Erase(size_t index) {
		m_Vector.erase(begin(m_Vector) + index);
	}

	T& operator[](size_t index) {
		return m_Vector[index];
	}

	const T& operator[](size_t index) const {
		return m_Vector[index];
	}

	size_t Size() const {
		return m_Vector.size();
	}

	template <typename K>
	friend std::ostream& operator<<(std::ostream& os, const Array<K>& arr);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
	for (auto element : arr.m_Vector) {
		os << element << ", ";
	}
	return os << "\n";
}


#include <thread>

void Operate(Array<int> &data) {
	data[0] = 100;
	for (int i = 0; i < 50; ++i) {
		data.Insert(i, i * 55);
	}
}


int main() {
	Array<int> data;

	for (int i = 0; i < 100; ++i)
		data.Add(i);

	std::thread t{Operate, std::ref(data)};

	std::cout << data;

	t.join();


	return 0;
}



/*
	The values in data will depend upon the order of execution of the two threads operating on it.

	This is called a "Race Condition". (because the thread race to access the resource)
	Because one thread is inserting data and the other is reading data.

	Thus when a data object is accessed by multiple threads we should apply a lock on it.
*/


