/*
	We can replace the RealSubject object in the client code
	with the Proxy object and the client code will not see the change.

	The RealSubject instance will be created only when the Request() is invoked.


	The proxy acts as a representative of the real object and it provides some
	additional behavior when the real subject is invoked.
*/



///////////////////////////////////////////////
//////////////////  Subject.h
///////////////////////////////////////////////
class Subject {
public:
	virtual void Request() = 0;
	virtual ~Subject() = default;
};



///////////////////////////////////////////////
//////////////////  RealSubject.h
///////////////////////////////////////////////
#include <iostream>

class RealSubject : public Subject{
public:
	void Request() override {
		std::cout << "[RealSubject] Request processed\n";
	}
};


// Proxy class will also inherit from Subject class
// because it should have the same interface as 
// the Subject class.
///////////////////////////////////////////////
//////////////////  Proxy.h
///////////////////////////////////////////////
#include <iostream>

class Proxy : public Subject{
	RealSubject *m_pRealSubject;
public:
	Proxy() : m_pRealSubject{nullptr} {}

	void Request() override {
		if (m_pRealSubject == nullptr) {
			std::cout << "[Proxy] Creating RealSubject\n";
			m_pRealSubject = new RealSubject{};
		}
		std::cout << "[Proxy] Additional Behavior.\n";
		m_pRealSubject->Request();
	}

	~Proxy() {
		delete m_pRealSubject;
	}
};



// Client
void Operate(Subject *s) {
	s->Request();
}


int main() {
	// RealSubject *sub = new RealSubject{};
	Proxy *sub = new Proxy{};
	Operate(sub);
}




