/*
	A thread-safe Array class using Strategy Pattern.


	Applying Strategy Pattern
		Our previous approach led to a lot of conditional statements.
		In this case the different algo are locking and not-locking.
		Thus we take these algo out and encapsulate them in their own
		classes.


	- Create a base-class that will define the interface of locking and unlocking (for any object)
	- Create sub-classes that will decide what kind of mutex to use for locks.


	Problem with current :
		- What if the use passes nullptr while creating instance of Array?
			(i.e. the client may not specify a strategy.)
		- How do we indicate that we wish to use Array in Single-threaded app?


	Although adding 
		if (arr.m_pLockPolicy)
	solved the previous problem, but now our code looks similar to that in 3_dynamic_array_5.cpp
	Thus we need a better approach to solve this issue.

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


namespace V2
{
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
};


///////////////////////////////////////////
/////////////////////   LockPolicy.h
///////////////////////////////////////////
class LockPolicy {
public:
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual ~LockPolicy() = default;
};


///////////////////////////////////////////
/////////////////////   MutexLock.h
///////////////////////////////////////////
class MutexLock : public LockPolicy {
	std::mutex m_Mtx;
public:
	virtual void lock() override {
		m_Mtx.lock();
	}

	virtual void unlock() override {
		m_Mtx.unlock();
	}

};

template <typename T>
class Array {
	std::vector<T> m_Vector;

	LockPolicy *m_pLockPolicy;   // m_pLockPolicy is a dependecy for Array class
								 // and we have to inject this dependency.
public:
	Array(LockPolicy *policy) : m_pLockPolicy{policy} {
	}
	/* 
		We didn't use the setter method to set the Lock Policy because once the policy is set
		we need not change it for that object.
		Thus we inject the dependency using the constructor.
	*/

	void Add(const T& element) {
		if (m_pLockPolicy)            // adding the if statement solve both the issues senn in the previous implementation.
			m_pLockPolicy->lock();
		m_Vector.push_back(element);
		if (m_pLockPolicy)
			m_pLockPolicy->unlock();
	}

	void Insert(size_t index, const T& element) {
		if (m_pLockPolicy)
			m_pLockPolicy->lock();
		m_Vector.insert(begin(m_Vector) + index, element);
		if (m_pLockPolicy)
			m_pLockPolicy->unlock();
	}

	void Erase(size_t index) {
		if (m_pLockPolicy)
			m_pLockPolicy->lock();
		m_Vector.erase(begin(m_Vector) + index);
		if (m_pLockPolicy)
			m_pLockPolicy->unlock();
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
		if (m_pLockPolicy)
			m_pLockPolicy->lock();

		size_t size = m_Vector.size();
		
		if (m_pLockPolicy)
			m_pLockPolicy->unlock();

		return size;
	}

	template <typename K>
	friend std::ostream& operator<<(std::ostream& os, const Array<K>& arr);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
	if (arr.m_pLockPolicy)
		arr.m_pLockPolicy->lock();

	for (auto element : arr.m_Vector) {
		os << element << ", ";
	}

	if (arr.m_pLockPolicy)
		arr.m_pLockPolicy->unlock();

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
	Array<int> data{new MutexLock{}};

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




