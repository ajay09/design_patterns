/*
    A powerpoint like application where users can create slides and give presentation.

    
    Here the EditorView class is polling the Deck class for changes in data.
    And most of the time there won't be any changes for a long time.
    Thus the view classes will unnecessarily consume CPU cycles.

    Secondly we will have to create another polling thread for SlideShowView or any new
    view we want to introduce. This will put load on the resources and make the app
    slow and unresponsive.

    And what if we want to provide a feature where the users can provide new views
    at runtime? Thus polling is not a good design


    Objective :  All the veiws should be kept updated with the data in the Deck class.
                 The data is the contents of the slides.

    Better Design : Use the Observer Design Pattern instead of polling

                    In the Deck classs create a pointer of EditorView
                    and call EditorView::Display(); from Deck whenever 
                    a slide is modified.


                    This is a better approach as it doen't involve polling.
                    But there is an issue, if we now want to add SlideShowView to the
                    application, we have to modify the Deck class which violates OCP.


                    Problem : Deck is tightly coupled with the EditorView class
                              and it can't work with other views without modification.

                              So we shouldn't add the EditorView* class in the Deck class.
                              This violates the "Dependency Inversion Principle".
                              Instead of programming to implementation, we should program to
                              interface.
                    
 
*/


//////////////////////////////////////////
////////////////////////  Slide.h
//////////////////////////////////////////
#include <string>

class Slide {
    std::string m_Title;
    std::string m_Description;
public:
    Slide() = default;

    Slide(const std::string mTitle, const std::string mDesc) : m_Title{mTitle}, m_Description{mDesc} {}

    void SetTitle(std::string title) {
        m_Title = std::move(title);
    }

    void SetDescription(std::string desc) {
        m_Description = std::move(desc);
    }

    const std::string& GetTitle() const {
        return m_Title;
    }

    const std::string& GetDescription() const {
        return m_Description;
    }
};

// holds slides
//////////////////////////////////////////
////////////////////////  Deck.h
//////////////////////////////////////////
#include <vector>

class EditorView;

using SlidePtr = std::shared_ptr<Slide>;

class Deck {
    std::vector<SlidePtr> m_Slides;
    EditorView *m_pView;
public:
    void SetView(EditorView *pView) {
        m_pView = pView;
    }

    void AddSlide(SlidePtr slide);

    void ModifyTitle(size_t index, std::string title);

    void ModifyDescription(size_t index, std::string desc);

    size_t Size() const {
        return m_Slides.size();
    }

    const SlidePtr& GetAt(size_t index) const {
        if (index < 0 || index >= m_Slides.size()) 
            return nullptr;
        return m_Slides[index];
    }
};




// Allows to add a new slide or modify content of a slide
//////////////////////////////////////////
////////////////////////  EditorView.h
//////////////////////////////////////////
#include <iostream>

class EditorView {
    Deck *m_pDeck;
public:
    EditorView(Deck *pDeck) : m_pDeck(pDeck) {}

    void Display() {
        for (size_t index = 0; index < m_pDeck->Size(); ++index) {
            std::cout << "\n\tTitle : " << m_pDeck->GetAt(index)->GetTitle() << "\n";
            std::cout << "\n\tDescription : " << m_pDeck->GetAt(index)->GetDescription() << "\n";
        }
        // getchar();
    }
};


//////////////////////////////////////////
////////////////////////  SlideShowView.h
//////////////////////////////////////////
#include <iostream>

class SlideShowView {
    Deck *m_pDeck;
public:
    SlideShowView(Deck *pDeck) : m_pDeck(pDeck) {}

    void Display() {
        for (size_t index = 0; index < m_pDeck->Size(); ++index) {
            std::cout << "\n----------------------- SLIDE NO: " << index + 1 << " -----------------------\n";
            std::cout << m_pDeck->GetAt(index)->GetTitle() << "\n";
            std::cout << m_pDeck->GetAt(index)->GetDescription() << "\n";
            std::cout << "---------------------------------------------------------------------\n";
        }
    }
};



void Deck::AddSlide(SlidePtr slide) {
    m_Slides.push_back(slide);
    m_pView->Display();
}

void Deck::ModifyTitle(size_t index, std::string title) {
    if (index < 0 || index >= m_Slides.size()) return;
    m_Slides[index]->SetTitle(title);
    m_pView->Display();
}

void Deck::ModifyDescription(size_t index, std::string desc) {
    if (index < 0 || index >= m_Slides.size()) return;
    m_Slides[index]->SetDescription(desc);
    m_pView->Display();
}



#include <chrono>
#include <thread>


void CheckChanges(EditorView &cv) {
    using namespace std::chrono_literals;
    while (true) {
        std::this_thread::sleep_for(500ms);
        system("clear");
        cv.Display();
    }
}

int main() {
    Deck deck{};
    EditorView ev{&deck};

    deck.SetView(&ev);

    // std::thread pollingThread{CheckChanges, std::ref(ev)};
    // pollingThread.detach();
    
    deck.AddSlide(std::make_shared<Slide>("Training", "C++ for beginners"));
    deck.AddSlide(std::make_shared<Slide>("Objective", "Learn the basics of C++"));
    deck.AddSlide(std::make_shared<Slide>("What is C++", "C++ is a general programming language"));

    // ev.Display();


    // SlideShowView sv(&deck);
    // sv.Display();
    getchar();

    return 0;
}






