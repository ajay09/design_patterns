/*
	Now we will implement the Adapter pattern using the Class Adapter.
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

/*
	We change this class, instead of hardcoding the range of values generated
	by the GetHorizontalAxis()  and  GetVerticalAxis() functions we initialize 
	the range using a function.
*/
class Accelerometer {
	std::default_random_engine m_Engine{6789};
public:
	// return a value between [-10, 10] -10 indicates a left tilt, +10 indicates a right tilt.
	double GetHorizontalAxis() {
		auto init_values = Initialize();
		std::uniform_int_distribution<> dist{init_values.first, init_values.second};
		auto value = dist(m_Engine);
		std::cout << "[Accelerometer] [Horizontal] " << value << std::endl;
		return value;
	}
	// similarly + for forward tilt and - for backward tilt.
	double GetVerticalAxis() {
		auto init_values = Initialize();
		std::uniform_int_distribution<> dist{init_values.first, init_values.second};
		auto value = dist(m_Engine);
		std::cout << "[Accelerometer] [Vertical] " << value << std::endl;
		return value;
	}

	virtual std::pair<int, int> Initialize() {
		return {-10, 10};
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



	We can observe that for our Game Input we don't actually need the integer values
	from the GetHorizontalAxis()  and  GetVerticalAxis() of the Accelerometer class.
	We only need to know if the value is positive or negative.

	So when we create the Adapter for the accelerometer, we would like to customise
	these initializer values.
*/

// 2. Class Adapter (i.e. through inheritance)
///////////////////////////////////////////
///////////////////  AccAdapter.h
///////////////////////////////////////////
class Input;
// class AccAdapter : public Input, public Accelerometer {


/*
	Use of private inheritance.
	When you create an instance of  AccAdapter
	If you use public inheritance then the public methods of the Accelerometer
	class will be exposed and can be used by the clients.
		Try the following and see the exposed methods.
		AccAdapter a;
		a.

	If you don't want to expose them then you should use private inheritance.
*/
class AccAdapter : public Input, private Accelerometer {
public:
	bool Up() {
		return GetVerticalAxis() > 0;
	}

	bool Down() {
		return GetVerticalAxis() < 0;
	}

	bool Left() {
		return GetHorizontalAxis() < 0;
	}

	bool Right() {
		return GetHorizontalAxis() > 0;
	}

	// If we don't override this method, then it will simply use the
	// base class Initialize method and function just like the 4_game_input_adapter.cpp
	std::pair<int, int> Initialize() {
		return {-1, 1};
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