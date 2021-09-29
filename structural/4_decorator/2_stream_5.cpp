/*
	Issue with the final Decorator pattern from 2_stream_4.cpp implementation.


		Although we can easily add more decorator's, but when you are add a new Decorator you'll
		have to compose an output stream pointer and then in the implementation, you'll have to
		call, read and close from the corresponding methods.


		To make it simple for the clients to create new decorators, we can add a new class between
		OuputStream class and the CompressedOutputStream class.

		This class will be the Decorator base class, and that'll be responsible for storing a 
		pointer to OutputStream and forwarding the call to it.


		One important thing is that we should not let the clients create instance of this output 
		decorator base class, so it should be an Abstract class.
	   				So we will use the pure specifier on its methods.

		
		Second thing is all the output stream decorators should now inherit from output 
		Decorator base class.


										Composition
	|   OutputStream   |<------------------------------------;
	--------------------									 |
	|				   |									 |
	--------------------									 |
		    /_\											 	 |
			 |      Inheritance 							 |
			 |--------------------------------;				 |
			 |								  |				 |
			 |			  					  |				 |
	| FileOutputStream |			  | OutputDecorator  |----
	--------------------			  --------------------
	|				   |		      |		    		 |
	--------------------			  --------------------
											/_\
											 |
											 |
											 |		Inheritance
					;------------------------|----------------------------;
					|						 |							  |
					|						 |							  |	
			| CompressedStream |    | BufferedOutputStream |    | EncryptedOutputStream |
			--------------------    ------------------------    -------------------------
			|		    	   |    |		    	       |    |		    	   		|
			--------------------    ------------------------    -------------------------			
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
/////////////////////  InputDecorator.h
/////////////////////////////////////////////////
class InputDecorator : public InputStream {
	InputStream *m_pIs;
public:
	InputDecorator(InputStream *pIs) : m_pIs{pIs} {}

	bool Read(std::string &text) override = 0; 

	void Close() override  = 0;
};


bool InputDecorator::Read(std::string &text) {
	return m_pIs->Read(text);
}

void InputDecorator::Close() {
	m_pIs->Close();
}


/////////////////////////////////////////////////
/////////////////////  BufferedInputStream.h
/////////////////////////////////////////////////
class BufferedInputStream : public InputDecorator {
	char m_Buffer[512]{};
	using InputDecorator::InputDecorator;
public:
	// We just simulate buffering not actually implement it.
	bool Read(std::string &text) override {
		std::cout << "[Buffered Read]\n";
		InputDecorator::Read(text);
	}

	void Close() override {
		InputDecorator::Close();
	}
};


/////////////////////////////////////////////////
/////////////////////  DecryptedStream.h
/////////////////////////////////////////////////
class DecryptedStream : public InputDecorator {
	InputStream *m_pIs;
	using InputDecorator::InputDecorator;
public:
	bool Read(std::string &text) override {
		std::cout << "[DecryptedStream Read]\n";
		std::string encrypted;
		auto result = InputDecorator::Read(encrypted);
		text.resize(encrypted.size());
		std::transform(begin(encrypted), end(encrypted), begin(text), [](char ch) { return ch - 5; });
		return result;
	}

	void Close() override {
		InputDecorator::Close();
	}
};



/////////////////////////////////////////////////
/////////////////////  DecompressedInputStream.h
/////////////////////////////////////////////////
class DecompressedInputStream : public InputDecorator {
	InputStream *m_pIs;
	using InputDecorator::InputDecorator;
public:

	bool Read(std::string &text) override {
		std::cout << "[DecompressedInputStream Read]\n";
		std::string compressed;
		auto result = InputDecorator::Read(compressed);
		text.resize(compressed.size());
		std::transform(begin(compressed), end(compressed), begin(text), [](char ch) { return ch - 2; });
		return result;
	}

	void Close() override {
		InputDecorator::Close();
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

class FileOutputStream : public OutputStream {
	std::ofstream m_Writer;
public:
	FileOutputStream() = default;
	FileOutputStream(const std::string &file) {
		m_Writer.open(file);
		if (!m_Writer) {
			throw std::runtime_error("Could not open file for writing.");
		}
	}
	void Write(const std::string &text) override {
		m_Writer << text << "\n";
	}

	void Close() override {
		if (m_Writer.is_open()) {
			m_Writer.close();
		}
	}
};



/////////////////////////////////////////////////
/////////////////////  OutputDecorator.h
/////////////////////////////////////////////////
class OutputDecorator : public OutputStream {
	OutputStream *m_pOs;
public:
	OutputDecorator(OutputStream *pOs) : m_pOs{pOs} {}

	void Write(const std::string &text) override = 0; 

	void Close() override  = 0;
};


void OutputDecorator::Write(const std::string &text) {
	return m_pOs->Write(text);
}

void OutputDecorator::Close() {
	m_pOs->Close();
}


/////////////////////////////////////////////////
/////////////////////  BufferedOutputStream.h
/////////////////////////////////////////////////
class BufferedOutputStream : public OutputDecorator {
	char m_Buffer[512]{};
	using OutputDecorator::OutputDecorator;
public:

	// We just simulate buffering not actually implement it.
	void Write(const std::string &text) override {
		std::cout << "[Buffered Write]\n";
		OutputDecorator::Write(text);
	}

	void Close() override {
		OutputDecorator::Close();
	}
};


/////////////////////////////////////////////////
/////////////////////  EncryptedStream.h
/////////////////////////////////////////////////
class EncryptedStream : public OutputDecorator {
	using OutputDecorator::OutputDecorator;
public:

	void Write(const std::string &text) override {
		std::cout << "[EncryptedStream Write]\n";
		std::string encrypted{};
		encrypted.resize(text.size());
		std::transform(begin(text), end(text), begin(encrypted), [](char ch) { return ch + 5; });
		OutputDecorator::Write(encrypted);
	}

	void Close() override {
		OutputDecorator::Close();
	}
};




/////////////////////////////////////////////////
/////////////////////  CompressedOutputStream.h
/////////////////////////////////////////////////
class CompressedOutputStream : public OutputDecorator {
	using OutputDecorator::OutputDecorator;
public:

	void Write(const std::string &text) override {
		std::cout << "[CompressedOutputStream Write]\n";
		std::string compressed{};
		compressed.resize(text.size());
		std::transform(begin(text), end(text), begin(compressed), [](char ch) { return ch + 2; });

		OutputDecorator::Write(compressed);
	}

	void Close() override {

		OutputDecorator::Close();
	}
};




int main() {

	FileOutputStream fs{"mix.txt"};
	BufferedOutputStream bs{&fs};
	CompressedOutputStream cs(&bs);
	EncryptedStream es(&cs);

	es.Write("Some secret text");
	es.Close();

	FileInputStream fsInput("mix.txt");
	BufferedInputStream bsInput{&fsInput};
	DecompressedInputStream csInput{&bsInput};
	DecryptedStream esInput(&csInput);

	std::string text;
	esInput.Read(text);
	std::cout << text << std::endl;
	esInput.Close();

	return 0;
}



