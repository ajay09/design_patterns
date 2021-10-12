/*
	A thread-safe Array class using Strategy Pattern.
*/

#include <vector>
#include <iostream>
#include <mutex>

namespace V1
{
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
};




template <typename T>
class Array {
	std::vector<T> m_Vector;
	mutable std::mutex m_Mtx;

	bool m_IsMultithreaded; // to decide whether to apply locks or not.
							// I true we will apply the locks otherwise not.
							// This will be specified by the clients through the constructor.
public:
	Array(bool threading=false) : m_IsMultithreaded{threading} {
	}

	void Add(const T& element) {
		if (m_IsMultithreaded)
			m_Mtx.lock();
		m_Vector.push_back(element);
		if (m_IsMultithreaded)
			m_Mtx.unlock();
	}

	void Insert(size_t index, const T& element) {
		if (m_IsMultithreaded)
			m_Mtx.lock();
		
		m_Vector.insert(begin(m_Vector) + index, element);
		
		if (m_IsMultithreaded)
			m_Mtx.unlock();
	}

	void Erase(size_t index) {
		if (m_IsMultithreaded)
			m_Mtx.lock();
		
		m_Vector.erase(begin(m_Vector) + index);

		if (m_IsMultithreaded)
			m_Mtx.unlock();
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
		if (m_IsMultithreaded)
			m_Mtx.lock();

		size_t size = m_Vector.size();
		
		if (m_IsMultithreaded)
			m_Mtx.unlock();

		return size;
	}

	template <typename K>
	friend std::ostream& operator<<(std::ostream& os, const Array<K>& arr);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
	if (arr.m_IsMultithreaded)
			arr.m_Mtx.lock();

	for (auto element : arr.m_Vector) {
		os << element << ", ";
	}

	if (arr.m_IsMultithreaded)
			arr.m_Mtx.unlock();
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
	Array<int> data{true};

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




