/*
	File stream library, which will provide classes that'll help you perform, 
	read and write operations on files.

	Thus when client requested new features, we added new classes and supported those
	requests through inheritence rather than modifying the existing classes.

	---------------------------------NEXT-----------------------------------

	Now some clients work witha encrypted data and they want us to implement encrypted streams.
	i.e while writing data should be first encrypted and then written.
	    and during read operation the data should be read from the file and decrypted.


	The problem with this implementation is that clients can use any of the feature at a time.
	e.g. They can either write encrypted data or compressed data or buffered output.
	They can't mix-match the different features.

	There may be clients that use encrypted stream and and also use buffering along with it.

		One solution can be, use multiplte inheritance.
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
/////////////////////  BufferedInputStream.h
/////////////////////////////////////////////////
class BufferedInputStream : public FileInputStream {
	char m_Buffer[512]{};
	using FileInputStream::FileInputStream;
public:

	// We just simulate buffering not actually implement it.
	bool Read(std::string &text) override {
		std::cout << "[Buffered Read]\n";
		return FileInputStream::Read(text);
	}

	void Close() override {
		FileInputStream::Close();
	}
};


/////////////////////////////////////////////////
/////////////////////  DecryptedStream.h
/////////////////////////////////////////////////
class DecryptedStream : public FileInputStream {
	using FileInputStream::FileInputStream;
public:

	bool Read(std::string &text) override {
		std::cout << "[DecryptedStream Read]\n";
		std::string encrypted;
		auto result = FileInputStream::Read(encrypted);
		text.resize(encrypted.size());
		std::transform(begin(encrypted), end(encrypted), begin(text), [](char ch) { return ch - 5; });
		return result;
	}

	void Close() override {
		FileInputStream::Close();
	}
};



/////////////////////////////////////////////////
/////////////////////  DecompressedInputStream.h
/////////////////////////////////////////////////
class DecompressedInputStream : public FileInputStream {
	using FileInputStream::FileInputStream;
public:

	bool Read(std::string &text) override {
		std::cout << "[DecompressedInputStream Read]\n";
		std::string compressed;
		auto result = FileInputStream::Read(compressed);
		text.resize(compressed.size());
		std::transform(begin(compressed), end(compressed), begin(text), [](char ch) { return ch - 2; });
		return result;
	}

	void Close() override {
		FileInputStream::Close();
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
/////////////////////  BufferedOutputStream.h
/////////////////////////////////////////////////
class BufferedOutputStream : public FileOutputStream {
	char m_Buffer[512]{};
	using FileOutputStream::FileOutputStream;
public:

	// We just simulate buffering not actually implement it.
	void Write(const std::string &text) override {
		std::cout << "[Buffered Write]\n";
		FileOutputStream::Write(text);
	}

	void Close() override {
		FileOutputStream::Close();
	}
};


/////////////////////////////////////////////////
/////////////////////  EncryptedStream.h
/////////////////////////////////////////////////
class EncryptedStream : public FileOutputStream {
	using FileOutputStream::FileOutputStream;
public:

	void Write(const std::string &text) override {
		std::cout << "[EncryptedStream Write]\n";
		std::string encrypted{};
		encrypted.resize(text.size());
		std::transform(begin(text), end(text), begin(encrypted), [](char ch) { return ch + 5; });
		FileOutputStream::Write(encrypted);
	}

	void Close() override {
		FileOutputStream::Close();
	}
};




/////////////////////////////////////////////////
/////////////////////  CompressedOutputStream.h
/////////////////////////////////////////////////
class CompressedOutputStream : public FileOutputStream {
	using FileOutputStream::FileOutputStream;
public:

	void Write(const std::string &text) override {
		std::cout << "[CompressedOutputStream Write]\n";
		std::string compressed{};
		compressed.resize(text.size());
		std::transform(begin(text), end(text), begin(compressed), [](char ch) { return ch + 2; });
		FileOutputStream::Write(compressed);
	}

	void Close() override {
		FileOutputStream::Close();
	}
};


void Encrypt() {
	EncryptedStream output("text.txt");
	output.Write("First Line");
	output.Write("Second Line");
	output.Write("Third Line");
}

void Decrypt() {
	DecryptedStream f("text.txt");
	std::string text;
	f.Read(text);
	std::cout << text << std::endl;
}


void Compress() {
	CompressedOutputStream output("text.txt");
	output.Write("First Line");
	output.Write("Second Line");
	output.Write("Third Line");
}

void Decompress() {
	DecompressedInputStream f("text.txt");
	std::string text;
	f.Read(text);
	std::cout << text << std::endl;
}


void Read() {
	BufferedInputStream f{"design_doc"};
	std::string text;
	f.Read(text);
	std::cout << text << std::endl;
	// the destructor of f will automatically close the file.
}


void Write() {
	BufferedOutputStream output{"text.txt"};
	output.Write("First Line");
	output.Write("Second Line");
	output.Write("Third Line");
}



int main() {
	Read();
	std::cout << std::endl;
	Write();
	std::cout << std::endl;
	Compress();
	std::cout << std::endl;
	Decompress();
	std::cout << std::endl;
	Encrypt();
	std::cout << std::endl;
	Decrypt();
	return 0;
}



