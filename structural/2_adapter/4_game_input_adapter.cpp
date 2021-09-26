/*
	Flight Simulator

	Suppose now we wish to take input from the Accelerometer of the mobile.

	Assume that the Accelerometer class already exists and created by someone else.

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





// This is the Adaptee
///////////////////////////////////////////
///////////////////  Accelerometer.h
///////////////////////////////////////////
#include <random>
#include <iostream>

class Accelerometer {
	std::default_random_engine m_Engine{6789};
public:
	// return a value between [-10, 10] -10 indicates a left tilt, +10 indicates a right tilt.
	double GetHorizontalAxis() {
		std::uniform_int_distribution<> dist{-10, 10};
		auto value = dist(m_Engine);
		std::cout << "[Accelerometer] [Horizontal] " << value << std::endl;
		return value;
	}
	// similarly + for forward tilt and - for backward tilt.
	double GetVerticalAxis() {
		std::uniform_int_distribution<> dist{-10, 10};
		auto value = dist(m_Engine);
		std::cout << "[Accelerometer] [Vertical] " << value << std::endl;
		return value;
	}
};

/*
	We wish to take input from the Accelerometer class but
	it does not have the same interface that the Game (client) expects.

	The Game expects an input class to have the four methods, but accelerometer
	does not have these methods.

	Reimplementing or modifying the Accelerometer class may need huge amout of work
	or may not be possible in some cases. 
	So we use the Adapter pattern to enable this.

*/

// 1. Object Adapter (i.e. through composition)
///////////////////////////////////////////
///////////////////  AccAdapter.h
///////////////////////////////////////////
class Input;
class AccAdapter : public Input {
	Accelerometer m_Acc;
public:
	bool Up() {
		return m_Acc.GetVerticalAxis() > 0;
	}

	bool Down() {
		return m_Acc.GetVerticalAxis() < 0;
	}

	bool Left() {
		return m_Acc.GetHorizontalAxis() < 0;
	}

	bool Right() {
		return m_Acc.GetHorizontalAxis() > 0;
	}
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
	
	AccAdapter a;
	Game(&a);

	return 0;
}