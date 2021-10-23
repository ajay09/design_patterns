/*
	Implement the Template Method Pattern for the Document Framework

	
	- The boiler plate code is tucked away in the base class and the sub-classes
	  implements their versions of the algo.

*/

//////////////////////////////////////////
////////////////////////  Document.h
//////////////////////////////////////////
#include <fstream>
#include <string>
#include <iostream>

class Document {
	enum class DialogType{SAVE, LOAD};

	bool m_IsModified;
	
	std::string FileDialog(DialogType type) const;
protected:
	virtual void WriteVersion(std::ofstream &out);  // hook
	virtual void ReadVersion(std::ifstream &in);  // hook

	virtual void WriteData(std::ofstream &out) = 0;
	virtual void ReadData(std::ifstream &in) = 0;
public:
	Document() : m_IsModified{false} {}

	void SetModified(bool modified) {
		m_IsModified = modified;
	}

	virtual void Save() final;
	// Save Algo
	// 1. Check if already saved.										// fixed
	// 2. If not saved display file dialog to get the filename.         // fixed
	// 3. Open that file : - write the version info						// *** custom (optional for subclasses which want versioning)
	//                     - write the data 							// *** custom
	// 4. set the modified state to false                               // fixed

	virtual void Load() final;
	// Load algo
	// 1. Check if modified               								// fixed									
	// 2. Display file dialog and get the filename						// fixed							
	// 3. Open the filestream for reading.								// fixed					
	// 4. Read version info												// *** custom	
	// 5. REad the data													// *** custom

	virtual ~Document() = default;
};

std::string Document::FileDialog(DialogType type) const {
	std::string filename{};
	if (type == DialogType::SAVE) {
		std::cout << "Name of the file to save? ";
	} else if (type == DialogType::LOAD) {
		std::cout << "Name of the file to load? ";
	}
	std::getline(std::cin, filename);
	return filename;
}

// Default implementation
void Document::WriteVersion(std::ofstream &out) {
}

// Default implementation
void Document::ReadVersion(std::ifstream &in) {
}

void Document::Save() {
	if (!m_IsModified) {
		std::cout << "Already saved.\n";
		return;
	}
	std::ofstream out{FileDialog(DialogType::SAVE)};
	WriteVersion(out);
	WriteData(out);
	m_IsModified = false;
	std::cout << "------- File saved successfully -------\n";
}

void Document::Load() {
	if (m_IsModified) {
		std::cout << "Save current changes first\n";
		return;
	}
	std::ifstream input{FileDialog(DialogType::LOAD)};
	ReadVersion(input);
	ReadData(input);
	std::cout << "------- File loaded successfully -------\n";
}







//////////////////////////////////////////
////////////////////////  TextDocument.h
//////////////////////////////////////////
#include <string>
class TextDocument : public Document {
	std::string m_Text;
protected:
	void ReadData(std::ifstream &in) override;
	void WriteData(std::ofstream &out) override;
public:
	void SetText(std::string text);
	void Print();
};

#include <iostream>

void TextDocument::ReadData(std::ifstream &in) {
	std::getline(in, m_Text);
}

void TextDocument::WriteData(std::ofstream &out) {
	out.seekp(0);
	out << m_Text;
	SetModified(false);
}

void TextDocument::SetText(std::string text) {
	m_Text = std::move(text);
	SetModified(true);
}


void TextDocument::Print() {
	std::cout << "TextDocument : " << m_Text << std::endl;
}







//////////////////////////////////////////
////////////////////////  Numbers.h
//////////////////////////////////////////
class Numbers : public Document {
	int m_Number;
	std::string m_Version;
	std::string m_Data;

public:
	void SetData(std::string data) {
		m_Data = std::move(data);
		SetModified(true);
	}

	void SetNumber(int num) {
		m_Number = num;
		SetModified(true);
	}

	void Print() {
		std::cout << "Number is : " << m_Number << "\n";
		std::cout << "Data is : " << m_Data << "\n";
	}

protected:
	void ReadVersion(std::ifstream &in) override {
		in >> m_Version;
	}

	void WriteVersion(std::ofstream &out) override {
		out << "v2.0\n";
	}


	void ReadData(std::ifstream &in) override {
		ReadVersion(in);
		if (m_Version == "v1.0") {
			in >> m_Number;
		}
		else if (m_Version == "v2.0") {
			in >> m_Number;
			in >> m_Data;
		}
	}


	void WriteData(std::ofstream &out) override {
		out.seekp(0);
		out << "v2.0\n";
		out << m_Number << "\n";
		out << m_Data;
		SetModified(false);
	}

};




void Text() {
	TextDocument txt{};

	// txt.SetText("Some user data");
	// txt.Save();

	txt.Load();
	txt.Print();
}



int main() {
	Numbers nm{};
	nm.SetNumber(999);
	nm.SetData("Second");
	nm.Save();
	nm.Load();
	nm.Print();
	return 0;
}


/*
	-------------------
	|    Document	  |
	-------------------
	| m_IsModified    |
	-------------------
	|  ReadVersion()  |  // hooks    they are called hooks because they are optional to be implemented by the sub-classes
	|  WriteVersion() |  // hooks
	|  ReadData()     |  // Compulsory to be implemented by the subclasses
	|  WriteData()    |  // Compulsory to be implemented by the subclasses
	|  SetModified()  |
	|  FileDialog()   |	 // Fixed can't be customized by the child classes					
	|  Load()  		  |	---; Template Methods
	|  Save() 		  |	---`			
	-------------------	
		   /_\
		    |
		    |------------------------------------;
	-------------------					-------------------
	|  TextDocument   |					|     Numbers     |
	-------------------					-------------------

	- Adv of converting Load and Save methods into template method is that
	  they avoid duplication of the boiler plate code in the child classes.
	
	- This seems similar to the strategy pattern.
	  But strategy pattern allows you to modify the entire algo.
	  But template method allows yout to modify the algo at certain points.


	- Clients should only call the template methods and not the methods that are used internally by the template methods.
	  That's why we made the internally used methods as protected.

	- The subclasses should not override the template methods.
	  Since Load() and Save() are not virtual so they can't be overriden by the child classes. But still the child classes
	  can accidently provide an implementation of the Load() or Save() which will hide the base-class methods.

	  Thus we make Load() and Save() as virtual and final.
	  Now if the child classes redefine Save() or Load() the code won't compile.

	  This is how you can prevent your template methods from getting overridden or hidden by the sub-classes.

*/


