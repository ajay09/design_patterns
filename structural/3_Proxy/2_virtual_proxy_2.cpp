/*	
	Virtual Proxy

	A virtual proxy creates objects on demand.


	client ----------------->  | Image   |
	                           -----------
	                               /_\
	                                |
	                                |
	                                |
	                            |  Bitmap   |
	                            -------------
	                            | Load()    |
	                            | Display() |


	When the client invokes the Load() method, the bitmap is loaded from the disk
	and it takes some time to load it as bitmap can be large.

	After the bitmap is loaded, the client may call the Display() method.

	From our experience we know that after the client calls Load()
	sometimes they do not call Display() method. But they have already paid
	the price of loading the bitmap which takes a lot of time.

	So we would like to create a proxy so that when the client loads the Bitmap, the Bitmap
	is not loaded at that time. Instead, the Bitmap is loaded on demad i.e. only when
	the client invokes the Display() function.
*/

// Instead of loading actual images we demonstrate our
// example by loading text files.
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




// Thus to save time of unnecessary loading the file we implement a proxy.
///////////////////////////////////////////////
//////////////////  BitmapProxy.h
///////////////////////////////////////////////
class BitmapProxy : public Image {
	Bitmap *m_pBitmap;
	bool m_IsLoaded{false};
public:
	BitmapProxy() : BitmapProxy{""} {}
	BitmapProxy(const std::string &name) {
		m_pBitmap = new Bitmap{name};
	}

	~BitmapProxy() {
		delete m_pBitmap;
	}

	void Display() {
		std::cout << "[BitmapProxy] Display() \n";
		if (!m_IsLoaded) {
			// std::cout << "[BitmapProxy] " << GetFileName() << std::endl;
			std::cout << "[BitmapProxy] Loading Bitmap\n";
			m_pBitmap->Load();
		}
		m_pBitmap->Display();
	}

	void Load() {
		std::cout << "[BitmapProxy] Load() \n";
		// SetFileName("");
	}

	void Load(const std::string &filename) {
		SetFileName(filename);
	}

};











int main() {
	Image *p = new BitmapProxy{"design_doc"};
	p->Load();
	// The image will now be actually loaded only when Display() is called.
	// p->Display();
	delete p;
}






