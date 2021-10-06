/*
	In the previous examples, we discussed how we can avoid proliferation of large number 
	of classes in our application.

	Bridge design pattern is useful when the abstraction and its implementation have to be
	varied independently. Now, if an abstraction has only one implementation, then there
	can be a one-to-one relationship between the abstraction and its implementation.


		And this situation is also called as the "Degenerate Bridge".
	    It also has an alternative name and that is the "Handle-Body", 
	    which is also an idiom in C++.


	In the Handle-Body idiom, 
	the abstraction is the Handle and the Implementer is the body, 

		It's also known as the Cheshire-Cat, Compilation-Firewall, Opaque-Pointer or D-pointer.


	But the most common alias of Handle-body is the pointer to Implementation or PIMPL.


PIML

	- PIMPL is simply a wrapper around a class, and it can be used to shield the clients
	  from the changes to the implementation class.
	
	- It can also prevent the compilation changes of the implementor from seeping into 
	  multiple source files.
		In this case, it's also known as the compilation firewall.

	- In the same way the PIMPL can hide the complex details of and Implementor class
	  from the client's.

	- It can also implement some extra functionality for the Implementation class.

*/




/*
	Let's implement a class that can be used to manage strings.	
*/

// you can define TRACE in the header file or through -D option
// cc -D TRACE -o a.cpp a.o
#ifdef TRACE
// #define TRACETHIS std::cout << __FUNCTION__ << std::endl;
// #define TRACETHIS std::cout << __func__ << std::endl;
// #define TRACETHIS std::cout << __PRETTY_FUNCTION__ << std::endl;
#define TRACETHIS std::cout << __LINE__ << " : " << __PRETTY_FUNCTION__ << "  " << __FILE__ << std::endl;
#else
#define TRACETHIS
#endif

#include <cstring>
#include <iostream>

class String {
	char *m_pString;
	size_t m_Length;

	void Create(const char *pstr) {
		m_Length = strlen(pstr);
		m_pString = new char[m_Length + 1];
		strcpy(m_pString, pstr);
	}
public:
	String() : String("") {
		TRACETHIS;
	}

	String(const char *pstr) {
		TRACETHIS;
		Create(pstr);
	}

	String(const String& other)	{
		TRACETHIS;
		Create(other.m_pString);
	}

	String(String&& other) noexcept {
		TRACETHIS;
		if (this != &other) {
			m_Length = other.m_Length;
			m_pString = other.m_pString;
			other.m_Length = 0;
			other.m_pString = nullptr;
		}
	}

	String& operator=(const String &other) {
		TRACETHIS;
		if (this != &other) {
			AssignString(other.m_pString);
		}
		return *this;
	}

	String& operator=(String &&other) noexcept {
		TRACETHIS;
		if (this != &other) {
			m_Length = other.m_Length;
			m_pString = other.m_pString;
			other.m_Length = 0;
			other.m_pString = nullptr;
		}
		return *this;
	}

	~String() {
		TRACETHIS;
		delete []m_pString;
	}

	size_t GetLength() const { return m_Length; }

	const char* GetString() const { return m_pString; }

	void AssignString(const char *pstr) {
		delete[] m_pString;
		Create(pstr);
	}
};

bool operator<(const String &left, const String &right) {
	return strcmp(left.GetString(), right.GetString()) < 0;
}

bool operator>(const String &left, const String &right) {
	return strcmp(left.GetString(), right.GetString()) > 0;
}

bool operator==(const String &left, const String &right) {
	return strcmp(left.GetString(), right.GetString()) == 0;
}

bool operator!=(const String &left, const String &right) {
	return !(left == right);
}



int main() {
	String s{"hello"};
	auto s2{s}; // copy constructor
	std::cout << "String : " << s.GetString() << std::endl;
	std::cout << "Length : " << s.GetLength() << std::endl;
	return 0;
}

/*
	Now suppose the application for which we wish to create the String class has
	memory constraints.

	And to save memory we decide that whenever you copy a string (assignment or constructor)
	we stend to share the same string across all its copies instead of allocating new
	memory for the same string.


	Thus we use the Handle-body idiom here, in such a way that the
	handle implements the sharing of the string and the body represents
	the implementation of the string.
*/


