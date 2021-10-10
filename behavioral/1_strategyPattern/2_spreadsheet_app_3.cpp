/*
	Enable clients to use new file formats to export the data
	without modifying the existing code.
*/

////////////////////////////////////////
//////////////		DataModel.h
//////////////		A class to manage the data entered by the users.
///////////////////////////////////////
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class DataModel {
	std::vector<std::vector<int>> m_Sheet; // consider data is integer only.
public:
	void AddRow(std::vector<int> data) {
		m_Sheet.push_back(std::move(data));
	}

	void Display() {
		for (auto row : m_Sheet) {
			for (auto element : row) {
				std::cout << element << ' ';
			}
			std::cout << "\n";
		}
	}

	void Load() {
		m_Sheet.clear();
		std::ifstream in{"data.sheet"};

		if (!in.is_open()) {
			std::cout << "Could not open the file for reading\n";
			return;
		}

		std::string line{};
		while (std::getline(in, line)) {
			std::vector<int> row;
			std::istringstream istr{line};
			int element{};

			while (istr >> element) {
				row.push_back(element);
			}

			m_Sheet.push_back(std::move(row));
		}
	}
	
	void Save() {
		std::ofstream out{"data.sheet"};
		if (!out.is_open()) {
			std::cout << "Could not open the file for writing\n";
			return;
		}
		for (auto row : m_Sheet) {
			for (auto element : row) {
				out << element << ' ';
			}
			out << "\n";
		}
	}


	virtual void Export(); 
	
	virtual ~DataModel() = default;

	const std::vector<std::vector<int>>& GetSheetData() const { return m_Sheet; }
};


void DataModel::Export() {
	std::ofstream out{"data.csv"};
	for (auto row : m_Sheet) {
		for (auto element : row) {
			out << element << ',';
		}
		out << "\n";
	}
}



///////////////////////////////////
///////////////		HtmlDataModel.h
///////////////////////////////////
class HtmlDataModel : public DataModel {
public:
	void Export() override {
		std::ofstream out("data.html");

		out << "<!DOCTYPE html>\n"
			<< "<html>\n"
			<< "<body>\n"
			<< "<h1>Exported</h1>\n";
		for (auto row : GetSheetData()) {
			for (auto element : row) {
				out << element << ',';
			}
			out << "\n";
		}
		out << "</body>\n"
			<< "</html>\n";
	}
};













int main() {
	HtmlDataModel model{};
	/*
		Suppose we create an instance of HtmlDataModel, now the client can't export the data
		in another format if he wants to. He can only export in html.


		What if the client wants to export in different format?
		He simply can't. Client always must know which format he will use in future, which
		is not always possible. 
		
		Thus this approach is restrictive, because it relies on inheritance. HtmlDataModel class
		is tightly coupled with the DataModel class, at runtime it is not possible to change a 
		HtmlDataModel class instance to a different class to export the data in a different file
		format.

	*/

	// model.AddRow({1, 2, 3, 4});
	// model.AddRow({11, 12, 13, 14});

	model.Load();
	model.Display();
	// model.Save();

	model.Export();

	return 0;
}














