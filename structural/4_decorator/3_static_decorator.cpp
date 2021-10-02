/*
	The decorator we have implemented till now is Dynamic Decorator, because the behavior
	is added at runtime dynamically.


	Static Decorator
	- Decorator is chosen and applied at compile time.
	- Cannot be changed at runtime.
	- It is preferrable because it doesn't use virtual mechanism.
		(virtual dispatch has an associated overhead.)
	- Can be implemented using mixin classes.
			Mixin
			A mixin is a class whose methods can be used by other classes without explicitly
			being a parent class. (without using inheritance.)
			The behavior is used through inheritance but without using explicit inheritance.
			Thus such classes are said to be included instead of inherited.
	
	- Using the Mixin we can add behavior at compile time.
	- In Static Decorator the behavior will not be added to the object but to the class.
	
*/


/////////////////////////////////////////////////
/////////////////////  FileInputStream.h
/////////////////////////////////////////////////
#include <fstream>
#include <stdexcept>
#include <iostream>
// In this case we don't need FileInputStream to inherit from InputStream class
class FileInputStream {
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
	bool Read(std::string &text) {
		text.clear();
		std::getline(m_Reader, text);
		return !text.empty();
	}

	void Close() {
		if (m_Reader.is_open()) {
			m_Reader.close();
		}
	}

};


/*
	Each decorator will inherit from the type name and we have added
	a variadic constructor that can accept any number of parameters and
	whaterver arguments that are passed are forwarded to the  
	constructor of the base class.
	Thus we use "Perfect forwarding" to support this.
*/
/////////////////////////////////////////////////
/////////////////////  DecryptedStream.h
/////////////////////////////////////////////////
// This is not an explicit inheritance. It is called "Include Relationship"
// Since this is a class template we will define everything in the header file.
template <typename T>
class DecryptedStream : public T {
public:
	// The DecryptedStream constructor should be able to accept any kind of parameters.
	// Thus we convert it into a member template.
	template <typename...Args> // variadic template.
	DecryptedStream(Args&&...args) : // forwarding reference
				T( std::forward<Args>(args)... ) {}

	bool Read(std::string &text) {
		std::cout << "[DecryptedStream Read]\n";
		std::string encrypted;
		auto result = T::Read(encrypted);
		text.resize(encrypted.size());
		std::transform(begin(encrypted), end(encrypted), begin(text), [](char ch) { return ch - 5; });
		return result;
	}

	void Close() {
		T::Close();
	}
};




/////////////////////////////////////////////////
/////////////////////  BufferedInputStream.h
/////////////////////////////////////////////////
template <typename T>
class BufferedInputStream : public T {
	char m_Buffer[512]{};
public:
	template <typename...Args>
	BufferedInputStream(Args&&...args) : 
			T{ std::forward<Args>(args)... } {}

	// We just simulate buffering not actually implement it.
	bool Read(std::string &text) {
		std::cout << "[Buffered Read]\n";
		T::Read(text);
	}

	void Close() {
		T::Close();
	}
};



/////////////////////////////////////////////////
/////////////////////  DecompressedInputStream.h
/////////////////////////////////////////////////
template <typename T>
class DecompressedInputStream : public T {
public:
	template <typename...Args>
	DecompressedInputStream(Args&&...args) : 
			T{ std::forward<Args>(args)... } {}

	bool Read(std::string &text) override {
		std::cout << "[DecompressedInputStream Read]\n";
		std::string compressed;
		auto result = T::Read(compressed);
		text.resize(compressed.size());
		std::transform(begin(compressed), end(compressed), begin(text), [](char ch) { return ch - 2; });
		return result;
	}

	void Close() override {
		T::Close();
	}
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
		m_Writer << text << "\n";
	}

	void Close() {
		if (m_Writer.is_open()) {
			m_Writer.close();
		}
	}
};


/////////////////////////////////////////////////
/////////////////////  BufferedOutputStream.h
/////////////////////////////////////////////////
template <typename T>
class BufferedOutputStream : public T {
	char m_Buffer[512]{};
public:
	template <typename...Args>
	BufferedOutputStream(Args&&...args) : T{std::forward<Args>(args)...} {}

	// We just simulate buffering not actually implement it.
	void Write(const std::string &text) {
		std::cout << "[Buffered Write]\n";
		T::Write(text);
	}

	void Close() {
		T::Close();
	}
};


/////////////////////////////////////////////////
/////////////////////  EncryptedStream.h
/////////////////////////////////////////////////
template <typename T>
class EncryptedStream : public T {
public:
	template <typename...Args>
	EncryptedStream(Args&&...args) : T{std::forward<Args>(args)...} {}

	void Write(const std::string &text) {
		std::cout << "[EncryptedStream Write]\n";
		std::string encrypted{};
		encrypted.resize(text.size());
		std::transform(begin(text), end(text), begin(encrypted), [](char ch) { return ch + 5; });
		T::Write(encrypted);
	}

	void Close() {
		T::Close();
	}
};




/////////////////////////////////////////////////
/////////////////////  CompressedOutputStream.h
/////////////////////////////////////////////////
template <typename T>
class CompressedOutputStream : public T {
public:
	template <typename...Args>
	CompressedOutputStream(Args&&...args) : T{std::forward<Args>(args)...} {}

	void Write(const std::string &text) {
		std::cout << "[CompressedOutputStream Write]\n";
		std::string compressed{};
		compressed.resize(text.size());
		std::transform(begin(text), end(text), begin(compressed), [](char ch) { return ch + 2; });
		T::Write(compressed);
	}

	void Close() {
		T::Close();
	}
};






void Write() {
	EncryptedStream<FileOutputStream> out{"test.txt"};
	out.Write("Using mixin to implement Static Decorator.");

	DecryptedStream<FileInputStream> in{"test.txt"};
	in.Read();
}




int main() {
	// CompressedOutputStream is decorating the FileStream using templates at compile time.
	//  and it will inherit from FileStream at compile time.
	// CompressedOutputStream is a Mixin.
	CompressedOutputStream<FileInputStream> cs;
	// Thus CompressedOutputStream adds more features to FileStream via inheritance.
	// But it does not use explicit inheritance. 


	Write();

	return 0;
}