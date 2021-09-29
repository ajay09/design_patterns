/*
	Create a file stream library, which will provide classes that'll help you perform, 
	read and write operations on files.

	So instead of component, we will have a class called as InputStream.
	And ConcreteComponent will be file input stream.

	Input stream will provide the interface that will be implemented by the FileInputStream.
	So using FileInputStream, we can read from a file.

	
	In the same way, we will have another class called as Output Stream, and 
	that will be inherited in a class called FileOutput Stream, which will 
	provide the functionality of writing into the files.

	
	So we will create these two parallel class hierarchies for performing 
	read and write operations on the files.
*/

/////////////////////////////////////////////////
/////////////////////  InputStream.h
/////////////////////////////////////////////////
#include<string>

class InputStream {
public:
	// text is the output parameter.
	virtual bool Read(std::string &text) = 0;
	virtual void Close() = 0;
	virtual ~InputStream() = default;
};


/////////////////////////////////////////////////
/////////////////////  FileInputStream.h
/////////////////////////////////////////////////
#include <fstream>
#include <stdexcept>
#include <iostream>

class FileInputStream : public InputStream {
	std::ifstream m_Reader;
public:
	FileInputStream() = default;
	
	FileInputStream(const std::string &file) {
		m_Reader.open(file);
		// Stream classes contain the bool type conversion operator
		// so the straem object can be used directly in boolean expressions.
		// operator! is overloaded for ifstream
		if (!m_Reader) {
			throw std::runtime_error{"Could not open the file for reading."};
		}
	}

	// here text is the output parameter.
	bool Read(std::string &text) override {
		text.clear();
		std::getline(m_Reader, text);
		return !text.empty();
	}

	void Close() override {
		if (m_Reader.is_open()) {
			m_Reader.close();
		}
	}

};


/////////////////////////////////////////////////
/////////////////////  OutputStream.h
/////////////////////////////////////////////////
#include<string>

class OutputStream {
public:
	virtual void Write(const std::string &text) = 0;
	virtual void Close() = 0;
	virtual ~OutputStream() = default;
};



/////////////////////////////////////////////////
/////////////////////  FileOutputStream.h
/////////////////////////////////////////////////
#include <string>
#include <fstream>

class FileOutputStream {
	std::ofstream m_Writer;
public:
	FileOutputStream() = default;
	FileOutputStream(const std::string &file) {
		m_Writer.open(file);
		if (!m_Writer) {
			throw std::runtime_error("Could not open file for writing.");
		}
	}
	void Write(const std::string &text) {
		m_Writer << text;
	}

	void Close() {
		if (m_Writer.is_open()) {
			m_Writer.close();
		}
	}
};






void Read() {
	FileInputStream f{"design_doc"};
	std::string text;
	f.Read(text);
	std::cout << text << std::endl;
	// the destructor of f will automatically close the file.
}


void Write() {
	FileOutputStream output{"text.txt"};
	output.Write("First Line");
	output.Write("Second Line");
	output.Write("Third Line");
}



int main() {
	Read();
	Write();
	return 0;
}



