/*
	Another way of implementing the Strategy Pattern.

	Suppose we want to use this class in a multi-threaded application.


	We wish to make the Array class thread-safe so that the client doesn't have
	to deal with locking and unlocking when it invokes methods of the Array class.


	But there is another issue now :
		If we want to use this in a single-threaded application, it will
		still apply locks when a single-thread calls its methods.
		And locking is unnecessary in a single-threaded application.


		Thus we would like to modify the Array class so that when it
		is used in a single-threaded application it will not apply any
		locks and when it is used in a multi-threaded application it
		will use the locks.
*/

#include <vector>
#include <iostream>
#include <mutex>

template <typename T>
class Array {
	std::vector<T> m_Vector;
	mutable std::mutex m_Mtx;
public:
	void Add(const T& element) {
		std::lock_guard<std::mutex> lock{m_Mtx};
		m_Vector.push_back(element);
	}

	void Insert(size_t index, const T& element) {
		std::lock_guard<std::mutex> lock{m_Mtx};
		m_Vector.insert(begin(m_Vector) + index, element);
	}

	void Erase(size_t index) {
		std::lock_guard<std::mutex> lock{m_Mtx};
		m_Vector.erase(begin(m_Vector) + index);
	}

	// The next 2 methods need not be thread-safe because
	// they are not modifying the state of the Array object.
	T& operator[](size_t index) {
		return m_Vector[index];
	}

	const T& operator[](size_t index) const {
		return m_Vector[index];
	}

	size_t Size() const {
		std::lock_guard<std::mutex> lock{m_Mtx};
		return m_Vector.size();
	}

	template <typename K>
	friend std::ostream& operator<<(std::ostream& os, const Array<K>& arr);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
	std::lock_guard<std::mutex> lock{arr.m_Mtx};
	for (auto element : arr.m_Vector) {
		os << element << ", ";
	}
	return os << "\n";
}


#include <thread>
#include <mutex>


namespace ManualLock {
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
};

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

	// To enable thread Operate() to acquire lock befor the main thread.
	using namespace std::chrono_literals;
	
	std::this_thread::sleep_for(500ms);

	std::cout << data;

	t.join();

	return 0;
}




