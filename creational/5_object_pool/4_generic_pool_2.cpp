/*
	Shooting actors game

	The current implementation is not threadsafe. Lets make it threadsafe.


	How do we create instances if the consturctor for an Object class is private.
	Thus we use another design to create objects using Allocator. Instead
	of using new and delete directly in the ObjectPool



	Here we have implemented another pattern =>  Strategy Pattern.
												 By providing a Custom Allocator for any object
												 inside the ObjectPool


	We can also use the Strategy pattern to implement :
	 - locks to be used when used with multiple threads and not when there is only one thread.
	 - Also client should be able to provide their own locks for locking.
*/



//////////////////////////////////////////////////
/////////////////////////// Allocator.h
//////////////////////////////////////////////////
template <typename T>
class DefaultAllocator {
public:
	T* operator()() {
		return new T{};
	}

	void operator()(T* p){
		delete p;
	}

	// to reset the state of the allocator when you call Destory() on object pool.
	void Reset() {

	}
};


// Represents all kinds of actors in the game.
//////////////////////////////////////////////////
/////////////////////////// ObjectPool.h
//////////////////////////////////////////////////
// #pragma once
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

template <typename T, typename AllocatorT=DefaultAllocator<T>>
class ObjectPool {
	static std::mutex mtx;
	static int InUse;
	static int Free;
	struct ObjectInfo {
		bool m_IsUsed{};
		T *m_pObject{};
	};
	static std::vector<ObjectInfo> m_PooledObjects;
	static AllocatorT m_Allocator;
public:
	static T* Acquire() {
		std::lock_guard<std::mutex> lock(mtx);
		std::cout << "InUse : " << InUse << "   Free : " << Free << "  Total : " << m_PooledObjects.size() << std::endl;
		std::flush(std::cout);
		for (auto &obj : m_PooledObjects) {
			if (!obj.m_IsUsed) {
				obj.m_IsUsed = true;
				std::cout << "[POOL] Returning an existing object\n";
				InUse++;
				Free--;
				return obj.m_pObject;
			}
		}
		std::cout << "[POOL] Creating a new object.\n";
		auto pObj = m_Allocator();
		m_PooledObjects.push_back({true, pObj});
		InUse++;
		return pObj;
	}

	static void Release(const T *pObj) {
		std::cout << "InUse : " << InUse << "   Free : " << Free << "  Total : " << InUse + Free << std::endl;
		for (auto &obj : m_PooledObjects) {
			if (obj.m_pObject == pObj) {
				obj.m_IsUsed = false;
				{
					std::lock_guard<std::mutex> lock(mtx);
					InUse--;
					Free++;
				}
				break;
			}
		}
	}

	static void Destroy() {
		for (auto &obj : m_PooledObjects) {
			if (obj.m_IsUsed) {
				std::cout << "[WARNING] Deleting an object still in use.\n";
			} else {
				std::cout << "[POOL] Deleting an object.\n";
			}
			m_Allocator(obj.m_pObject);
		}
		m_Allocator.Reset();
		m_PooledObjects.clear();
	}
};



template <typename T, typename A>
std::vector<typename ObjectPool<T, A>::ObjectInfo> ObjectPool<T, A>::m_PooledObjects;

template <typename T, typename A>
std::mutex ObjectPool<T, A>::mtx;

template <typename T, typename A>
A ObjectPool<T, A>::m_Allocator;

template <typename T, typename A>
int ObjectPool<T, A>::InUse{0};
template <typename T, typename A>
int ObjectPool<T, A>::Free{0};

using IntPool = ObjectPool<int>;

void seq1() {
	auto p1 = IntPool::Acquire();
	*p1 = 1;
	IntPool::Release(p1);
	auto p2 = IntPool::Acquire();
	*p2 = 2;
	auto p3 = IntPool::Acquire();
	*p3 = 3;

	IntPool::Release(p1);
	IntPool::Release(p2);

	auto p4 = IntPool::Acquire();
	*p4 = 4;
}

void seq2() {
	auto p1 = IntPool::Acquire();
	*p1 = 1;
	auto p2 = IntPool::Acquire();
	*p2 = 2;
	auto p3 = IntPool::Acquire();
	*p3 = 3;
	auto p5 = IntPool::Acquire();
	*p5 = 3;

	IntPool::Release(p1);

	auto p4 = IntPool::Acquire();
	*p4 = 4;
}


// Constructor of this class is private.
class TestObject {
	TestObject() = default;
public:
	void Foo() {}

	friend class TestAllocator;
};

class TestAllocator {
public:
	TestObject* operator()() {
		return new TestObject{};
	}
	void operator()(TestObject *p) {
		delete p;
	}
	void Reset() {

	}
};


int main() {
	std::thread t1(seq1);
	std::thread t2(seq2);
	std::thread t3(seq1);
	
	auto p1 = IntPool::Acquire();
	*p1 = 1;
	auto p2 = IntPool::Acquire();
	*p2 = 2;
	auto p3 = IntPool::Acquire();
	*p3 = 3;

	t3.join();

	IntPool::Release(p1);
	IntPool::Release(p2);

	auto p4 = IntPool::Acquire();
	*p4 = 4;

	t1.join();
	t2.join();

	IntPool::Destroy();

	auto p6 = ObjectPool<TestObject, TestAllocator>::Acquire();
	p6->Foo();

	return 0;
}


