/*
	Use Command Pattern to create Macro.

	A Macros is a collection of commands.

	DataList contains integer data like a spreadsheet.
	We will use the Menu class to maipulate data of the DataList class.




   Invoker
---------------      m_OptionaTable      ---------------     m_Macro
|	  Menu    |------------------------->|	 Command   |<-------------------------------;
---------------                          ---------------						        |
											   /_\									    |
											    |										|
									   _________|_______________________________________|
									   |                       |						|
                                       |	                   |						|
---------------	  m_pList        ---------------		  ---------------			---------------
|  DataList   |<-----------------|     Sum     |		  |  Smallest   |			|    Macro    |
---------------		             ---------------		  ---------------			---------------
   Receiver


		- Sum, Smallest and Macro are Command classes                  =>  Command Design Pattern

		- Macro Command class is a composite because using it we can   =>  Composite Design Pattern
		  recursively compose different kinds of commands. 
		  A Macro can even compose another macro.
*/


#include <iostream>
// This will pause the program and prompt the user for input.
void Message(const std::string &text) {
	std::cout << "\n----------- " << text << " -----------\n";
	system(R"(read -p "Press enter to continue!")");
	system("clear");
}



///////////////////////////////////////
////////////////// Datalist.h
///////////////////////////////////////
#include <vector>
class DataList {
	std::vector<int> m_Data;
public:
	void Add(int data) {
		m_Data.push_back(data);
	}

	void Remove(size_t index) {
		if (index >= m_Data.size()) return;

		m_Data.erase(begin(m_Data) + index);
	}
	
	const std::vector<int>& GetData() const {
		return m_Data;
	}
};



/////////////////////////////////////////////
////////////////////////  	Command.h
/////////////////////////////////////////////
class Command {
public:
	virtual void Execute() = 0;
	virtual ~Command() = default;
};

/*
 * Add
 * Remove
 * Display
 * Largest
 * Smallest
 * Sort
 * Sum
 * Average
 */

#include <iostream>

/////////////////////////////////////////////
////////////////////////  	CommandAdd.h
/////////////////////////////////////////////
#include <random>
class CommandAdd : public Command {
	DataList *m_pDataList;
public:
	CommandAdd(DataList *pList) : m_pDataList{pList} {}

	void Execute() override {
		std::default_random_engine engine{std::random_device{}()};
		std::uniform_int_distribution<> dist{0, 100};
		m_pDataList->Add(dist(engine));
	}
};

/////////////////////////////////////////////
////////////////////////  	CommandRemove.h
/////////////////////////////////////////////
class CommandRemove : public Command {
	DataList *m_pDataList;
public:
	CommandRemove(DataList *pList) : m_pDataList{pList} {}

	void Execute() override {
		size_t index;
		std::cout << "Remove at index? ";
		std::cin >> index;
		m_pDataList->Remove(index);
	}
};

/////////////////////////////////////////////
////////////////////////  	CommandDisplay.h
/////////////////////////////////////////////
class CommandDisplay : public Command {
	DataList *m_pDataList;
public:
	CommandDisplay(DataList *pList) : m_pDataList{pList} {}

	void Execute() override {
		for (auto item : m_pDataList->GetData()) {
			std::cout << item << ", ";
		}

		std::cout << std::endl;
	}
};

/////////////////////////////////////////////
////////////////////////  	CommandLargest.h
/////////////////////////////////////////////
class CommandLargest : public Command {
	DataList *m_pDataList;
public:
	CommandLargest(DataList *pList) : m_pDataList{pList} {}

	void Execute() override {
		int largest = INT_MIN;
		
		for (auto item : m_pDataList->GetData()) {
			if (largest < item)
				largest = item;
		}

		std::cout << "largest number is : " << largest << std::endl;
	}
};

