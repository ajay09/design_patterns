/*
	Given a application which can display text in a window.

	The user can enter some text in the application which
	will be displayed in the window.

	We have to add a functionality where the user can search
	for text in the window.

	We will create a serch-dialog where the user can specify the serach item and click on find.
	The dialog will interact with the main window, search for the text and then highlight
	it for the user.

	- In a simple implementation the class that creates the find dialog will have a pointer
	  to the main window and execute some function that will perform the actual search.

	- But we want to make the find dialog a reusable component, we should be able to use it
	  with other apps and don't want it to be tightly coupled with the main window.

	- In this example, the Find window is the Invoker
	                       Main window is the Receiver
	
*/

////////////////////////////////////////////
////////////////////////  Command.h
////////////////////////////////////////////
#include <string>

class Command {
public:
	virtual void ExecuteFind(const std::string text) = 0;
	virtual ~Command() = default;
};


////////////////////////////////////////////
////////////////////////  MainWindow.h
////////////////////////////////////////////
#include <string>
#include <iostream>

class MainWindow : public Command {
	std::string m_Text;
public:
	MainWindow() {
		m_Text.assign(R"(Given a application which can display text in a window.

	The user can enter some text in the application which
	will be displayed in the window.

	We have to add a functionality where the user can search
	for text in the window.

	We will create a serch-dialog where the user can specify the serach item and click on find.
	The dialog will interact with the main window, search for the text and then highlight
	it for the user.

	- In a simple implementation the class that creates the find dialog will have a pointer
	  to the main window and execute some function that will perform the actual search.

	- But we want to make the find dialog a reusable component, we should be able to use it
	  with other apps and don't want it to be tightly coupled with the main window.

	- In this example, the Find window is the Invoker
	                       Main window is the Receiver)");
	}

	void ExecuteFind(const std::string text) override {
		if (text.empty())
			return;

		size_t position{};
		size_t count{};

		while ((position = m_Text.find(text, position)) != std::string::npos) {
			std::cout << "Found at index : " << position << "\n";
			position += text.size();
			++count;
		}

		if (count != 0)
			std::cout << "Total occurances : " << count << "\n";
		else
			std::cout << "Not found\n";
	}
};





////////////////////////////////////////////
////////////////////////  FindDialog.h
////////////////////////////////////////////
class FindDialog {
	std::string m_SearchText;
	Command *m_pCmd;
public:
	FindDialog(Command *mPCmd) : m_pCmd{mPCmd} {}

	void SetSearchText(const std::string &text) {
		m_SearchText = text;
	}

	void Find() {
		m_pCmd->ExecuteFind(m_SearchText);
	}
};




int main() {
	MainWindow win{};
	FindDialog dlg{&win};
	dlg.SetSearchText("window");
	dlg.Find();

	return 0;
}


/*
	           --------------         m_pCmd   ------------------
	           | FindDialog |<>--------------->| Command        |
	           --------------                  ------------------
	  								     	   | ExecuteFind()  |
	           						   	  	   ------------------
	  								   		      /_\
	  								   		       |
	  								   		       |
											-----------------------
											|   MainWindow        | 
										    -----------------------
										    |   ExecuteFind()     |
										    -----------------------


	- FindDialog is the Invoker
	  MainWindow is the Receiver

	- This is used in UI apps where the dialog class has a callback in the main Window class.


*/