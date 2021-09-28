/*
	Remote Proxy

	We will now use the Sprite Class as a COM component.

	Sprite class is now in the Server and the Client wants to use it.

	In COM, if you want to use a component remotely, then you have to create a
	proxy Stub dll.
	When the client process requests to the component, it will automatically load the 
	proxy Stub dll in its address space and that will also cause the server to start.
	The server will also load this proxy Stub dll, and that's how the client process
	and the server process will communicate with each other.


	So we have to create three projects here, one for the client, 
	other for the proxy Stub dll, and third for the server.


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


