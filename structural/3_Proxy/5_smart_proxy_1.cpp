/*
	Smart Proxy
*/


///////////////////////////////////////////////
//////////////////  Image.h
///////////////////////////////////////////////
#include <string>
#include <iostream>

class Image {
	std::string m_FileName;
protected:
	// Protected because this function is invoked only by the derived classes.
	void SetFileName(const std::string &filename) {
		m_FileName = filename;
	}
public:
	Image() = default;
	Image(const std::string &file) : m_FileName{file} {
		std::cout << "Image file is : " << m_FileName << std::endl;
	}

	const std::string& GetFileName() const {
		std::cout << "[Image] GetFileName() : " << m_FileName << "\n";
		return m_FileName;
	}

	virtual ~Image() = default;
	virtual void Display() = 0;
	virtual void Load() = 0;
	virtual void Load(const std::string &filename) = 0;
};



///////////////////////////////////////////////
//////////////////  Bitmap.h
///////////////////////////////////////////////
#include <thread>
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>

using std::string;

class Bitmap : public Image {
	string m_Buffer{};
public:
	/*
						(not doing any initialization for the Bitmap class)
		Since we are actually not doing anything in the Derived class constuctor
		rather than just calling the relevant Base class constuctors
		thus we can use the C++11 feature of  "Inheriting Constructors"
		Bitmap() = default;
		Bitmap(std::string &file) : Image(file) {}
	*/
	using Image::Image;

	void Display() {
		std::cout << m_Buffer << std::endl;
	}

	void Load() {
		m_Buffer.clear();
		std::cout << "[Bitmap] " << GetFileName() << std::endl;
		std::ifstream file{GetFileName()};
		if (!file) {
			throw std::runtime_error{"Failed to open file!"};
		}
		std::string line{};
		std::cout << "Loading bitmap[";
		while (std::getline(file, line)) {
			m_Buffer += line + "\n";
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(100ms);
			std::cout << ".";
			flush(std::cout);
		}
		std::cout << "] Done!\n";
	}

	void Load(const std::string &filename) {
		SetFileName(filename);
		Load();
	}

};




int main() {
	Bitmap *p = new Bitmap("design_doc");
	p->Load();
	p->Display();

	return 0;
}


/*
	There is one problem with this code : 
	We are not deleting the pointer "p", so this will cause a memory leak in our program.

	In a large project that uses a lot of pointers, sometimes programmers forget to call 
	delete on those pointers and that causes memory leaks and it affects the performance 
	of the application.

	How do we ensure that the memory is not leaked?
	you have to ensure that you free the pointers every time.
	But that is not possible all the time!
	Sometimes we may forget or sometimes we don't know where we should free the pointer 
	because it is being shared by different parts of the code.


	So that's why we crate a proxy for this pointer.
*/