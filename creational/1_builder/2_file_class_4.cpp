/*
	File class using the Builder Design Pattern

	To work with encrypted files we can simply add a new builder.
*/

// typedef unsigned long DWORD;
using DWORD = unsigned long;
using HANDLE = void *;
using BOOL = int;

#include <iostream>
#include <exception>
#include <stdexcept>
using std::fstream;

typedef void* LPVOID;

#define FALSE 0
#define TRUE 1

typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;


#include <fstream>
using std::fstream;

class File {
	const char *m_pFileName{};      // filename
	DWORD m_DesiredAccess;        // mode Read/write
	DWORD m_ShareMode;            // shared mode => share among processes
	LPSECURITY_ATTRIBUTES m_pSA;  // security attribute
	DWORD m_CreationDisposition;  // action to take if file already exists or not
	DWORD m_FlagAttributes;       // attributes for the file
	HANDLE m_hTemplateFile;       // handle to a file that constains the attributes that you want to apply to this file.

	std::fstream m_hFile{};
public:
	File(const char *fileName,
		DWORD desiredAccess,
		DWORD shareMode,
		LPSECURITY_ATTRIBUTES sa,
		DWORD creationDisposition,
		DWORD flagAttributes,
		HANDLE templateFile);

	File(const char* fileName, DWORD desiredAccess);

	File(const char* fileName, DWORD desiredAccess, 
				DWORD flagsAttributes);

	// returns the number of characters read from the file.
	DWORD Read(char *pBuffer, DWORD size);

	DWORD Write(const char *pBuffer, DWORD size);

	void Close();

	~File();

	BOOL IsOpen() const;
};



#define INVALID_HANDLE_VALUE -1

#define READ 8
#define WRITE 16

#define SUCCESS 0
#define FAILED -1
#define FILE_SHARED_READ 1


#define FILE_ATTRIBUTE_ENCRYPTED 64
#define CREATE_ALWAYS  128
#define FILE_ATTRIBUTE_NORMAL 256

File::File(const char* fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES sa,
           DWORD creationDisposition, DWORD flagsAttributes,
           HANDLE templateFile) :
			m_pFileName{ fileName },
			m_DesiredAccess{desiredAccess},
			m_ShareMode{ shareMode },
			m_pSA{ sa },
			m_CreationDisposition{creationDisposition},
			m_FlagAttributes{flagsAttributes},
			m_hTemplateFile{templateFile} 
			{

				// std::cout << "Opening file : " << fileName << std::endl;
				std::ios_base::openmode mode{0};
				if (m_DesiredAccess & READ) {
					// std::cout << "Read mode\n";
					mode |= std::ios_base::in;
				}
				if (m_DesiredAccess & WRITE) {
					// std::cout << "Write mode\n";
					mode |= std::ios_base::out;
				}
				// std::cout << "mode : " << mode << std::endl;

				m_hFile.open(m_pFileName, mode) ;

				if(m_hFile.fail()) {
					throw std::runtime_error{"File error"} ;
				}
			}

// Delegating constructor
// Call a constructor from other constructors.
// Constructor for simple files
File::File(const char* fileName, DWORD desiredAccess)
	:File{fileName, desiredAccess, FILE_ATTRIBUTE_NORMAL}
{

}


// Constructor for files with custom attributes
File::File(const char* fileName, 
	DWORD desiredAccess, 
	DWORD flagsAttributes)
   :File{fileName, desiredAccess, 0, nullptr, CREATE_ALWAYS,flagsAttributes, nullptr}
{

}

#include <stdlib.h>
DWORD File::Read(char* pBuffer, DWORD size) {
	DWORD read{};
	// std::cout << "buffer : "<< (void *)pBuffer << std::endl;

	memset(pBuffer, 0, size);

	// std::cout << "buffer : "<< (void *)pBuffer << std::endl;
	if (!m_hFile.read(pBuffer, size - 1)) {
		if (!m_hFile.eof()) {
			throw std::runtime_error{"Error while reading"} ;
		}
	}
	if (pBuffer[0] == 0)
		read = 0;
	else{
		// std::cout << pBuffer[0] << "   ";
		read = size - 1;
	}
	// std::cout << read << std::endl;
	return read ;
}

DWORD File::Write(const char* pBuffer, DWORD size) {
	DWORD written{0} ;

	std::cout << "  -  " << pBuffer[3] << "  " << size << std::endl;
	if (!m_hFile.write(pBuffer, size)) {
		throw std::runtime_error{"Error while writing"} ;
	}
	written = size;
	return written ;
}

void File::Close() {
	m_hFile.close();
}

File::~File() {
	if (m_hFile)
		m_hFile.close();
}

BOOL File::IsOpen() const {
	return m_hFile.is_open() ;
}




