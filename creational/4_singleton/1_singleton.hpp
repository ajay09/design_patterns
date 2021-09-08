#pragma once
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

class SingletonDatabase {
	SingletonDatabase() {
		std::cout << "Initializing database" << std::endl;

		std::ifstream ifs("capitals.txt");

		std::string s, s2;
		while (std::getline(ifs, s)) {
			getline(ifs, s2);
			int pop = boost::lexical_Cast<int>(s2);
			capitals[s] = pop;
		}
	}

	std::map<std::string, int> capitals;

	static SingletonDatabase *instance;
public:
	SingletonDatabase(const SingletonDatabase &) = delete;
	SingletonDatabase& operator=(const SingletonDatabase &) = delete;

	static SingletonDatabase* getInstance() {
		if (!instance) {
			instance = new SingletonDatabase;
		}
		return instance;
	}
};

/*
Problem with this :
 - Thread safety : 2 threads can call the line 28 simultaneously and create 2 instances
 - How do we delete Singleton object here after it is constructed.
 */