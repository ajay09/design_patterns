/*
	Till now we have created dynamic strategies through virtual mechanism.
	But we can also create Static strategies :
		- Strategy classes can be implemented as class templates
		  Thus we need not create a common base class, only similar function signature
		
		- It can be used when strategy can be selected at compile time and need not be
		  changed at runtime. 

	
	- NullMutex and MutexLock don't inherit from a common class instead follow similar
	  function signatures. This is much better strategy than a dynamic strategy.
	    - We don't need to perform any null check
	    - This will be faster than the Dynamic Strategy as calls to Lock() and UnLock()
	       are non-polymorphic. 
	    - 
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


namespace DynamicStrategy 
{
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
		///////////////////////////////////////////
		/////////////////////   NullMutex.h
		///////////////////////////////////////////
		class NullMutex : public LockPolicy {
		public:
			void lock() override {}

			void unlock() override {}

			static NullMutex* GetInstance() {
				static NullMutex instance;
				return &instance;
			}
		};


		std::vector<T> m_Vector;

		LockPolicy *m_pLockPolicy;   // m_pLockPolicy is a dependecy for Array class
									 // and we have to inject this dependency.
	public:
		Array(LockPolicy *policy) : m_pLockPolicy{policy} {
			if (!m_pLockPolicy) {
				m_pLockPolicy = NullMutex::GetInstance();
			}
		}
		/* 
			We didn't use the setter method to set the Lock Policy because once the policy is set
			we need not change it for that object.
			Thus we inject the dependency using the constructor.
		*/

		void Add(const T& element) {
			m_pLockPolicy->lock();
			m_Vector.push_back(element);
			m_pLockPolicy->unlock();
		}

		void Insert(size_t index, const T& element) {
			m_pLockPolicy->lock();
			m_Vector.insert(begin(m_Vector) + index, element);
			m_pLockPolicy->unlock();
		}

		void Erase(size_t index) {
			m_pLockPolicy->lock();
			m_Vector.erase(begin(m_Vector) + index);
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
			m_pLockPolicy->lock();

			size_t size = m_Vector.size();
			
			m_pLockPolicy->unlock();

			return size;
		}

		template <typename K>
		friend std::ostream& operator<<(std::ostream& os, const Array<K>& arr);
	};

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
		arr.m_pLockPolicy->lock();

		for (auto element : arr.m_Vector) {
			os << element << ", ";
		}

		arr.m_pLockPolicy->unlock();

		return os << "\n";
	}
	//
};

///////////////////////////////////////////
/////////////////////   MutexLock.h
///////////////////////////////////////////
class MutexLock {
	mutable std::mutex m_Mtx;
public:
	virtual void lock() const {
		m_Mtx.lock();
	}

	virtual void unlock() const {
		m_Mtx.unlock();
	}

};

// MutexLock and NullMutex have the same function signature.
///////////////////////////////////////////
/////////////////////   NullMutex.h
///////////////////////////////////////////
class NullMutex {
public:
	void lock() const {}

	void unlock() const {}

	static NullMutex* GetInstance() {
		static NullMutex instance;
		return &instance;
	}
};	



template <typename T, typename LockPolicy = NullMutex>
class Array {

	std::vector<T> m_Vector;

	LockPolicy m_pLockPolicy; 
public:
	void Add(const T& element) {
		m_pLockPolicy.lock();
		m_Vector.push_back(element);
		m_pLockPolicy.unlock();
	}

	void Insert(size_t index, const T& element) {
		m_pLockPolicy.lock();
		m_Vector.insert(begin(m_Vector) + index, element);
		m_pLockPolicy.unlock();
	}

	void Erase(size_t index) {
		m_pLockPolicy.lock();
		m_Vector.erase(begin(m_Vector) + index);
		m_pLockPolicy.unlock();
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
		m_pLockPolicy.lock();

		size_t size = m_Vector.size();
		
		m_pLockPolicy.unlock();

		return size;
	}

	template <typename K, typename L>
	friend std::ostream& operator<<(std::ostream& os, const Array<K, L>& arr);
};

template <typename K, typename L>
std::ostream& operator<<(std::ostream& os, const Array<K, L>& arr) {
	arr.m_pLockPolicy.lock();

	for (auto element : arr.m_Vector) {
		os << element << ", ";
	}

	arr.m_pLockPolicy.unlock();

	return os << "\n";
}



#include <thread>


void Operate(Array<int, MutexLock> &data) {
	data[0] = 100;
	for (int i = 0; i < 50; ++i) {
		data.Insert(i, i * 55);
	}
}


int main() {
	Array<int, MutexLock> data;

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




