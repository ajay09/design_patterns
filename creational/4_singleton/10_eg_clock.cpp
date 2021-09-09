/*
	We will implement the singular behavior of the Class
	without using the Singleton Pattern.
*/

// clock.h
// This will represent the Realtime clock of the system.

// #pragma once
#include <string>
class Clock {
	mutable int m_Hour;
	mutable int m_Minute;
	mutable int m_Second;

	void CurrentTime() const; // private because this will be internally called from other functions.
public:
	Clock();
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;

	std::string GetTimeString() const;
};



// clock.cpp
#include <ctime>
#include <sstream>

void Clock::CurrentTime() const {
	time_t raw_time;
	time(&raw_time);
	tm *local_time = localtime(&raw_time);
	m_Hour	 =	local_time->tm_hour;
	m_Minute =	local_time->tm_min;
	m_Second =	local_time->tm_sec;
}

Clock::Clock(){}


int Clock::GetHour() const {
	CurrentTime();
	return m_Hour;
}

int Clock::GetMinute() const {
	CurrentTime();
	return m_Minute;
}

int Clock::GetSecond() const {
	CurrentTime();
	return m_Second;
}

std::string Clock::GetTimeString() const {
	CurrentTime();
	std::stringstream oss;
	oss << m_Hour << ":" << m_Minute << ":" << m_Second;
	return oss.str();
}



// client.cpp
#include <iostream>

int main() {
	Clock clk;
	std::cout << clk.GetTimeString() << std::endl;
	return 0;
}

/*
	Even if we create multiple instances of Clock
	all the instances will first synchroise their time with the system clock
	and there is only one system clock thus will always give the similar results.

	Thus we don't need multiple instance of the Clock to exist thus we can 
	implement Clock as a Singleton Class. But then we will have to create
	static methods and members.

	There is another way of making it singleton : using Monostate pattern.
*/