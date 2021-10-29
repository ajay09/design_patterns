/*
	Change the Command Design from 3_text_pad_3.cpp and move the commands from the
	Application class to their own Command classes.

	Thus we are converting a function call into an object.
	The advantage would be, an object can store state, while a function cannot.

	Instead of Application interacting with Command we have converted the commands into objects.

													  <<interface>>
		_______________			m_OptionsTable	    _______________			
		|     Menu    |---------------------------->|   Command   |			
		---------------								---------------			
		|			  |								|			  |			
		---------------								---------------	
														  /_\
														   |
										___________________|________________________________
										|					    |					|
	_______________	     m_pApp    __________________  	__________________ 	__________________
	| Application |<---------------| CommandDisplay |  	| CommandAdd     | 	| CommandInsert  |
	---------------	               ------------------  	------------------ 	------------------ ...
	|			  |	               |			    |  	|			     |  |			     |
	---------------	               ------------------  	------------------ 	------------------


	Using Command we can implement :
		- Undo & redo in an application
		- transactions that can be rolled back
	
	- Since Commands are object thus we can compose them together and perform macro or composite commands.
		We can also create a queue of commands.

	

	Undo / Redo
	- Command can support undo and redo by storing state.
	- State can be the receiver object if it is small, or the arguments that are passed
      to the receiver for the action. or the original values in the Receiver that can 
      change as a result of the action.
    - If the application require only one level of undo then it will require the application
      to store only the last executed command.
    - For multiple levels of undo / redo, the application needs to store the history of the
      commands in a list.
      This list should be traversed backwards to reverse the effect of command execution.
      For redo the list need to be traversed in forward direction.
	- Copies of existing commands have to be stored in the list to implement undo/redo
	  because as soon as a command executes the state will change.
	- For a command to undo/redo the receiver must provide appropriate opertaions.


Without using command pattern : 
	We can use a Stack to store the changes made by the user.
	And each stack entry will store the incremental changes.
	In case of change of color or boldness what are we going to store in the stack. We can store
	the string, we need to store some different kind of info.

	The ideal way would have been, instead of storing the changes we would have stored the operations
	that are performed and undo these operations later. Without the Command pattern the operations are
	simply function calls and we can't store function calls in a stack. At the most we can store the
	addresses of the functions but through the addresses we can't know how to undo the operation.


	The Command Pattern suggests us to convert function into object. Instead of implementing the functionality 
	of a request in a function we can implement it in a class and instances of these classes are command
	objects. When the user performs an action the command handles that action and it can also store some
	state because command is an object.

	When we have to undo a command we simply pop the command form the stack and invoke its undo member
	function. That member function will restore the state.


	- Whenever a Command is executed we create a copy and store it in the stack.
	  We need to create the copy because if the command is performed multiple times then the state that it store
	  will get modified and we could not undo and redo. That's why create a copy before storing the command
	  to the stack.
	-

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
	virtual void Execute() = 0;
	virtual void Undo() = 0;   // to support undo and redo.
	virtual void Redo() = 0;
	virtual ~Command() = default;
};



// Monostate
// Will manage the stack of the Commands
////////////////////////////////////////
////////////////////  	UndoManager.h
////////////////////////////////////////
#include <stack>

class UndoManager {
	static std::stack<std::shared_ptr<Command>> m_Undo;
	static std::stack<std::shared_ptr<Command>> m_Redo;
	UndoManager() = default;
public:
	static void AddCommand(std::shared_ptr<Command> pCmd) {
		m_Undo.push(pCmd);
	}

	static bool Undo() {
		if (m_Undo.empty()) return false;

		auto pCmd = m_Undo.top(); m_Undo.pop();
		pCmd->Undo();
		m_Redo.push(pCmd);

		return true;
	}

	static bool Redo() {
		if (m_Redo.empty()) return false;

		auto pCmd = m_Redo.top(); 
		m_Redo.pop();
		pCmd->Redo();
		m_Undo.push(pCmd);


		return true;
	}
};


std::stack<std::shared_ptr<Command>> UndoManager::m_Undo;
std::stack<std::shared_ptr<Command>> UndoManager::m_Redo;



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
	void InputInsertText();
	void InputOverwriteText();
	void InputRemoveText();
	void InputSetColor();
	void InputSetBold();
};


////////////////////////////////////
//////////////////  CommandDisplay.cpp
////////////////////////////////////
class CommandDisplay : public Command {
	Application *m_pApp;
public:
	CommandDisplay(Application* pApp) : m_pApp{pApp} {}

	void Execute() override {
		m_pApp->Display();
	}

	void Undo() override {}

	void Redo() override {}
};


////////////////////////////////////
//////////////////  CommandAdd.cpp
////////////////////////////////////
class CommandAdd : public Command {
	Application *m_pApp;

	std::string m_Text; // store the text that was added.
public:
	CommandAdd(Application* pApp) : m_pApp{pApp} {}

	void Execute() override {
		std::cout << "Enter text to add : ";
		std::cin.ignore(); // to ignore any remaining characters in the input stream
						   // required when using getline because getline by default reads till next \n
		std::getline(std::cin, m_Text);
		m_pApp->AddText(m_Text);
		
		// create a copy and store to the stack.
		// even though we have not added a copy constructor to the command classes
		// but since these classes don't have ownership semantics so we can use the compiler genreated copy constructor.
		// Or you can use the Prototype Desgin Pattern.
		UndoManager::AddCommand(std::make_shared<CommandAdd>(*this));
		
		Message("Text added!");
	}

	void Undo() override {
		auto count = m_Text.size() + 1; // 1 is for the ' ' added while adding.
		auto index = m_pApp->GetText().size() - count;
		m_pApp->RemoveText(index, count);
	}

	void Redo() override {
		m_pApp->AddText(m_Text);
	}
};

////////////////////////////////////
//////////////////  CommandRemove.cpp
////////////////////////////////////
class CommandRemove : public Command {
	Application *m_pApp;

	std::string m_Text;
	size_t m_Index;
public:
	CommandRemove(Application* pApp) : m_pApp{pApp} {}

	void Execute() override {
		size_t count;
		std::cout << "Starting index? ";
		std::cin >> m_Index;
		std::cout << "How many characters to remove? ";
		std::cin >> count;
		m_Text = m_pApp->GetText().substr(m_Index, count);
		m_pApp->RemoveText(m_Index, count);

		UndoManager::AddCommand(std::make_shared<CommandRemove>(*this));

		Message("Text removed!");
	}

	void Undo() override {
		m_pApp->InsertText(m_Index, m_Text);
	}

	void Redo() override {
		m_pApp->RemoveText(m_Index, m_Text.size());
	}
};

////////////////////////////////////
//////////////////  CommandOverWrite.cpp
////////////////////////////////////
class CommandOverWrite : public Command {
	Application *m_pApp;

	size_t m_Index;
	std::string m_Text;
public:
	CommandOverWrite(Application* pApp) : m_pApp{pApp} {}

	void Execute() override {
		std::string text;
		std::cout << "Enter text : ";
		std::cin.ignore();
		getline(std::cin, text);
		std::cout << "Position of overwrite? ";
		std::cin >> m_Index;
		m_Text = m_pApp->GetText().substr(m_Index, text.size());
		m_pApp->OverwriteText(m_Index, text);

		UndoManager::AddCommand(std::make_shared<CommandOverWrite>(*this));

		Message("Text overwritten!");
	}

	void Undo() override {
		auto text = m_pApp->GetText().substr(m_Index, m_Text.size());
		m_pApp->OverwriteText(m_Index, m_Text);
		m_Text = text; // for redo
	}

	void Redo() override {
		auto text = m_pApp->GetText().substr(m_Index, m_Text.size());
		m_pApp->OverwriteText(m_Index, m_Text);
		m_Text = text;
	}
};

////////////////////////////////////
//////////////////  CommandInsert.cpp
////////////////////////////////////
class CommandInsert : public Command {
	Application *m_pApp;

	std::string m_Text;
	size_t m_Index;
public:
	CommandInsert(Application* pApp) : m_pApp{pApp} {}

	void Execute() override {
		std::cout << "Enter text : ";
		std::cin.ignore();
		getline(std::cin, m_Text);
		std::cout << "Position of insertion? ";
		std::cin >> m_Index;
		m_pApp->InsertText(m_Index, m_Text);

		UndoManager::AddCommand(std::make_shared<CommandInsert>(*this));

		Message("Text inserted!");
	}

	void Undo() override {
		auto count = m_Text.size();
		m_pApp->RemoveText(m_Index, count);
	}

	void Redo() override {
		m_pApp->InsertText(m_Index, m_Text);
	}
};


////////////////////////////////////
//////////////////  CommandSetColor.cpp
////////////////////////////////////
class CommandSetColor : public Command {
	Application *m_pApp;

	Color m_Color;
public:
	CommandSetColor(Application* pApp) : m_pApp{pApp} {}

	void Execute() override {
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
		m_Color = m_pApp->GetColor();
		m_pApp->SetColor(color);

		UndoManager::AddCommand(std::make_shared<CommandSetColor>(*this));

		Message("Text color set!");
	}

	void Undo() override {
		auto color = m_pApp->GetColor();
		m_pApp->SetColor(m_Color);
		m_Color = color;
	}

	void Redo() override {
		auto color = m_pApp->GetColor();
		m_pApp->SetColor(m_Color);
		m_Color = color;
	}
};

////////////////////////////////////
//////////////////  CommandSetBold.cpp
////////////////////////////////////
class CommandSetBold : public Command {
	Application *m_pApp;

	bool m_IsBold;
public:
	CommandSetBold(Application* pApp) : m_pApp{pApp} {}

	void Execute() override {
		bool bold;
		std::cout << "Press (b) for bold or any other key for normal text";
		char ch;
		std::cin >> ch;
		m_IsBold = m_pApp->IsBold();
		if (ch == 'b') {
			m_pApp->SetBold(true);
		} else {
			m_pApp->SetBold(false);
		}

		UndoManager::AddCommand(std::make_shared<CommandSetBold>(*this));

		Message("Text bold property set!");
	}

	void Undo() override {
		auto bold = m_pApp->IsBold();
		m_pApp->SetBold(m_IsBold);
		m_IsBold = bold; // for redo
	}

	void Redo() override {
		auto bold = m_pApp->IsBold();
		m_pApp->SetBold(m_IsBold);
		m_IsBold = bold; // for redo
	}
};




/////////////////////////////////
/////////////////  CommandUndo.cpp
/////////////////////////////////
class CommandUndo : public Command {
public:
	void Execute() override {
		if (UndoManager::Undo()) {
			Message("Performed undo!");
		}
		else {
			Message("Nothing to undo.");
		}
	}

	void Undo() override {
	}
	
	void Redo() override {}
};


/////////////////////////////////
/////////////////  CommandRedo.cpp
/////////////////////////////////
class CommandRedo : public Command {
public:
	void Execute() override {
		if (UndoManager::Redo()) {
			Message("Performed redo!");
		}
		else {
			Message("Nothing to redo.");
		}
	}

	void Undo() override {
	}
	
	void Redo() override {}
};




////////////////////////////////////////
////////////////////  	Menu.h
////////////////////////////////////////
#include <functional>
#include <map>

class Menu {
	using Callback = std::shared_ptr<Command>;
	using CallbackInfo = std::tuple<std::string, Callback>;
	using Table = std::map<int, CallbackInfo> ;
	Table m_OptionsTable;
	
	// returns an iterator to the next callback after the display callback.
	Table::iterator DisplayData() {
		auto iter = m_OptionsTable.begin();
		if (iter->first == 0) { // if the key is 0
			std::get<1>(iter->second)->Execute();  // in place of  m_pApp->Display();
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
			std::get<1>(m_OptionsTable[choice])->Execute();
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

	std::shared_ptr<CommandDisplay>	   cmdDisplay	 = std::make_shared<CommandDisplay>(&app);
	std::shared_ptr<CommandAdd>		   cmdAdd		 = std::make_shared<CommandAdd>(&app);
	std::shared_ptr<CommandInsert>     cmdInsert	 = std::make_shared<CommandInsert>(&app);
	std::shared_ptr<CommandOverWrite>  cmdOverwrite	 = std::make_shared<CommandOverWrite>(&app);
	std::shared_ptr<CommandRemove>	   cmdRemove	 = std::make_shared<CommandRemove>(&app);
	std::shared_ptr<CommandSetColor>   cmdSetColor	 = std::make_shared<CommandSetColor>(&app);
	std::shared_ptr<CommandSetBold>	   cmdSetBold	 = std::make_shared<CommandSetBold>(&app);
	std::shared_ptr<CommandUndo>	   cmdUndo		 = std::make_shared<CommandUndo>();
	std::shared_ptr<CommandRedo>	   cmdRedo		 = std::make_shared<CommandRedo>();

	menu.Init(0, "",			  cmdDisplay);
	menu.Init(1, "Add",			  cmdAdd);
	menu.Init(2, "Insert",		  cmdInsert);
	menu.Init(3, "Overwrite",	  cmdOverwrite);
	menu.Init(4, "Erase",		  cmdRemove);
	menu.Init(5, "Change color",  cmdSetColor);
	menu.Init(6, "Toggle bold",	  cmdSetBold);
	menu.Init(7, "Undo",	  	  cmdUndo);
	menu.Init(8, "Redo",	  	  cmdRedo);

	menu.Run();

	return 0;
}