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


    Also we are using new to allocate a TextDocument instance in Create()
    but never recovering that memory. Thus over implementation has memory leaks.
    Thus we should use smart pointers instead of raw pointers for automatic
    memory management.

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
///////////////////////  Application.h
///////////////////////  Will be responsible for user input.
///////////////////////////////////////////////////
// #pragma once
class Document;

class Application {
    Document *m_pDocument;
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
    m_pDocument = new TextDocument();
}

void Application::Open() {
    m_pDocument = new TextDocument();
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















