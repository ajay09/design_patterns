/*
	Enable clients to use new file formats to export the data
	without modifying the existing code.

	Thus we use Strategy Design Pattern.

	If we have an algo in our class that needs to change in future, or you have to add
	more variant in future then you take them out of the class.

	In our DataModel class we have an Export function that is being used to export the
	data in different formats. In one of the implementation we used conditional statements
	to support differnt formats. But that approach vioated the OCP and would make it difficult
	to add support for more formats in future.

	If we apply strategy desgin patter then we can consider each conditional statement as
	an algorithm and we can take them out of the Export function and put them in their own 
	classes. This way algos will be encapsulated and we can make them interchangeable
	by inheriting them from a common base class.



	Format *m_pFormat{};    inside the DataModel class is a dependency for DataModel as DataModel
							is dependent on a subclass of Format.
							And somehow we need an instance of one of the sub-classes of Format
							to initialize this pointer.

							- One why is the DataModel itself can create instance of the sub-class
							  of Format, but that would expose it to their implementation.

							- So that's why we will set the instance from outside.
							  And since Format is a dependency for DataModel, this is called
							  "Dependency Injection".

							- There are 2 ways of injecting the dependecy :
								1. Through the constructor
								2. Through a setter method

							- If we inject the dependecy through a constructor then we wouldn't be 
							  able to change it later, thus we should use the setter method.
*/



////////////////////////////////////////
//////////////		Format.h
////////////////////////////////////////
class DataModel;

class Format {
public:
	virtual void ExportData(DataModel *pModel) = 0;
	virtual ~Format() = default;
};

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
	// CSVFormat csv;
	/*
		We should not use CSVFormat instance here becuase then this class will get tightly 
		coupled with the CSVFormat class and this solution will not be a flexible solution.

		Since we are direcly using the concrete instance of a class and there could be a variation
		of the algo that this class implements, we are violating the Dependency Inversion Principle.

		DIP : states program to interface not implementation.
	*/
	Format *m_pFormat{}; // Thus Format is a dependency for DataModel
						 // Program to interface rather than implementation.
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
		if (m_pFormat)
			m_pFormat->ExportData(this);
	}

	const std::vector<std::vector<int>>& GetSheetData() const { return m_Sheet; }

	void SetFormat(Format *pFormat) {
		m_pFormat = pFormat;
	}
};



#include <stdexcept>
#include <sstream>

class CSVFormat : public Format {
	std::ofstream m_OStream{};
public:
	CSVFormat(const std::string &file) : m_OStream{file} {
		if (!m_OStream.is_open()) {
			std::stringstream ss;
			ss << "Could not open the file " << file << " for writing.";
			throw std::runtime_error{ss.str().c_str()};
		}
	}

	// pull based approach to get the data.
	void ExportData(DataModel *pModel) override {
		for (auto row : pModel->GetSheetData()) {
			for (auto element : row) {
				m_OStream << element << ',';
			}
			m_OStream << "\n";
		}
		std::cout << "File exported successfully.\n";
	}
};



class HtmlFormat : public Format {
	std::ofstream m_OStream{};
public:
	HtmlFormat(const std::string &file) : m_OStream{file} {
		if (!m_OStream.is_open()) {
			std::stringstream ss;
			ss << "Could not open the file " << file << " for writing.";
			throw std::runtime_error{ss.str().c_str()};
		}
	}

	// pull based approach to get the data.
	void ExportData(DataModel *pModel) override {
		m_OStream << "<!DOCTYPE html>\n"
				  << "<html>\n"
				  << "<body>\n"
				  << "<h1>Exported</h1>\n";
		for (auto row : pModel->GetSheetData()) {
			for (auto element : row) {
				m_OStream << element << ',';
			}
			m_OStream << "\n";
		}
		m_OStream << "</body>\n"
				  << "</html>\n";

		std::cout << "File exported successfully.\n";
	}
};










int main() {
	DataModel model{};

	// model.AddRow({1, 2, 3, 4});
	// model.AddRow({11, 12, 13, 14});

	model.Load();
	model.Display();
	// model.Save();

	CSVFormat csv{"records.csv"};

	model.SetFormat(&csv);
	model.Export();

	HtmlFormat html{"records.html"};

	model.SetFormat(&html);
	model.Export();

	return 0;
}




/*
								m_pFormat
     |     DataModel      |<>---------------------->|       Format         |
     ----------------------                         ------------------------
     |  Export()		  |                         | ExportData() 		   |
     ----------------------                         ------------------------
                                                              /_\
                                                               |
                                                               |
                    ___________________________________________|______________________
                    |                             |                                  |
                    |                             |                                  |
          |   CSVFormat		     |       |   HtmlFormat		    |                   ...
          ------------------------       ------------------------           
          | ExportData()		 |       | ExportData()			|           



	
		- DataModel can now work with different kinds of Format classes and we don't have to 
		  modify it even if we add new types of Format classes.

		- We can set the strategies at runtime dynamically.

		- Instead of using Inheritance we are using Composition, and since Composition is a
		  dynamic relationship we can set any of the Format classes at runtime inside the
		  DataModel

		- Thus we use strategy pattern as a replacement for conditional statements.

*/










