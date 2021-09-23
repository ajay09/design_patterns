/*
	Use Fluent Interface to chani methods and reduce syntactical noise.
	
	Method chaining involves each methode to return the instance of the
	calling object (current object) and then object is used to invoke the
	next method in the chain.

	The return type for the Builder class method should be "Builder&"

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

#define INVALID_HANDLE_VALUE -1

#define READ 8
#define WRITE 16

#define SUCCESS 0
#define FAILED -1
#define FILE_SHARED_READ 1

#define OPEN_EXISTING 20
#define FILE_ATTRIBUTE_ENCRYPTED 64
#define CREATE_ALWAYS  128
#define FILE_ATTRIBUTE_NORMAL 256

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

	class Builder {
		const char* m_pFileName{};
		DWORD m_DesiredAccess{};
		DWORD m_ShareMode{};
		LPSECURITY_ATTRIBUTES m_pSA{};
		DWORD m_CreationDisposition{CREATE_ALWAYS};
		DWORD m_FlagsAttributes{FILE_ATTRIBUTE_NORMAL};
		HANDLE m_hTemplateFile{};
	public:

		Builder(const Builder& other) = delete;

		Builder(Builder&& other) noexcept
			: m_pFileName{other.m_pFileName},
			  m_DesiredAccess{other.m_DesiredAccess},
			  m_ShareMode{other.m_ShareMode},
			  m_pSA{other.m_pSA},
			  m_CreationDisposition{other.m_CreationDisposition},
			  m_FlagsAttributes{other.m_FlagsAttributes},
			  m_hTemplateFile{other.m_hTemplateFile} {
			other.m_pFileName = nullptr ;
			other.m_DesiredAccess = 0 ;
			other.m_ShareMode = 0 ;
			other.m_pSA = nullptr ;
			other.m_CreationDisposition = 0 ;
			other.m_FlagsAttributes = 0 ;
			other.m_hTemplateFile = nullptr ;
		}

		Builder& operator=(const Builder& other) = delete;

		Builder& operator=(Builder&& other) noexcept {
			if (this == &other)
				return *this;
			m_pFileName = other.m_pFileName;
			m_DesiredAccess = other.m_DesiredAccess;
			m_ShareMode = other.m_ShareMode;
			m_pSA = other.m_pSA;
			m_CreationDisposition = other.m_CreationDisposition;
			m_FlagsAttributes = other.m_FlagsAttributes;
			m_hTemplateFile = other.m_hTemplateFile;
			other.m_pFileName = nullptr ;
			other.m_DesiredAccess = 0 ;
			other.m_ShareMode = 0 ;
			other.m_pSA = nullptr ;
			other.m_CreationDisposition = 0 ;
			other.m_FlagsAttributes = 0 ;
			other.m_hTemplateFile = nullptr ;
			return *this;
		}

		Builder(const char *pFileName, DWORD desiredAcces):
		m_pFileName{pFileName},
		m_DesiredAccess{desiredAcces} {
			
		}
		Builder & ShareMode(DWORD shareMode) {
			m_ShareMode = shareMode ;
			return *this; 
		}
		Builder & SecurityAttributes(LPSECURITY_ATTRIBUTES lpsa) {
			m_pSA = lpsa ;
			return *this; 
		}
		Builder & CreationDisposition(DWORD creationDisposition) {
			m_CreationDisposition = creationDisposition ;
			return *this; 
		}
		Builder & FlagsAttributes(DWORD flagsAttributes) {
			m_FlagsAttributes = flagsAttributes ;
			return *this; 
		}
		Builder & TemplateFile(HANDLE templateFile) {
			m_hTemplateFile = templateFile ;
			return *this; 
		}
		File* Build() {
			return new File{m_pFileName, m_DesiredAccess, m_ShareMode,m_pSA,
			m_CreationDisposition, m_FlagsAttributes, m_hTemplateFile} ;
		}
	};
};





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
//////////////////////////  Client.cpp
/////////////////////////////////////////////////




#include <iostream>
#include <stdio.h>




int main() {
	SECURITY_ATTRIBUTES sa{};
	File::Builder builder("3_fluent_builder.cpp", READ);
	/*
		builder.FlagsAttributes(FILE_ATTRIBUTE_ENCRYPTED);
		builder.CreationDisposition(OPEN_EXISTING);
		builder.ShareMode(FILE_SHARED_READ);
		builder.SecurityAttributes(&sa);
		
		auto f = builder.Build();
	*/
	// Instead of the above lines you can use chaining (through the Fluent Interface)
	// This is possible because the chained member function returns the same
	// object that was used to call it in the first place!!!

	auto f = builder.FlagsAttributes(FILE_ATTRIBUTE_ENCRYPTED)
				    .CreationDisposition(OPEN_EXISTING)
				    .ShareMode(FILE_SHARED_READ)
				    .SecurityAttributes(&sa)
				    .Build();

	char buffer[1024]{};
	f->Read(buffer, 1024);
	std::cout << buffer;

	return 0;
}


