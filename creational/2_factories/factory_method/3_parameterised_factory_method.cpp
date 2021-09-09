/*
	Factory method can be used to create instances without depending on their concrete types.
	The instances are created by deferring the instantiation process to the subclass.

	One disadv of this patter is that every time you add a new Product class, you need a
	corresponding Creator class. In app_framework_2 when we added a new Document type, we
	also had to add a correspoding Application class.

	How do we upgrade the framework to support different kinds of frameworks using the
	same application?
	The users of our framework should be able to create instances of multiple classes without
	having to create Application classes.

	Therefore if we know beforehand how many types of Documents the Application framework
	is going to create, then instead of using the Factory Method we can use a 
	Parameterized Factory.
*/


///////////////////////////////////////////////////
///////////////////////  Document.h
///////////////////////////////////////////////////
// #pragma once
class Document {
public:
    virtual void Read() = 0;
    virtual void Write() = 0;

    virtual ~Document() = default;
};


// Let's add a new Document type as well.
///////////////////////////////////////////////////
///////////////////////  SpreadsheetDocument.h
///////////////////////////////////////////////////
// #pragma once
class SpreadsheetDocument : public Document {
public:
    void Read() override;
    void Write() override;
};

///////////////////////////////////////////////////
///////////////////////  TextDocument.h
///////////////////////////////////////////////////
// #pragma once
class TextDocument : public Document {
public:
    void Read() override;
    void Write() override;
};


///////////////////////////////////////////////////
///////////////////////  SpreadsheetDocument.cpp
///////////////////////////////////////////////////
#include <iostream>

void SpreadsheetDocument::Read() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SpreadsheetDocument::Write() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


///////////////////////////////////////////////////
///////////////////////  TextDocument.cpp
///////////////////////////////////////////////////
#include <iostream>

void TextDocument::Read() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void TextDocument::Write() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


///////////////////////////////////////////////////
///////////////////////  DocumentFactory.h
///////////////////////  This is a factory class, it will create instances of differnt classes
///////////////////////////////////////////////////
// We need to use smart pointers here because we are only using new in Create() and
//  never releasing the resource. Thus need to take benefit of automatic memory management.
using pDocument = std::unique_ptr<Document>;
#include <string>

class DocumentFactory {
public:
	// Factory method will accept a parameter and based on the parameter it will return
	// instances of different Document classes.
	pDocument Create(const std::string&);
};


///////////////////////////////////////////////////
///////////////////////  DocumentFactory.cpp
///////////////////////////////////////////////////
pDocument DocumentFactory::Create(const std::string &type) {
	if (type == "text")
		return std::make_unique<TextDocument>();
	else if(type == "spreadsheet")
		return std::make_unique<SpreadsheetDocument>();
	return nullptr;
}

///////////////////////////////////////////////////
///////////////////////  Application.h
///////////////////////  Will be responsible for user input.
///////////////////////////////////////////////////
// #pragma once
#include <memory>
class Document;


class Application {
    pDocument m_pDocument;
public:
    // creates a new document
    void New();
    void Open(); // open existing document
    void Save(); // save current document
};


///////////////////////////////////////////////////
/////////////////////// Application.cpp
///////////////////////////////////////////////////
void Application::New() {
    DocumentFactory factory;
    m_pDocument = factory.Create("text"); // we can take the input from the user
}

void Application::Open() {
	DocumentFactory factory;
    m_pDocument = factory.Create("text");
    m_pDocument->Read();
}

void Application::Save() {
    m_pDocument->Write();
}






///////////////////////////////////////////////////
///////////////////////  Client.cpp
///////////////////////////////////////////////////
// #include "Application.h"
int main() {
    Application app;
    app.New();
    app.Open();
    app.Save();

    return 0;
}















