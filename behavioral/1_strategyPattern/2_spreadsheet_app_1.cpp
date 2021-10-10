/*
	SpreadSheet Appliation

	Users can enter data in rows and columns.

	Clients request us to provide the functionality of export the data
	in other file formats. e.g. in HTML format.
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
		// out will automatically close as the object goes out of scope.
	}

	// export the data in other formats. e.g. csv format
	void Export() {
		std::ofstream out{"data.csv"};
		for (auto row : m_Sheet) {
			for (auto element : row) {
				out << element << ',';
			}
			out << "\n";
		}
	}
};















int main() {
	DataModel model{};

	// model.AddRow({1, 2, 3, 4});
	// model.AddRow({11, 12, 13, 14});

	model.Load();
	model.Display();
	// model.Save();

	model.Export();

	return 0;
}














