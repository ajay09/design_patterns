#include <iostream>
class A {
public:
	void CallA() {
		std::cout << "[A] CallA()" << std::endl;
	}
};


class B {
public:
	void CallB() {
		std::cout << "[B] CallB()" << std::endl;
	}
};


class C {
public:
	void CallC() {
		std::cout << "[C] CallC()" << std::endl;
	}
};

/*
	These are the classes that the client has to use and these are part of some system.
*/


class Client {
	A *m_pA;
	B *m_pB;
	C *m_pC;
public:
	Client() {
		m_pA = new A{};
		m_pB = new B{};
		m_pC = new C{};
	}

	void Invoke() {
		m_pA->CallA();
		m_pB->CallB();
		m_pC->CallC();
	}

	~Client() {
		delete m_pA;
		delete m_pB;
		delete m_pC;
	}

};

/*

	Now there can be two problems here :
	- Assume that the interfaces of these components in the system (class A, B and C) are complex to use.
	- The client is tightly coupled to the classes in the system. If any of these classes
	   change then the client has to change.
*/

class Facade {
	A *m_pA;
	B *m_pB;
	C *m_pC;
public:
	Facade() {
		m_pA = new A{};
		m_pB = new B{};
		m_pC = new C{};
	}

	~Facade() {
		delete m_pA;
		delete m_pB;
		delete m_pC;
	}

	void Use() {	
		m_pA->CallA();
		m_pB->CallB();
		m_pC->CallC();
	}	
};



class Client2 {
	Facade *m_pF;
public:
	Client2() {
		m_pF = new Facade();
	}

	void Invoke() {
		m_pF->Use();
	}

	~Client2() {
		delete m_pF;
	}
};

/*
	Classes A, B and C are part of a system. The client2 doesn't use them directly.
	Instead we have created a Facade here, which converts the complex interface of the
	subsystem classes into a simple interface because of that the coupling between the
	sub-system classes and the client reduces. And even if we change the subsystem classes
	it won't affect the client.
*/


int main() {
	Client c;
	c.Invoke();

	return 0;
}

