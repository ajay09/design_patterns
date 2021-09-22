/*
	Create a wrapper around the CreateFile windows api
	
	WINBASEAPI
	HANDLE
	WINAPO
	HANDLE CreateFileA(
		_IN_ 	 LPCSTR                lpFileName,
		_IN_ 	 DWORD                 dwDesiredAccess,
		_IN_ 	 DWORD                 dwShareMode,
		_IN_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		_IN_ 	 DWORD                 dwCreationDisposition,
		_IN_ 	 DWORD                 dwFlagsAndAttributes,
		_IN_opt_ HANDLE                hTemplateFile
	);


	The clients can choose different kinds of constructors
	as per their needs.
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
File::File(const char* fileName, DWORD desiredAccess)
	:File{fileName, desiredAccess, FILE_ATTRIBUTE_NORMAL}
{

}

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
	DWORD written{} ;

	if (!m_hFile.write(pBuffer, size)) {
		throw std::runtime_error{"Error while writing"} ;
	}
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
		std::cout << "File is open\n";
		
		auto str = "Hello world!";
		f.Write(str, strlen(str));
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}


int main() {

	Write();

	// fstream fs;
	// fs.open ("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	// fs << "hello world\n";
	// fs.close();
	
	return 0;
}






