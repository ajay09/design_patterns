#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

class Database {
public:
	virtual int get_population(const std::string &name) = 0;
};

class SingletonDatabase : public Database{
	SingletonDatabase() {
		std::cout << "Initializing database" << std::endl;

		std::ifstream ifs("capitals.txt");

		std::string s, s2;
		while (std::getline(ifs, s)) {
			getline(ifs, s2);
			int pop = boost::lexical_cast<int>(s2);
			capitals[s] = pop;
		}
		instance_count++;
	}

	std::map<std::string, int> capitals;
public:
	// for testing
	static int instance_count;
	SingletonDatabase(const SingletonDatabase &) = delete;
	SingletonDatabase& operator=(const SingletonDatabase &) = delete;

	static SingletonDatabase& get() {
		static SingletonDatabase sdb; // this invocation will only happen once
									  // this is also thread safe!
		return sdb;
	}
	
	int get_population(const std::string &name) override {
		return capitals[name];
	}
};

int SingletonDatabase::instance_count = 0;


class DummyDatabase : public Database {
	std::map<std::string, int> capitals;
public:
	DummyDatabase() {
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
		capitals["gamma"] = 3;
	}
	int get_population(const std::string &name) override {
		return capitals[name];
	}
};

// Returns the total population for a particular selection of cities.
struct SingletonRecordFinder {
	int total_population(std::vector<std::string> &names) {
		int result = 0;
		for (auto &name : names) {
			result += SingletonDatabase::get().get_population(name);
		}
		return result;
	}
};

struct ConfigurableRecordFinder {
	explicit ConfigurableRecordFinder(Database &db) : db{db} {}

	int total_population(const std::vector<std::string> &names) {
		int result = 0;
		for (auto &name : names) {
			result += db.get_population(name);
		}
		return result;
	}

	Database &db;
};