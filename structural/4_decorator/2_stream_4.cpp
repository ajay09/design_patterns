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

		We will have to create BufferedEncryptedStream class which will inherit from EncryptedStream
		and BufferedOutputStream classes.
		But here we will face the Diamond problem and a single instance of BufferedEncryptedStream
		will have 2 instances of FileOutputStream class. Thus file would be opened twice. Thus this
		approach won't work.

		To make the above approach work we will have to use virtual inheritance. Thus modify the
		way EncryptedStream and BufferedOutputStream classes are inheriting FileOutputStream class.


		Similarly new features may require mixing other classes which will lead to a lot of modifications
		at various levels of inheritance.


	
	And what if we have to implement a new stream class "NetworkOutputStream"(instead of FileOutputStream)	
	The features we have already implemented using inheritance won't be useful for NetworkOutputStream.
	Thus we will have to implement the entire hierarchy for NetworkOutputStream also.



	Thus instead of inheritance we should use Decorator Pattern to add new behavior.
	Using dEcorator pattern we can add more features to the component by creating wrappers and 
	without modifying the existin component.
	Using inheritance is a compile-time relationship. This is a inflexible design because at 
	runtime you can neither add or remove existing features from the component.



					|   OutputStream   |				|   OutputStream   |
					--------------------				--------------------
					|				   |				|				   |
					--------------------				--------------------
							/_\									/_\
							 |									 |
							 |									 |
					| FileOutputStream |				| FileOutputStream |<-------------;
					--------------------				--------------------			  |
					|				   |				|				   |		      |
					--------------------				--------------------			  |
							/_\															  |
							 |	Inheritance												  |
							 |												  Composition |
					| CompressedStream |				| CompressedStream |---------------
					--------------------				--------------------
					|				   |				|				   |
					--------------------				--------------------
				

Lets focus on just one class, in this case, the CompressStream inherits from FileOutputStream.
This is because it needs to override the functionality of the FileOutputStream class, but this is
not only overwriting because CompressStream also needs to use the functionality from FileOutputStream.


So CompressStream does two things, one is it provides its own implementation and also calls 
the base implementation that is in FileOutputStream class so it does not completely replace 
the implementation of the FileOutputStream class.
Even though we override the functionality of the FileOutputStream class, its functionality 
is still required.


		So no matter what kind of stream you use here, all the streams will 
		ultimately use the functionality of the FileOutputStream.

					We can use that to our advantage.


Instead of inheriting CompressStream from FileOutputStream, let us compose FileOutputStream, inside
CompressStream and we will remove the inheritance relationship.
This will not make any difference because even now, if we create instance of CompressedStream, we
will have to initialize it with an instance of FileOutputStreamand, thus it can still provide the
behavior of compression and also call the implementation of FileOutputStream class.


		void Operate(OutputStream *pOs) {
			pOs->Write("some text");
			pOs->Close();
		}

If we pass the object of CompressedOutputStream to the above function, it won't work.
This doesn't work because CompressedOutputStream is not a kind of OutputStream.
This defeats the whole purpose of using inheritance.
That is why we need to ensure that CompressedOutputStream class is a kind of OutputStream class.
And on the other side, the DecompressedInputStream should be a kind of InputStream class.



Although we can pass CompressedOutputStream object to Operate() after inheriting CompressedOutputStream
from OutputStream class.
		
		CompressedOutput stream has a pointer to file stream. Also the other stream classes
		also have a pointer to the FileOutput stream class, but this means the stream classes 
		will always point to a FileOutput Stream class.
		This is very inflexible if we have a NetworkOutputStream, then CompressedOutput stream
		will not be able to work with it.


				But there is a very simple solution to this.

		Instead of pointing to FileOutputStream, we modify the CompressedOutputStream to point
		to an output stream?
	    The advantage would be the CompressedOutputStream can now point to any kind of OutputStream.
		So basically any derivative of OutputStream class and that will be a huge advantage.

						
																
	|   OutputStream   |										
	--------------------										
	|				   |										
	--------------------										
			/_\													
			 |      Inheritance 								
			 |--------------------------------;					
			 |								  |					
			 |			  Composition		  |					
	| FileOutputStream |<-------------| CompressedStream |		
	--------------------			  --------------------		
	|				   |		      |		    		 |		
	--------------------			  --------------------		


						| |
						| |	  will become
					   \   /
						\_/


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
	| FileOutputStream |			  | CompressedStream |----
	--------------------			  --------------------
	|				   |		      |		    		 |
	--------------------			  --------------------


						
