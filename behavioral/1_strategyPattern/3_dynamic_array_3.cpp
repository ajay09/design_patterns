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
#include <mutex>

std::mutex mtx;

void Operate(Array<int> &data) {
	data[0] = 100;
	mtx.lock();
	for (int i = 0; i < 50; ++i) {
		data.Insert(i, i * 55);
	}
	mtx.unlock();
}


int main() {
	Array<int> data;

	for (int i = 0; i < 100; ++i)
		data.Add(i);

	std::thread t{Operate, std::ref(data)};

	// To enable thread Operate() to acquire lock befor the main thread.
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(500ms);

	mtx.lock();
	std::cout << data;
	mtx.unlock();

	t.join();

	return 0;
}



/*

	This still has issue.

	We still have "Race condition" in our code.

	By the time the Operate thread requests a lock the main thread will acquire it
	and the print the array and the array will print only 100 elements then the 
	Operate thread will acquire the lock and insert the 50 elements.



	Thus through syncronization we have ensured that only one thread can access
	the data object at a time.


	But this is a problem because the clients will have to manually apply locks
	when they access the methods of the array class.
	Thus we have to modify the array class so that it becomes thread safe, so that
	the clients don't have to deal with synchronisation themselves. Instead the
	array class will automatically take care of synchronising multiple thread
	access to its methods.
*/