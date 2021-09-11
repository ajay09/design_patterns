/*
	Shooting actors game

	Now our object pool handles creation of both Alien and Missile
	The ActorPool will create the instances of different types of Actors through a Factory Method.
	Thus we reduced the coupling between the ActorPool and the Actors that it instantiates.

	But what if we want to manage different kinds of objects in our Pool.
	Currently the ActorPool manages objects of type Actor only!

	To make a Generic Pool Class that can be used to manage any kind of object
	we take help of templates.
*/

// Represents all kinds of actors in the game.
//////////////////////////////////////////////////
/////////////////////////// ObjectPool.h
//////////////////////////////////////////////////
// #pragma once
#include <vector>
#include <iostream>

template <typename T>
class ObjectPool {
	struct ObjectInfo {
		bool m_IsUsed{};
		T *m_pObject{};
	};
	static std::vector<ObjectInfo> m_PooledObjects;
public:
	static T* Acquire() {
		for (auto &obj : m_PooledObjects) {
			if (!obj.m_IsUsed) {
				obj.m_IsUsed = true;
				std::cout << "[POOL] Returning an existing object\n";
				return obj.m_pObject;
			}
		}
		std::cout << "[POOL] Creating a new object.\n";
		auto pObj = new T{};
		m_PooledObjects.push_back({true, pObj});
		return pObj;
	}

	static void Release(const T *pObj) {
		for (auto &obj : m_PooledObjects) {
			if (obj.m_pObject == pObj) {
				obj.m_IsUsed = false;
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
			delete obj.m_pObject;
		}
		m_PooledObjects.clear();
	}
};



template <typename T>
std::vector<typename ObjectPool<T>::ObjectInfo> ObjectPool<T>::m_PooledObjects;


int main() {
	using IntPool = ObjectPool<int>;
	auto p1 = IntPool::Acquire();
	*p1 = 1;
	auto p2 = IntPool::Acquire();
	*p2 = 2;
	auto p3 = IntPool::Acquire();
	*p3 = 3;

	IntPool::Release(p1);
	IntPool::Release(p2);

	auto p4 = IntPool::Acquire();
	*p4 = 4;

	IntPool::Destroy();
	return 0;
}