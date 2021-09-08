// Single Resposibility Principle
/*
	A class should only have a single responsibility.
	Sometimes when we edit code we end up adding functionality to a class that is not its responsibility.
	And maybe we need to create a seperate class to support the new functionality.
*/

#include <string>
#include <vector>
#include <fstream>

struct Journal {
	std::string title;
	std::vector<std::string> entries;

	explicit Journal(const std::string &title) : title{title} {}

	// Adding a new entry to the jornal is the responsibility of the Journal class
	// Journal must provide ability to add a new entry
	void add(const std::string &entry) {
		entries.push_back(entry);
	}

	/*
	// Saving a Jornal should not be a responsibility of the Journal class
	// Problem is whenever you decide you wish to save things differently
	// you'll have to modify the Jornal class and recompile it.
	void save(const std::string &filename) {
		std::ofstream ofs(filename);
		for (auto &s : entries)
			ofs << s << std::endl;
	}
	*/
};

// We can have a separate component to save the journal
struct PersistanceManager {
	static void save(const Journal &j, const std::string &filename) {
		std::ofstream ofs(filename);
		for (auto &s : j.entries)
			ofs << s << std::endl;
	}
};

int main() {
	return 0;
}

