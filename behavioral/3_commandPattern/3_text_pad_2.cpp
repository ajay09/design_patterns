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


	
	Solution - 1 => Use function pointers instead of function names to invoke functions.

					But we can't do it here because the functions are member functions and not normal functions.
					And calling member function using function pointers is not possible we will have to use
					pointer to member. 

					But we still have to use the name of the Class even if we use pointer to member.
					But there is a way around it in C++.


		Menu is no longer tightly coupled with the application class.
		We can configure the Menu options at runtime.


	Solution - 2 => Use Command Design Pattern.
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
#include <functional>
#include <map>

class Menu {
	using Callback = std::function<void()>;
	using CallbackInfo = std::tuple<std::string, Callback>;
	using Table = std::map<int, CallbackInfo> ;
	Table m_OptionsTable;
	
	// returns an iterator to the next callback after the display callback.
	Table::iterator DisplayData() {
		auto iter = m_OptionsTable.begin();
		if (iter->first == 0) { // if the key is 0
			std::get<1>(iter->second)();  // in place of  m_pApp->Display();
			++iter;						  // The first entry in map is the Display callback
		}
		return iter;
	}

	void DisplayMenuOptions(Table::iterator iter) {
		std::cout << "\n------------------------------------------------\n";
		for (; iter != m_OptionsTable.end(); ++iter) {
			std::cout << iter->first << ". " << std::get<0>(iter->second) << "\n";
		}
	}

	int GetUserChoice() {
		size_t choice;
		std::cout << "Your choice (0 to exit)?\n";
		std::cin >> choice;
		if (choice == 0)
			return false;
		if (choice >= m_OptionsTable.size()) {
			Message("Unknown option.");
		} else {
			std::get<1>(m_OptionsTable[choice])();
		}
		return true;
	}
public:
	void Init(int choice, const std::string &menuText, Callback callback) {
		m_OptionsTable[choice] = std::make_tuple(menuText, callback);
	}


	void Run() {
		while (true) {
			auto iter = DisplayData();
			DisplayMenuOptions(iter);
			if (!GetUserChoice()) {
				break;
			}
		}
		Message("Application terminated");
	}
};















int main() {
	Application app{};
	Menu menu{};

	// This will not work because &Application::Display is not a function pointer but a pointer to
	// a member function. We need to convert it to function pointer using std::bind
	menu.Init(0, "", std::bind(&Application::Display, &app));
	menu.Init(1, "Add", std::bind(&Application::InputAddText, &app));
	menu.Init(2, "Insert", std::bind(&Application::InputInsertText, &app));
	menu.Init(3, "Overwrite", std::bind(&Application::InputOverwriteText, &app));
	menu.Init(4, "Erase", std::bind(&Application::InputRemoveText, &app));
	menu.Init(5, "Change color", std::bind(&Application::InputSetColor, &app));
	menu.Init(6, "Toggle bold", std::bind(&Application::InputSetBold, &app));

	menu.Run();

	return 0;
}