This is the Decorator Design pattern.
And using the decorator patter we can add more features and add new behavior to the 
FileOutputStream class at runtime.						

All we have to do add a new class that inherits from OutputStream class and compose an
OutputStream pinter inside it and initialize it with any kind of OutputStream class.



--------------------------------- Next-------------------------------
				Issue with the above implementation.

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
class BufferedInputStream : public InputStream {
	char m_Buffer[512]{};
	InputStream *m_pIs;
public:
	BufferedInputStream(InputStream *pIs) : m_pIs{pIs} {}
	// We just simulate buffering not actually implement it.
	bool Read(std::string &text) override {
		std::cout << "[Buffered Read]\n";
		return m_pIs->Read(text);
	}

	void Close() override {
		m_pIs->Close();
	}
};


/////////////////////////////////////////////////
/////////////////////  DecryptedStream.h
/////////////////////////////////////////////////
class DecryptedStream : public InputStream {
	InputStream *m_pIs;
public:
	DecryptedStream(InputStream *pIs) : m_pIs{pIs} {}

	bool Read(std::string &text) override {
		std::cout << "[DecryptedStream Read]\n";
		std::string encrypted;
		auto result = m_pIs->Read(encrypted);
		text.resize(encrypted.size());
		std::transform(begin(encrypted), end(encrypted), begin(text), [](char ch) { return ch - 5; });
		return result;
	}

	void Close() override {
		m_pIs->Close();
	}
};



/////////////////////////////////////////////////
/////////////////////  DecompressedInputStream.h
/////////////////////////////////////////////////
class DecompressedInputStream : public InputStream {
	InputStream *m_pIs;
public:
	DecompressedInputStream(InputStream *pIs) : m_pIs{pIs} {}

	bool Read(std::string &text) override {
		std::cout << "[DecompressedInputStream Read]\n";
		std::string compressed;
		auto result = m_pIs->Read(compressed);
		text.resize(compressed.size());
		std::transform(begin(compressed), end(compressed), begin(text), [](char ch) { return ch - 2; });
		return result;
	}

	void Close() override {
		m_pIs->Close();
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
class BufferedOutputStream : public OutputStream {
	char m_Buffer[512]{};
	OutputStream *m_pOs;
public:
	BufferedOutputStream(OutputStream *pOs) : m_pOs{pOs} {}

	// We just simulate buffering not actually implement it.
	void Write(const std::string &text) override {
		std::cout << "[Buffered Write]\n";
		m_pOs->Write(text);
	}

	void Close() override {
		m_pOs->Close();
	}
};


/////////////////////////////////////////////////
/////////////////////  EncryptedStream.h
/////////////////////////////////////////////////
class EncryptedStream : public OutputStream {
	OutputStream *m_pOs;
public:
	EncryptedStream(OutputStream *pOs) : m_pOs{pOs} {}

	void Write(const std::string &text) override {
		std::cout << "[EncryptedStream Write]\n";
		std::string encrypted{};
		encrypted.resize(text.size());
		std::transform(begin(text), end(text), begin(encrypted), [](char ch) { return ch + 5; });
		m_pOs->Write(encrypted);
	}

	void Close() override {
		m_pOs->Close();
	}
};




/////////////////////////////////////////////////
/////////////////////  CompressedOutputStream.h
/////////////////////////////////////////////////
class CompressedOutputStream : public OutputStream {
	OutputStream *m_pOs;
public:
	CompressedOutputStream(OutputStream *pOs) : m_pOs{pOs} {}

	void Write(const std::string &text) override {
		std::cout << "[CompressedOutputStream Write]\n";
		std::string compressed{};
		compressed.resize(text.size());
		std::transform(begin(text), end(text), begin(compressed), [](char ch) { return ch + 2; });
		m_pOs->Write(compressed);
	}

	void Close() override {
		m_pOs->Close();
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



