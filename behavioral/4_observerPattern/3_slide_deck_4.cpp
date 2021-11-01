/*
    A powerpoint like application where users can create slides and give presentation.



    Issue with the design in 3_slide_deck_3.cpp :
        - When a new slide is added the view displays all the previous slides.
        - Only that part of the view should be updated that contains the modified data.
          Because painting on the screen is expensive.


    - Modify design so that only the updated slide is display when an update is performed.
    - Thus views should contain logic to determine which slide to display.
    - Add parameters to the Notificaiton method (here Display).
      The parameters can be use to represent :
        - Data for the Observers
        - Subject that sent the notification
        - Metadat for identifying the change in the subject.
    


    Push Model
    The Subject sends Observers detailed info about the change
    - not efficient for large data.
    - not all observers may require the data.
    - difficult to generalize data for different types of observers.


    Pull Model
    The Subject only sends a notification to the Observer, then the Observer asks for details
    later. This can be used with any kind of Observer.
    But it might get become difficult for the Observers to determine what data changed.



    In our example we can't use the Pull model because the Views don't have info about the slide that has changed. 
    Also it won't be desirable to send the entire slide data to all the views, because not all views may require all
    the data.

    Thus here we use a combination of the pull and the push model, and send the index of the slide that has
    changed.
 
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

//////////////////////////////////////////
//////////////////////////////   View.h
//////////////////////////////////////////
class View {
public:
    virtual void Display(size_t index) = 0;
    ~View() = default;
};

// holds slides
//////////////////////////////////////////
////////////////////////  Deck.h
//////////////////////////////////////////
#include <vector>
#include <list>

using SlidePtr = std::shared_ptr<Slide>;

class Deck {
    std::vector<SlidePtr> m_Slides;
    std::list<View*> m_Views;
public:
    void Attach(View *pView) {
        m_Views.push_back(pView);
    }

    void Detach(View *pView) {
        m_Views.remove(pView);
    }

    void Notify(size_t index) {
        for (auto view : m_Views) {
            view->Display(index);
        }
    }

    void AddSlide(SlidePtr slide) {
        m_Slides.push_back(slide);
        Notify(m_Slides.size() - 1);
    }

    void ModifyTitle(size_t index, std::string title) {
        if (index < 0 || index >= m_Slides.size()) return;
        m_Slides[index]->SetTitle(title);
        Notify(index);
    }

    void ModifyDescription(size_t index, std::string desc) {
        if (index < 0 || index >= m_Slides.size()) return;
        m_Slides[index]->SetDescription(desc);
        Notify(index);
    }

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

class EditorView : public View {
    Deck *m_pDeck;
public:
    EditorView(Deck *pDeck) : m_pDeck(pDeck) {}

    void Display(size_t index) override {
        std::cout << "\n\tTitle : " << m_pDeck->GetAt(index)->GetTitle() << "\n";
        std::cout << "\n\tDescription : " << m_pDeck->GetAt(index)->GetDescription() << "\n";
        // getchar();
    }
};


//////////////////////////////////////////
////////////////////////  SlideShowView.h
//////////////////////////////////////////
#include <iostream>

class SlideShowView  : public View {
    Deck *m_pDeck;
public:
    SlideShowView(Deck *pDeck) : m_pDeck(pDeck) {}

    void Display(size_t index) override {
        std::cout << "\n----------------------- SLIDE NO: " << index + 1 << " -----------------------\n";
        std::cout << m_pDeck->GetAt(index)->GetTitle() << "\n";
        std::cout << m_pDeck->GetAt(index)->GetDescription() << "\n";
        std::cout << "---------------------------------------------------------------------\n";
    }
};






#include <chrono>
#include <thread>


// void CheckChanges(EditorView &cv) {
//     using namespace std::chrono_literals;
//     while (true) {
//         std::this_thread::sleep_for(500ms);
//         system("clear");
//         cv.Display();
//     }
// }

int main() {
    Deck deck{};
    EditorView ev{&deck};

    deck.Attach(&ev);

    // std::thread pollingThread{CheckChanges, std::ref(ev)};
    // pollingThread.detach();
    
    deck.AddSlide(std::make_shared<Slide>("Training", "C++ for beginners"));
    deck.AddSlide(std::make_shared<Slide>("Objective", "Learn the basics of C++"));
    deck.AddSlide(std::make_shared<Slide>("What is C++", "C++ is a general programming language"));

    // ev.Display();


    SlideShowView sv(&deck);
    deck.Attach(&sv);

    std::cout << "Modifying slide #3\n";
    deck.ModifyTitle(2, "Overview");

    getchar();

    return 0;
}






