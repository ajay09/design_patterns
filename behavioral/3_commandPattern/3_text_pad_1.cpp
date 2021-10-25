/*
	Create  a Notepad like application where a user can enter text.
	And can perform basic editing opertions, e.g add text, remove text, insert text, change formatting, etc.

		Invoker										Receiver
	____________________						____________________
	|		Menu   	   |						|	Application    |
	--------------------						--------------------
	| 1. Add		   |						| 				   |		
	| 2. Remove		   |						| 	AddText		   |		
	| 3. Insert		   |						| 				   |		
	| 4. Overwrite	   |						| 	RemoveText	   |				
	| 5. Bold		   |						| 				   |		
	| 6. Colorize	   |						| 	InsertText	   |				
	--------------------						--------------------
	User Interface									Different operations that can be performed on the text
	Thus for Menu we will create					 We don't want to implement the functionality of handling the Menu
	a separate class and invoke						 in the Application class, because then the application class
	the Application methods							 will be overburdened with different responsibilities and would
	using the Command Design Pattern				 violate the SRP.

	

	There is a huge problem with our design in the following code :
	 - The Menu class is tightly coupled with the Application class.
	 	If anything changes in the Application, Menu will also have to change.
	 	The coupling is due to the pointer of the Application class in the Menu class and the
	 	name of the Applicaiton member function being used directly. 

	 - To remove the dependecy of the Menu on the Application we use the Command Design Pattern

     - Menu should be able to invoke the methods in the Application without getting tightly coupled
	   with the Application name.

	 - This way we will be able to reuse the Menu for some other Application.
*/

#include <iostream>
// This will pause the program and prompt the user for input.
void Message(const std::string &text) {
	std::cout << "\n----------- " << text << " -----------\n";
	system(R"(read -p "Press enter to continue!")");
	system("clear");
}


////////////////////////////////////////
////////////////////  Application.h
////////////////////////////////////////
#include "Console.h"
#include <string>
#include <algorithm>



class Application {
	std::string m_Text;
	Color m_Color;
	bool m_Bold;
public:
	Application() : m_Color{Color::DEFAULT}, m_Bold{false} {}

	void AddText(const std::string &text) { m_Text += text + " "; }
	void RemoveText(size_t index, size_t count) { m_Text.erase(index, count); }
	void OverwriteText(size_t index, const std::string &text) {
		std::copy(text.begin(), text.end(), m_Text.begin() + index);
	}
	void InsertText(size_t index, const std::string &text) { m_Text.insert(index, text); }
	void SetColor(Color color) { m_Color = color; }
	void SetBold(bool bold) { m_Bold = bold; }
	bool IsBold() const { return m_Bold; }
	Color GetColor() const { return m_Color; }
	const std::string& GetText() const { return m_Text; }
	void Display() const { Console::WriteLine(m_Text, m_Color, m_Bold); }

	// Menu class will invoke these and these will get input from user.
	void InputAddText();
	void InputRemoveText();
	void InputOverwriteText();
	void InputInsertText();
	void InputSetColor();
	void InputSetBold();
};

void Application::InputAddText() {
	std::string text;
	std::cout << "Enter text to add : ";
	std::cin.ignore(); // to ignore any remaining characters in the input stream
					   // required when using getline because getline by default reads till next \n
	std::getline(std::cin, text);
	AddText(text);
	Message("Text added!");
}

void Application::InputRemoveText() {
	size_t start, count;
	std::cout << "Starting index? ";
	std::cin >> start;
	std::cout << "How many characters to remove? ";
	std::cin >> count;
	RemoveText(start, count);
	Message("Text removed!");
}

void Application::InputOverwriteText() {
	std::string text;
	std::cout << "Enter text : ";
	std::cin.ignore();
	getline(std::cin, text);
	std::cout << "Position of overwrite? ";
	size_t index{};
	std::cin >> index;
	OverwriteText(index, text);
	Message("Text overwritten!");
}

void Application::InputInsertText() {
	std::string text;
	std::cout << "Enter text : ";
	std::cin.ignore();
	getline(std::cin, text);
	std::cout << "Position of insertion? ";
	size_t index{};
	std::cin >> index;
	InsertText(index, text);
	Message("Text inserted!");
}

void Application::InputSetColor() {
	char choice;
	Color color{};
	std::cout << "Choose color (r, g, b, w) : ";
	std::cin >> choice;
	switch (choice) {
		case 'r':
			color = Color::RED;
			break;
		case 'g':
			color = Color::GREEN;
			break;
		case 'b':
			color = Color::BLUE;
			break;
		case 'w':
			color = Color::WHITE;
			break;
		default:
			color = Color::DEFAULT;
			break;
	}
	SetColor(color);
	Message("Text color set!");
}

void Application::InputSetBold() {
	bool bold;
	std::cout << "Press (b) for bold or any other key for normal text";
	char ch;
	std::cin >> ch;
	if (ch == 'b') {
		SetBold(true);
	} else {
		SetBold(false);
	}
	Message("Text bold property set!");
}




////////////////////////////////////////
////////////////////  	Menu.h
////////////////////////////////////////
class Menu {
	Application *m_pApp;
public:
	Menu(Application *pApp) : m_pApp{pApp} {};

	void Run() {
		bool exit{false};
		int choice{};
		while (!exit) {
			m_pApp->Display();
			std::cout << "\n------------------------------------------------\n";
			std::cout << "1. Add\n";
			std::cout << "2. Insert\n";
			std::cout << "3. Overwrite\n";
			std::cout << "4. Erase\n";
			std::cout << "5. Change color\n";
			std::cout << "6. Toggle bold\n";
			std::cout << "Your choice (0 to exit)?\n";
			std::cin >> choice;
			std::cout << "\n";

			switch (choice) {
				case 0 :
					exit = true;
					break;
				case 1 :
					m_pApp->InputAddText();
					break;
				case 2 :
					m_pApp->InputInsertText();
					break;
				case 3 :
					m_pApp->InputOverwriteText();
					break;
				case 4 :
					m_pApp->InputRemoveText();
					break;
				case 5 :
					m_pApp->InputSetColor();
					break;
				case 6 :
					m_pApp->InputSetBold();
					break;
			}
		}
	}
};















int main() {
	Application app{};
	Menu menu{&app};

	menu.Run();

	return 0;
}