/*
	Implement Singleton Behavior of Clock class
	without using Singleton Pattern.

	Even if multiple instances of the clock class are created there is no point
	in creating multiple instances.

	Singleton :                               ||  Monostate : 
	- enforces singularity through structure  ||  - enforces singularity through behavior.
	- Only one instance can exist			  ||  - class may or may not be instantiated.
	- Support lazy instantiation 			  ||  - no support.
	- Can support inheritance & polymorphism  ||  - static methods can't be overridden.
 	
*/

// #pragma once
#include <string>
class Clock {
	static int m_Hour;
	static int m_Minute;
	static int m_Second;

	static void CurrentTime(); // private because this will be internally called from other functions.
	Clock(); // prevent user from creating instance.
public:
	// removed const because GetHour although a getter method was modifying the state.
	static int GetHour();
	static int GetMinute();
	static int GetSecond();

	static std::string GetTimeString();
};

int Clock::m_Hour;
int Clock::m_Minute;
int Clock::m_Second;


// clock.cpp
#include <ctime>
#include <sstream>

void Clock::CurrentTime() {
	time_t raw_time;
	time(&raw_time);
	tm *local_time = localtime(&raw_time);
	m_Hour	 =	local_time->tm_hour;
	m_Minute =	local_time->tm_min;
	m_Second =	local_time->tm_sec;
}

Clock::Clock(){}


int Clock::GetHour() {
	CurrentTime();
	return m_Hour;
}

int Clock::GetMinute() {
	CurrentTime();
	return m_Minute;
}

int Clock::GetSecond() {
	CurrentTime();
	return m_Second;
}

std::string Clock::GetTimeString() {
	CurrentTime();
	std::stringstream oss;
	oss << m_Hour << ":" << m_Minute << ":" << m_Second;
	return oss.str();
}



// client.cpp
#include <iostream>

int main() {
	std::cout << Clock::GetTimeString() << std::endl;
	return 0;
}
