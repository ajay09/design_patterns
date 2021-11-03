/*
	Implement a Lamp

	- variable is required in the class to track the state because if we called SwitchOn twice in a row
	  then our lamp switches on twice which doesn't makes sense.
*/



////////////////////////////////////////////////////
////////////////////////////  Lamp.h
////////////////////////////////////////////////////
#include <iostream>

class Lamp {
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
	void SwitchOn() {
		system("clear");
		std::cout << m_LampOn << std::endl;
		std::cout << "Turned On\n";
	}
	void SwitchOff() {
		system("clear");
		std::cout << m_LampOff << std::endl;
		std::cout << "Turned Off\n";
	}
};




int main() {
	Lamp lamp;
	lamp.SwitchOn();
	getchar();
	lamp.SwitchOff();
	getchar();
	return 0;
}