/////////////////////////////////////////////////
//////////////////////////  FileBuilder.h
//////////////////////////  It will contain methods that will be used
//////////////////////////  to set the data that corresponds to the
//////////////////////////  arguments of the create file API
/////////////////////////////////////////////////
class FileBuilder {
public:
	virtual void SetFileName(const char *pFile) = 0;
	virtual void SetDesiredAccess(DWORD access) = 0;
	virtual void SetShareMode() = 0;
	virtual void SetSecurityAttributes() = 0;
	virtual void SetCreationDisposition() = 0;
	virtual void SetFlagAttributes() = 0;
	virtual void SetTemplateFile() = 0;

	virtual ~FileBuilder() = default;

	// We can't use File here and instead have to use File*
	// The implicit copy-ctor for File class is deleted becuase
	// the copy-ctor for one of its member variable is also deleted.
	virtual File* Build() = 0;
};




// A class to build a simple file.
/////////////////////////////////////////////////
//////////////////////////  SimpleFileBuilder.h
/////////////////////////////////////////////////
class SimpleFileBuilder : public FileBuilder {
	const char *m_pFileName;
	DWORD m_DesiredAccess;
public:
	void SetFileName(const char *pFile) override {
		m_pFileName = pFile;
	}

	void SetDesiredAccess(DWORD access) override {
		m_DesiredAccess = access;
	}


	// We need not do anything in the rest of the functions as they are not
	// relevant to a simple file.
	void SetShareMode()  override {

	}

	void SetSecurityAttributes()  override {

	}

	void SetCreationDisposition()  override {

	}

	void SetFlagAttributes()  override {

	}

	void SetTemplateFile()  override {

	}


	File* Build() override {
		return new File{m_pFileName, m_DesiredAccess, 0, nullptr, 1, 1, nullptr};
	}

};



/////////////////////////////////////////////////
//////////////////////////  EncryptedFileBuilder.h
/////////////////////////////////////////////////
class EncryptedFileBuilder : public FileBuilder {
	const char *m_pFileName;
	DWORD m_DesiredAccess;
	DWORD m_ShareMode;
	DWORD m_FlagsAttributes;
public:
	void SetFileName(const char *pFile) override {
		m_pFileName = pFile;
	}

	void SetDesiredAccess(DWORD access) override {
		m_DesiredAccess = access;
	}

	// Since we are using in encrypted mode thus we don't want
	// anyone else to use the file while it is in use.
	void SetShareMode()  override {
		m_ShareMode = 0;
	}

	void SetSecurityAttributes()  override {

	}

	void SetCreationDisposition()  override {

	}

	void SetFlagAttributes()  override {
		m_FlagsAttributes = FILE_ATTRIBUTE_ENCRYPTED;
	}

	void SetTemplateFile()  override {

	}


	File* Build() override {
		return new File{m_pFileName, m_DesiredAccess, 0, nullptr, 1, m_FlagsAttributes, nullptr};
	}
};



/////////////////////////////////////////////////
//////////////////////////  Director.h
/////////////////////////////////////////////////
class Director {
	FileBuilder *m_pBuilder;
public:
	Director(FileBuilder *builder) : m_pBuilder{builder} {}

	void Create(const char *pFileName, DWORD desiredAccess) {
		m_pBuilder->SetFileName(pFileName);
		m_pBuilder->SetDesiredAccess(desiredAccess);
		m_pBuilder->SetShareMode();
		m_pBuilder->SetSecurityAttributes();
		m_pBuilder->SetCreationDisposition();
		m_pBuilder->SetFlagAttributes();
		m_pBuilder->SetTemplateFile();
	}
};




/////////////////////////////////////////////////
//////////////////////////  Client.cpp
/////////////////////////////////////////////////




#include <iostream>
#include <stdio.h>



void Read() {
	try {
		File f{"2_file_class.cpp", READ, 1, nullptr, 1, 1, nullptr};
		if (!f.IsOpen()) {
			std::cout << "Could not open the file\n";
		}
		std::cout << "File is open\n";
		constexpr int SIZE{128};
		char buffer[SIZE];
		std::cout << "buffer ::: "<<  &buffer << std::endl;

		while (f.Read(&buffer[0], SIZE) != 0) {
			std::cout << buffer ;//<< std::endl;
			flush(std::cout);
		}
		std::cout << "file read\n";
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}



void Write() {
	try {
		File f{"abc_hello", WRITE, 1, nullptr, 1, 1, nullptr};
		if (!f.IsOpen()) {
			std::cout << "Could not open the file\n";
		}
		// std::cout << "File is open\n";
		
		auto str = "Hello world!\n";
		f.Write(str, strlen(str));
		(&f)->Write("ABC", 3);
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}



int main() {
	SimpleFileBuilder builder{};
	Director director(&builder);

	director.Create("abc_hello", WRITE);
	File *fi = builder.Build();
	try {
		auto str = "Hello world!\n";
		fi->Write(str, strlen(str));
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	

	EncryptedFileBuilder builder2{};
	Director director2(&builder2);

	director.Create("abc_hello_encrypt", WRITE);
	File *fi2 = builder.Build();
	try {
		auto str = "Hello world!\n";
		fi2->Write(str, strlen(str));
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}


	// Write();

	return 0;
}


