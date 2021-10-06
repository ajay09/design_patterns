/*
	Thus we use the Handle-body idiom here, in such a way that the
	handle implements the sharing of the string and the body represents
	the implementation of the string.

	Lets add a new class through which same string can be shared between different
	instances of the String class.


	We have an implementor class called String and we created a 
			   handle class called SharedString.

	The handle class implements sharing of the String objects so that the same String
	can be shared across teh different instances of the SharedString class.

	__________________ 			m_Strings   __________________
	|  SharedString  | -------------------->|     String     |
	------------------ 						------------------


			Modern name for Handle-Body idiom is PIMPL.
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









#include <unordered_map>

class SharedString {
	static std::unordered_map<String*, size_t*> m_Strings;
	String *m_pString;
	size_t m_Length;

	void RemoveString();
public:
	SharedString() = default;
	SharedString(const char *pstr);

	SharedString(const SharedString& other);
	SharedString(SharedString&& other) noexcept;

	SharedString& operator=(const SharedString &other);
	SharedString& operator=(SharedString &&other) noexcept;

	~SharedString();

	size_t GetLength() const;
	const char* GetString() const;
	void AssignString(const char *pstr);
};

std::unordered_map<String*, size_t*> SharedString::m_Strings;

void SharedString::RemoveString() {
	auto found = m_Strings.find(m_pString);
	if (found != m_Strings.end()) {
		if (--(*found->second) == 0) {	
			delete m_pString;
			auto pCount = found->second;
			delete pCount;
			m_Strings.erase(found);

		}
	}
}



SharedString::SharedString(const char* pstr) {
	auto found = std::find_if(begin(m_Strings), end(m_Strings), [pstr](auto p) {
		return *p.first == pstr;
	});
	if (found != m_Strings.end()) {
		++(*found->second);
		m_pString = found->first;
	}
	else {
		String* pTemp = new String{ pstr };
		m_Strings[pTemp] = new size_t{ 1 };
		m_pString = pTemp;
	}
}

SharedString::SharedString(const SharedString& other) {
	if (!other.m_pString)
		return;
	auto found = m_Strings.find(other.m_pString);
	if (found != m_Strings.end()) {
		m_pString = other.m_pString;
		++(*found->second);
	}
}

SharedString::SharedString(SharedString&& other) noexcept {
	m_pString = other.m_pString;
	other.m_pString = nullptr;

}

SharedString& SharedString::operator=(const SharedString& other) {
	if (this != &other) {
		if (m_pString) {
			RemoveString();
		}
		auto found = m_Strings.find(other.m_pString);
		if (found != m_Strings.end()) {
			m_pString = other.m_pString;
			++(*found->second);
		}

	}
	return *this;
}

SharedString& SharedString::operator=(SharedString&& other) noexcept {
	if (this != &other) {
		if (m_pString) {
			RemoveString();
		}
		m_pString = other.m_pString;
		other.m_pString = nullptr;
	}
	return *this;
}

SharedString::~SharedString() {
	if (m_pString)
		RemoveString();
}

size_t SharedString::GetLength() const {
	if (!m_pString)
		return 0;
	return m_pString->GetLength();
}

const char* SharedString::GetString() const {
	if (!m_pString)
		return "";
	return m_pString->GetString();
}

void SharedString::AssignString(const char* pstr) {
	if (m_pString) {
		RemoveString();
	}
	auto found = std::find_if(begin(m_Strings), end(m_Strings), [pstr](auto p) {
		return *p.first == pstr;
	});
	if (found != m_Strings.end()) {
		++(*found->second);
		m_pString = found->first;
	}
	else {
		String* pTemp = new String{ pstr };
		m_Strings[pTemp] = new size_t{ 1 };
		m_pString = pTemp;
	}
}





int main() {
	SharedString s{"hello"};
	auto s2{s}; // copy constructor
	
	SharedString s3;
	s3 = s;

	/*
		Although we are creating 3 SharedString objects, internally they are
		sharing the same String object.

		This is evident from the fact that String constructor is called only once.
	*/

	return 0;
}



