/*
	Remote Proxy

	A remote proxy is used when you want to use the features of a class that resides in
	a different address space.
	Till now in all of the examples, classes that we have been using and instantiating
	are int he same process address space.


	What if the class wish to use resides in different address space?


	The client process will have to use some kind of RPC mechanism to
	invoke the methods of the server process and the data will have to be returned.

	Implementation for the client and server will become complicated as we'll have to
	deal with the RPC APIs.
	To avoid this complication we can use a   "Remote Proxy"


	Remote proxy is simply a class on the client side and will have tha same interface
	as the server class.
	The client will use the interfaces of the proxy and won't realise that it's just a
	proxy and doesn't contain the actual implementation. Thus the client calls into the
	proxy and the proxy will communicate over the network with this particular component.


	We may also have another type of proxy called a Stub.
	Stub is a remote proxy on the server side. And the server will think of stub as the client.
*/

using HRESULT = unsigned long;
#define S_OK 0

// We implement the COM for this example
// In Component Object Model methods alwasy return HRESULT which signify either success or failure.
/////////////////////////////////////////////
//////////////////////  IAnimate.h
////////////////////////////////////////////
// #include <objbase.h>

class IAnimate {
public:
	virtual HRESULT SetImage(unsigned char image) = 0;
	virtual HRESULT Animate(int durations) = 0;

	virtual ~IAnimate() = default;
};



/////////////////////////////////////////////
//////////////////////  Sprite.h
////////////////////////////////////////////
#include <thread>
#include <iostream>

class Sprite : public IAnimate {
	unsigned char m_Image;
public:
	HRESULT SetImage(unsigned char image) {
		m_Image = image;
		return S_OK;
	}

	HRESULT Animate(int duration) {
		for (int i = 0; i < duration; ++i) {
			std::cout << m_Image;
			flush(std::cout);
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(1000ms);
		}
		std::cout << std::endl;
		return S_OK;
	}


};




/////////////////////////////////////////////
//////////////////////  client
////////////////////////////////////////////

void Draw(IAnimate *p) {
	p->SetImage('#');
	p->Animate(5);
}

int main() {
	Sprite s;
	Draw(&s);

	return 0;
}


/*
	What if the Sprite class resides in different address space?
	How then we can use the Sprite class?
*/