/////////////////////////////////////////////
////////////////////////  	CommandSmallest.h
/////////////////////////////////////////////
class CommandSmallest : public Command {
	DataList *m_pDataList;
public:
	CommandSmallest(DataList *pList) : m_pDataList{pList} {}

	void Execute() override {
		int smallest = INT_MAX;
		
		for (auto item : m_pDataList->GetData()) {
			if (smallest > item)
				smallest = item;
		}

		std::cout << "smallest number is : " << smallest << std::endl;
	}
};

/////////////////////////////////////////////
////////////////////////  	CommandSort.h
/////////////////////////////////////////////
class CommandSort : public Command {
	DataList *m_pDataList;
public:
	CommandSort(DataList *pList) : m_pDataList{pList} {}

	void Execute() override {
		auto sortedData = m_pDataList->GetData(); // this will create a copy of the vector by invoking the copy constructor.
		std::sort(begin(sortedData), end(sortedData));
		std::cout << "Sorted Data : ";
		for (auto item : sortedData) {
			std::cout << item << ", ";
		}
		std::cout << std::endl;
	}
};

/////////////////////////////////////////////
////////////////////////  	CommandSum.h
/////////////////////////////////////////////
class CommandSum : public Command {
	DataList *m_pDataList;
public:
	CommandSum(DataList *pList) : m_pDataList{pList} {}

	void Execute() override {
		std::cout << "Sum : " << accumulate(begin(m_pDataList->GetData()), end(m_pDataList->GetData()), 0)
				  << std::endl;
	}
};

/////////////////////////////////////////////
////////////////////////  	CommandAverage.h
/////////////////////////////////////////////
class CommandAverage : public Command {
	DataList *m_pDataList;
public:
	CommandAverage(DataList *pList) : m_pDataList{pList} {}

	void Execute() override {
		if (m_pDataList->GetData().empty())
			return;
		auto sum = accumulate(begin(m_pDataList->GetData()), end(m_pDataList->GetData()), 0);
		
		std::cout << "Average : " <<  sum / m_pDataList->GetData().size() << std::endl;
	}
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
			Message("Operation completed.");
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





/////////////////////////////////////
////////////////////  Macro.h
/////////////////////////////////////
#include <list>

class Macro : public Command {
	using Cmd = std::shared_ptr<Command>;
	std::list<Cmd> m_Macro;
public:
	void Add(Cmd pCmd) {
		m_Macro.push_back(pCmd);
	}

	void Execute() {
		for (auto item : m_Macro) {
			item->Execute();
		}
	}
};




/*
 * Add
 * Remove
 * Display
 * Largest
 * Smallest
 * Sort
 * Sum
 * Average
 */

int main() {
	DataList data;
	Menu menu;

	auto Display 	=   std::make_shared<CommandDisplay>(&data);
	auto Add 		=   std::make_shared<CommandAdd>(&data);
	auto Remove 	=   std::make_shared<CommandRemove>(&data);
	auto Largest 	=   std::make_shared<CommandLargest>(&data);
	auto Smallest 	=   std::make_shared<CommandSmallest>(&data);
	auto Sort 		=   std::make_shared<CommandSort>(&data);
	auto Sum 		=   std::make_shared<CommandSum>(&data);
	auto Average 	=   std::make_shared<CommandAverage>(&data);


	auto macro  	=   std::make_shared<Macro>();
	
	macro->Add(Average);
	macro->Add(Sum);
	macro->Add(Largest);
	macro->Add(Smallest);


	menu.Init(0, "Display",	 Display );
	menu.Init(1, "Add",		 Add );
	menu.Init(2, "Remove",	 Remove );
	menu.Init(3, "Largest",	 Largest );
	menu.Init(4, "Smallest", Smallest );
	menu.Init(5, "Sort",	 Sort );
	menu.Init(6, "Sum",		 Sum );
	menu.Init(7, "Average",	 Average );
	menu.Init(8, "Macro",	 macro );

	menu.Run();

	return 0;
}



