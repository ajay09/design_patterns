/*
	Implement a Lamp

	- variable is required in the class to track the state because if we called SwitchOn twice in a row
	  then our lamp switches on twice which doesn't makes sense.

	Problem :
		- Suppose we have different kind of lamp, which can be on(white color), on(yellow color) or off
		  i.e. exhibit 3 states.
		  The first time user presses On it will show white color
		  The second time user presses On it will show yellow color

		  How do we integrate this change?
		  	- add one more enum state
		  	- add one more case statement.

		 We were able to manage this case. But with time the complexity can increase, then
		 it would become difficult to manage.

		 Thus we should use the State-Design Pattern


*/



////////////////////////////////////////////////////
////////////////////////////  Lamp.h
////////////////////////////////////////////////////
#include <iostream>

class Lamp {

	enum class State {OFF, ON};
	State m_State;

	const char *m_LampOn = 
R"(
         |
 \     _____     /
     /       \
    (         )
-   ( ))))))) )   -
     \ \   / /
      \|___|/
  /    |___|    \
       |___| 
       |___|
)";

	const char *m_LampOff = 
R"(
          
       _____      
     /       \
    (         )
    ( ))))))) )    
     \ \   / /
      \|___|/
       |___|     
       |___| 
       |___|
)";

public:
	// default state is off
	Lamp() : m_State{State::OFF} {}

	void SwitchOn() {
		switch (m_State) {
			case State::OFF:
				system("clear");
				std::cout << m_LampOn << std::endl;
				std::cout << "Turned On\n";
				m_State = State::ON;
				break;

			case State::ON:
				std::cout << "Lamp is already On\n";
				break;
		}
	}
	
	void SwitchOff() {
		switch (m_State) {
			case State::OFF:
				std::cout << "Lamp is already Off\n";
				break;

			case State::ON:
				system("clear");
				std::cout << m_LampOff << std::endl;
				std::cout << "Turned Off\n";
				m_State = State::OFF;
				break;
		}
	}
};




int main() {
	Lamp lamp;
	lamp.SwitchOn();
	getchar();
	lamp.SwitchOn();
	getchar();
	lamp.SwitchOff();
	getchar();
	lamp.SwitchOff();
	getchar();
	return 0;
}














