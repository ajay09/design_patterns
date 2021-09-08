/*
	Doesn't use dynamic allocation

	Lazy and thread safe
*/

#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <boost/lexical_cast.hpp>

class SingletonDatabase {
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
	
};

int SingletonDatabase::instance_count = 0;

/*
Checklist
	- make constructor private
	- delete copy constructor and copy assignment operator
	- define a static function that returns a reference to a static instance fo a local object of the class
*/