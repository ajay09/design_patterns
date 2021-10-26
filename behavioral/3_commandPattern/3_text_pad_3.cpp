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


	3_text_pad_1.cpp
		Initially we stored a pointer to the Application in the Menu class to invoke the functions.
		This led to tight coupling between the Menu and the Application class.
		But we wanted to use the Menu with other classes as well so we wanted 
		to remove this coupling.

	3_text_pad_2.cpp
	    provdies the first solution to this.

	    We invoke the required functions through their addresses. So we created a map in Menu
	    which stored the function pointer. But the problem is we wanted to invoke the methods
	    of theApplication class and we can not store the address of a method in a function pointer.

	    Thus we used "bind", which acted as an "adapter" and converted a pointer to the member
	    into a function pointer using bind.

	    Now we can reuse the Menu with other classes as well.
	

	Solution - 2 => Use Command Design Pattern.

		We are still using function pointers to invoke the functions and function pointers are
		inflexible. As we had to use bind in order to invoke the methods of the Applicaiton class.
		To add more flexibility to the design we should use the Command Design Pattern.




						
										 <<Interface>>
										_______________
										|  Command    |
				;---------------------->--------------- <|------------------;
				|						|	Execute() |					    |
				|						---------------					    |
				|															|		
		_______________												_______________			
		|     Menu    |												| Application |			
		---------------												---------------			
		|			  |												|			  |			
		---------------												---------------			


			- Interface Command contains a pure-virtual function Execute()
			- Menu class will have a pointer to the Command Interface.
			- And any class that want to handle a request from Menu, will
			  inherit from the Command Class. Thus Application class inherits
			  from the Command interface.
			- Now we don't need the function pointer or bind.
			- To handle the request form Menu all we have to do is simply set the command.
			  The command could be any class that inherits from the Command class and overrides
			  the Execute function.


	Next  =>  Create a separate class and move the implementation of commands there.
	          This will allow the Command classes to store state while the operation is bein performed.
	          This will allow us to implement undo/redo later.
*/

#include <iostream>
// This will pause the program and prompt the user for input.
void Message(const std::string &text) {
	std::cout << "\n----------- " << text << " -----------\n";
	system(R"(read -p "Press enter to continue!")");
	system("clear");
}



////////////////////////////////////////
////////////////////  Command.h
////////////////////////////////////////
class Command {
public:
	virtual void Execute(int id) = 0;
	virtual ~Command() = default;
};


////////////////////////////////////////
////////////////////  Application.h
////////////////////////////////////////
#include "Console.h"
#include <string>
#include <algorithm>



class Application : public Command{
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
	void InputInsertText();
	void InputOverwriteText();
	void InputRemoveText();
	void InputSetColor();
	void InputSetBold();


	void Execute(int id) override {
		switch (id) {
			case 0:
				Display();
				break;
			case 1:
				InputAddText();
				break;
			case 2:
				InputInsertText();
				break;
			case 3:
				InputOverwriteText();
				break;
			case 4:
				InputRemoveText();
				break;
			case 5:
				InputSetColor();
				break;
			case 6:
				InputSetBold();
				break;
		}
	}
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
	using Callback = Command *;
	using CallbackInfo = std::tuple<std::string, Callback>;
	using Table = std::map<int, CallbackInfo> ;
	Table m_OptionsTable;
	
	// returns an iterator to the next callback after the display callback.
	Table::iterator DisplayData() {
		auto iter = m_OptionsTable.begin();
		if (iter->first == 0) { // if the key is 0
			std::get<1>(iter->second)->Execute(0);  // in place of  m_pApp->Display();
			++iter;						  		   // The first entry in map is the Display callback
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
			std::get<1>(m_OptionsTable[choice])->Execute(choice);
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

	menu.Init(0, "", &app);
	menu.Init(1, "Add", &app);
	menu.Init(2, "Insert", &app);
	menu.Init(3, "Overwrite", &app);
	menu.Init(4, "Erase", &app);
	menu.Init(5, "Change color", &app);
	menu.Init(6, "Toggle bold", &app);

	menu.Run();

	return 0;
}