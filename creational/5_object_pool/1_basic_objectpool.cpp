/*

//////////////////////////////////////////////////
//////////////////////////////  SharedObject.h
//////////////////////////////////////////////////
// #pragma once
class SharedObject {
	// whether the object is in use or not.
	bool m_IsUsed{true};
public:
	void MethodA();
	void MethodB();
	// to reset the state of the sharedobject before it is given to the client.
	void Reset();

	void SetUsedState(bool);
	bool IsUsed() { return m_IsUsed; }
};

//////////////////////////////////////////////////
//////////////////////////////  SharedObject.cpp
//////////////////////////////////////////////////
#include <iostream>

void SharedObject::MethodA() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SharedObject::MethodB() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SharedObject::Reset() {
	std::cout << __PRETTY_FUNCTION__ << "  Resetting the state." << std::endl;
}

void SharedObject::SetUsedState(bool isUsed) {
	m_IsUsed = isUsed;
}

//////////////////////////////////////////////////
//////////////////////////////  ObjectPool.h
//////////////////////////////////////////////////
// #pragma once
// THis should have only one instance. So we implement it as Monostate.
#include <vector>
class ObjectPool {
	ObjectPool() = default;
	static std::vector<SharedObject*> m_PooledObjects;
public:
	// factory method
	static SharedObject& AcquireObject();
	static void ReleaseObject(SharedObject *rSo);
};


//////////////////////////////////////////////////
//////////////////////////////  ObjectPool.cpp
//////////////////////////////////////////////////

std::vector<SharedObject*> ObjectPool::m_PooledObjects;

SharedObject& ObjectPool::AcquireObject() {
	for (auto so : m_PooledObjects) {
		if (!so->IsUsed()) {
			std::cout << "[POOL] Returning an existing object\n";
			so->SetUsedState(true);
			so->Reset();
			return *so;
		}
	}
	std::cout << "[Pool] Creating a new object\n";
	SharedObject *so = new SharedObject();
	m_PooledObjects.push_back(so);
	std::cout << so << std::endl;
	return *so;
}

void ObjectPool::ReleaseObject(SharedObject *rSo) {
	for (auto so : m_PooledObjects) {
		// std::cout << so << "   " << rSo << std::endl;
		if (so == rSo) {
			std::cout << "[POOL] Releasing a leased object\n\n";
			so->SetUsedState(false);
			// you can reset the state here or in AcquireObject
			return;
		}
	}
	std::cout << "[POOL] Failed to release an object.\n";
}




//////////////////////////////////////////////////
//////////////////////////////  Client.cpp
//////////////////////////////////////////////////

int main() {
	SharedObject &s1 = ObjectPool::AcquireObject();
	s1.MethodA();
	s1.MethodB();

	// Since we are returning reference from ObjectPool::AcquireObject();
	// So use auto& instead of just auto.
	// Using auto will create a copy and not a reference.
	auto& s2 = ObjectPool::AcquireObject();
	s2.MethodA();
	s2.MethodB();

	ObjectPool::ReleaseObject(&s1);
	ObjectPool::ReleaseObject(&s2);

	auto s3 = ObjectPool::AcquireObject();
	s3.MethodA();

	return 0;
}




*/






















/*
The above implementation used raw pointers. Since we are only calling new and never
calling delete, thus to prevent memory leaks we should use smart pointer.
*/





//////////////////////////////////////////////////
//////////////////////////////  SharedObject.h
//////////////////////////////////////////////////
// #pragma once
class SharedObject {
	// whether the object is in use or not.
	bool m_IsUsed{true};
	SharedObject() = default; // made it private so that it can't be created directly.
public:
	void MethodA();
	void MethodB();
	// to reset the state of the sharedobject before it is given to the client.
	void Reset();

	void SetUsedState(bool);
	bool IsUsed() { return m_IsUsed; }

	friend class ObjectPool; // So that we can call the constructor to create SharedObject
};

//////////////////////////////////////////////////
//////////////////////////////  SharedObject.cpp
//////////////////////////////////////////////////
#include <iostream>

void SharedObject::MethodA() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SharedObject::MethodB() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SharedObject::Reset() {
	std::cout << __PRETTY_FUNCTION__ << "  Resetting the state." << std::endl;
}

void SharedObject::SetUsedState(bool isUsed) {
	m_IsUsed = isUsed;
}

//////////////////////////////////////////////////
//////////////////////////////  ObjectPool.h
//////////////////////////////////////////////////
// #pragma once
// THis should have only one instance. So we implement it as Monostate.
#include <vector>
#include <memory>

using std::shared_ptr;

using ObjectStore = std::vector<shared_ptr<SharedObject>>;
class ObjectPool {
	ObjectPool() = default;
	static ObjectStore m_PooledObjects;
public:
	// factory method
	static shared_ptr<SharedObject> AcquireObject();
	static void ReleaseObject(shared_ptr<SharedObject> rso);
};


//////////////////////////////////////////////////
//////////////////////////////  ObjectPool.cpp
//////////////////////////////////////////////////

ObjectStore ObjectPool::m_PooledObjects;

shared_ptr<SharedObject> ObjectPool::AcquireObject() {
	for (auto so : m_PooledObjects) {
		if (!so->IsUsed()) {
			std::cout << "[POOL] Returning an existing object\n";
			so->SetUsedState(true);
			so->Reset();
			return so;
		}
	}
	std::cout << "[Pool] Creating a new object\n";
	shared_ptr<SharedObject> so{new SharedObject()};
	m_PooledObjects.push_back(so);
	return so;
}

void ObjectPool::ReleaseObject(shared_ptr<SharedObject> rSo) {
	for (auto so : m_PooledObjects) {
		// std::cout << so << "   " << rSo << std::endl;
		if (so.get() == rSo.get()) {
			std::cout << "[POOL] Releasing a leased object\n\n";
			so->SetUsedState(false);
			// you can reset the state here or in AcquireObject
			return;
		}
	}
	std::cout << "[POOL] Failed to release an object.\n";
}




//////////////////////////////////////////////////
//////////////////////////////  Client.cpp
//////////////////////////////////////////////////

int main() {
	shared_ptr<SharedObject> s1 = ObjectPool::AcquireObject();
	s1->MethodA();
	s1->MethodB();

	auto s2 = ObjectPool::AcquireObject();
	s2->MethodA();
	s2->MethodB();

	ObjectPool::ReleaseObject(s1);
	ObjectPool::ReleaseObject(s2);

	auto s3 = ObjectPool::AcquireObject();
	s3->MethodA();

	return 0;
}


