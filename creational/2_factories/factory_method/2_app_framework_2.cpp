/*
 We wish to create a framework that other developers can use to create their own apps.

 The framework will provide support for managing different kinds of documents.
 So using our framework, a programmer can create an application that can display 
 different kinds of documents. Data may be text, graphics or video 
 To manage this data as a document, our framework will provide support through
 which it'll be easy to maintain this kind of data.

 Thus we will add a class called Application - responsible for user input and to display the data
 											    a document may have.
                                 Document    - to manage the data

                                 Appication will use the features of the Document and provide
                                 various functionalities such as displaying data that is there
                                 in the document.
                                 But the Application won't know what is the kind of data that
                                 the document has. That's why we will provide this Document in
                                 our framework as an Abstract class.

            |Document |         |Application |         
            |_________|<--------|____________|
            |Read()   |         |            |
            |Write()  |         |            |
                ^
                |
                |                   If the application wants to manage text data, then the user
            |TextDocument |         will have to create a class TextDocument and inherit from
            |_____________|         Document. It will override Read() and Write() methods.
            |Read()       |         An Application will be able to use the text document through
            |Write()      |         the base class Document.

                                    Thus this framework can provide support to manage any kind
                                    of document.
*/


/*  
    Issue with the below implementation.

    If we want to use the application framework with a different kind of document.
    Then we will have to make changes to the Application class New() and Open() function.
    And it is a framework class and we are not allowed to modify this class.

    The Application class is tightly coupled with TextDocument.
    We would like to remove this dependency on TextDocument because the application should
    be able to work with any kind of user-defined Document class.

    Factory Method will save us here.
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

// to implement Factory Method the Application class should define a virtual method
// that will return a Document instance.
///////////////////////////////////////////////////
///////////////////////  Application.h
///////////////////////  Will be responsible for user input.
///////////////////////////////////////////////////
// #pragma once
#include <memory>
class Document;

// We need to use smart pointers here because we are only using new in Create() and
//  never releasing the resource. Thus need to take benefit of automatic memory management.
using pDocument = std::unique_ptr<Document>;
class Application {
    pDocument m_pDocument;
public:
    // creates a new document
    void New();
    void Open(); // open existing document
    void Save(); // save current document

    virtual pDocument Create() { return nullptr; } // factory method with is default implementation.
};


// Then we inherit a class from Application that will override the Create() method.
class TextApplication : public Application{
public:
    pDocument Create() override;
};


// Since we added a new kind of Document therefor we need to create a new kind of creator class also
class SpreadsheetApplication : public Application {
public:
    pDocument Create() override;
};


///////////////////////////////////////////////////
/////////////////////// SpreadsheetApplication.cpp
///////////////////////////////////////////////////
pDocument SpreadsheetApplication::Create() {
    return std::make_unique<SpreadsheetDocument>();
}


///////////////////////////////////////////////////
/////////////////////// TextApplication.cpp
///////////////////////////////////////////////////
pDocument TextApplication::Create() {
    return std::make_unique<TextDocument>();
}


///////////////////////////////////////////////////
/////////////////////// Application.cpp
///////////////////////////////////////////////////
void Application::New() {
    // m_pDocument = new TextDocument();
    m_pDocument = Create();
}

void Application::Open() {
    m_pDocument = Create();
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
    TextApplication tApp;
    tApp.New();
    tApp.Open();
    tApp.Save();

    SpreadsheetApplication sApp;
    sApp.New();
    sApp.Open();
    sApp.Save();
    return 0;
}















