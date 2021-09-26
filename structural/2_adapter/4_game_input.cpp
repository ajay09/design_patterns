/*
	Flight Simulator

	A player can fly different kinds of planes.
	To control the plane, we map the input to some keys on the keyboard. To make
	the plane go up and down we map the keys to up and down arrow keys.
	Similarly for left and right direction, the input is mapped to left and right
	arrow keys.


	The player may also want to use a different kind of device to play the game.


	Thus we don't want to hardcode the game input to the keyboard and would like
	to have a design where the game can take input from any kind of controller.
*/

///////////////////////////////////////////
///////////////////  Input.h
///////////////////  Base class containing the interface for accepting input
///////////////////  from any kind of device.
///////////////////////////////////////////
class Input {
public:
	/*
		These methods don't necessarily map to the input from the keyboard
		but these are just abstractions of the different ways a player can 
		input to the game.
	*/
	virtual bool Up() = 0;
	virtual bool Down() = 0;
	virtual bool Left() = 0;
	virtual bool Right() = 0;

	virtual ~Input() = default;
};




///////////////////////////////////////////
///////////////////  Keyboard.h
///////////////////  A class to take input from the keyboard.
///////////////////  We return true/false randomly from the methods.(using a random generator)
///////////////////////////////////////////
#include <random>

class Keyboard : public Input {
	// a default random engine  with the seed value.
	std::default_random_engine m_Engine{1234};

	bool SimulateInput() {
		// we have to use a distribution class to use the engine to generate 
		// random boolean values.
		std::bernoulli_distribution dist{0.5};
		return dist(m_Engine);// invoke the function call operator on the distribution object.
	}
public:
	bool Up() {
		return SimulateInput();
	}

	bool Down() {
		return SimulateInput();
	}

	bool Left() {
		return SimulateInput();
	}

	bool Right() {
		return SimulateInput();
	}
};




#include <iostream>
#include <thread>

void Game(Input *pInput) {
	int count{5};
	while (count != 0) {
		std::cout << "=================================\n";
		if (pInput->Up()) {
			std::cout << "Pitch Up.\n";
		} else if (pInput->Down()) {
			std::cout << "Pitch Down.\n";
		} else {
			std::cout << "Plane is level.\n";
		}

		if (pInput->Left()) {
			std::cout << "Plane is turning Left\n";
		} else if (pInput->Right()) {
			std::cout << "Plane is turning Right\n";
		} else {
			std::cout << "Plane is flying straight.\n";
		}

		std::cout << std::endl;
		using namespace std;
		std::this_thread::sleep_for(1s);
		--count;
	}
}


int main() {
	
	Keyboard k;
	Game(&k);

	return 0;
}