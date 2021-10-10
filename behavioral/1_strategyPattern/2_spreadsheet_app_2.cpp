/*
	SpreadSheet Appliation

	Users can enter data in rows and columns.

	Clients request us to provide the functionality of export the data
	in other file formats. e.g. in HTML format.

	Solution : We can provide the client to specify whether they wish to export the data
		       in csv or html format. This can be done in the Export() function itsef.

	Problem : Problem with this solution is : 
			  - We violated the OCP, by modifying the existing code.
			  	The code should be open for extension but closed for modification.
			  	We modified the signature of a method and this will break existing clients.

			  - We now have conditional statemens in our export function.
				And client would wish to export the data in other formats maybe pdf or xml or json
				And we would again have to modify the exisiting code and keep on adding new cases
				in the conditional. With time the complexity of code will increase.
				This approach also violates the OCP.


		Thus we need a different approach, so that we can add new file formats without modifying
		exisitin code.
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
	// Now the export takes an input of the output it has to generate
	void Export(int type) {
		std::ofstream out;
		switch (type) {
			case 0 : //csv
				out.open("data.csv");
				for (auto row : m_Sheet) {
					for (auto element : row) {
						out << element << ',';
					}
					out << "\n";
				}
				break;
			case 1:
				out.open("data.html");
				out << "<!DOCTYPE html>\n"
					<< "<html>\n"
					<< "<body>\n"
					<< "<h1>Exported</h1>\n";
				for (auto row : m_Sheet) {
					for (auto element : row) {
						out << element << ',';
					}
					out << "\n";
				}
				out << "</body>\n"
					<< "</html>\n";
				break;
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

	model.Export(1);

	return 0;
}














