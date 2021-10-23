/*
	Document Framework

	Template Method pattern is common in frameworks as it allows the framework
	to provide some basic implementation which can be customized by the user.

	Lets create a Document Framework class which can be used by the clients to define
	their own file types. (Similar to what we discussed in the Factory Method Design Pattern)



	Document provides the functionaliyt
	of managing the application data.                Application uses the client implementation
	-------------------								-------------------	through the base-class document.							
	|    Document	  |<----------------------------|   Application	  |
	-------------------								-------------------									
	|  Read()  		  |								|  Write() 		  |								
	|  Write() 		  |								-------------------
	-------------------	
		   /_\
		    |
		    |------------------------------------;
	-------------------					-------------------
	|  TextDocument   |					|     Numbers     |
	-------------------					-------------------
	|  Read()  		  |					|  Read()  		  |
	|  Write() 		  |					|  Write() 		  |
	-------------------					-------------------
	Document is sub-classed by clients
	to support their own file types.


	We see that there is a lot of code duplication here.
	The subclasses should only focus on saving and loading the data
	and not on stream management.

	
	Thus we implement the Template Method Design pattern
	to avoid code duplication for Save and Load methods.
	They will also provide hooks that the subclasses can
	use to provide their own implementation.
*/

//////////////////////////////////////////
////////////////////////  Document.h
//////////////////////////////////////////
#include <fstream>
class Document {
protected:
	std::fstream m_Stream;
	bool m_IsModified;
public:
	Document() : m_IsModified{false} {}

	virtual void Save() = 0;
	virtual void Load() = 0;

	virtual ~Document() = default;
};



//////////////////////////////////////////
////////////////////////  TextDocument.h
//////////////////////////////////////////
#include <string>
class TextDocument : public Document {
	std::string m_Text;
public:
	void Load() override;
	void Save() override;

	void SetText(std::string text);

	void Print();
};

#include <iostream>

void TextDocument::Load() {
	if (m_IsModified) {
		std::cout << "Save current changes first\n";
		return;
	}
	std::cout << "Name of the file to load? ";
	std::string fileName{};
	std::getline(std::cin, fileName); 	   // use getline to get inputs.
	m_Stream.open(fileName, m_Stream.in);
	std::getline(m_Stream, m_Text);
}

void TextDocument::Save() {
	if (!m_Stream.is_open()) {
		std::cout << "Name of the file to save? ";
		std::string fileName{};
		std::getline(std::cin, fileName); 	   // use getline to get inputs.
		m_Stream.open(fileName, m_Stream.out);
	}
	m_Stream.seekp(0);
	m_Stream << m_Text;
	m_IsModified = false;
}

void TextDocument::SetText(std::string text) {
	m_Text = std::move(text);
	m_IsModified = true;
}


void TextDocument::Print() {
	std::cout << "TextDocument : " << m_Text << std::endl;
}






//////////////////////////////////////////
////////////////////////  Numbers.h
//////////////////////////////////////////
class Numbers : public Document {
	int m_Number;
public:
	void SetNumber(int num) {
		m_Number = num;
		m_IsModified = true;
	}

	void Print() {
		std::cout << m_Number;
	}

	void Load() override {
		if (m_IsModified) {
			std::cout << "Save current changes first\n";
			return;
		}
		std::cout << "Name of the file to load? ";
		std::string fileName{};
		std::getline(std::cin, fileName); 	   // use getline to get inputs.
		m_Stream.open(fileName, m_Stream.in);
		std::string version;
		std::getline(m_Stream, version);
		if (version == "v1.0")
			m_Stream >> m_Number;
	}

	void Save() override {
		if (!m_Stream.is_open()) {
			std::cout << "Name of the file to save? ";
			std::string fileName{};
			std::getline(std::cin, fileName); 	   // use getline to get inputs.
			m_Stream.open(fileName, m_Stream.out);
		}
		m_Stream.seekp(0);
		m_Stream << "v1.0\n";
		m_Stream << m_Number;
		m_IsModified = false;
	}
};




void Text() {
	TextDocument txt{};

	// txt.SetText("Some user data");
	// txt.Save();

	txt.Load();
	txt.Print();
}



int main() {
	Numbers nm{};
	// nm.SetNumber(999);
	// nm.Save();
	nm.Load();
	nm.Print();
	return 0;
}





