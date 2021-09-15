/*
	Game_1 is working fine. But we have 1 issue:
	If we add a new vehicle in  this game then to create their instances

	This can be done in the Run() method.
	 TO create instances we would have to modify
	 m_Vehicles.push_back(new RedCar{30, 15, "RedCar", "red.anim", {50, 50}});

	 The GameManager is tightly coupled with the Vicles child classes.
	 So how do we remove this coupling of game management with specific class?
	 The answer is   "Parameterised Factory Method."
	We can implement it as a class or a function. And in this case, the Factory Method
	only needs to create the instance, it doesn't need to store any state. SO we can 
	easily create a function as a Factory Method.

	This will remove the dependency of the GameManager on the Vehicle classes.

*/

/////////////////////////////////////////////
//////////////////////  Animation.h
//////////////////////  It will load animation for different vehicles. Each vehicle
//////////////////////  will have its own instance of this animation and when the 
//////////////////////  instance of the vehicle is created the corresponding animation
//////////////////////  will be loaded from a file.
/////////////////////////////////////////////
#include <string>

class Animation {
	std::string m_AnimationData;
public:
	Animation() = default;
	Animation(const std::string &file);
	const std::string& GetAnimationData() const {
		return m_AnimationData;
	}
	void SetAnimationData(const std::string &animationData) {
		m_AnimationData = animationData;
	}
};

/////////////////////////////////////////////
//////////////////////  Animation.cpp
/////////////////////////////////////////////
#include <thread>
#include <iostream>
Animation::Animation(const std::string &file) {
	using namespace std;
	std::cout << "[Animation Loading : " << file << " ";
	for (int i = 0; i < 10; ++i) {
		std::cout << ".";
		std::this_thread::sleep_for(200ms);
	}
	std::cout << std::endl;

	m_AnimationData = "^^^^^^";
}



/////////////////////////////////////////////
//////////////////////  Vehicle.h
/////////////////////////////////////////////
struct Position {
	int x;
	int y;
	friend std::ostream& operator<<(std::ostream& os, const Position &p) {
		return os << "(" << p.x << "," << p.y << ")";
	}
};
class Vehicle {
	int m_Speed;
	int m_HitPoints;
	std::string m_Name;
	Animation *m_pAnimation;
	Position m_Position;
public:
	Vehicle(int speed, int hitPoints, const std::string &name, const std::string &animFile, const Position &pos)
	 : m_Speed{speed}, m_HitPoints{hitPoints}, m_Name{name}, m_Position{pos} 
	 {
	 	m_pAnimation = new Animation(animFile);
	 }

	virtual ~Vehicle() { delete m_pAnimation; }

	int GetSpeed() const { return m_Speed; }
	Position GetPosition() const { return m_Position; }
	const std::string& GetName() const { return m_Name; }
	int GetHitPoints() const { return m_HitPoints; }
	const std::string& GetAnimation() const { return m_pAnimation->GetAnimationData(); }
	void SetSpeed(int speed) { m_Speed = speed; };
	void SetPosition(Position &pos) { m_Position = pos; }
	void SetName(const std::string &name) { m_Name = name; }
	void SetHitPoints(int points) { m_HitPoints = points; }
	void SetAnimationData(const std::string &animData) {
		m_pAnimation->SetAnimationData(animData);
	}

	// It will be invoked by the game engine for all the vehicles.
	// The game objects will have to perform their tasks, eg. taking input or animating objects.
	// But in our case we will only print the details of the object
	virtual void Update() = 0;
};




/////////////////////////////////////////////
//////////////////////  GreenCar.h
/////////////////////////////////////////////
class GreenCar : public Vehicle {
	// Inheriting constructor
	// In C++11, a form of 'constructor inheritance' has been introduced where you can 
	// instruct the compiler to generate a set of constructors for you that take the same 
	// arguments as the constructors from the base class and that just forward those 
	// arguments to the base class.
	// The scope will be same as that in the Base class
	using Vehicle::Vehicle;   // Inherit Base's constructors.
    // Equivalent to:
    // GreenCar(int speed, int hitPoints, std::string &name, std::string &animFile, Position &pos) : 
    //   Vehicle(int speed, int hitPoints, std::string &name, std::string &animFile, Position &pos) {}
	
public:
	void Update() override {
		std::cout << "[" << GetName() << "]\n"
				  << "\tAnimation : " << GetAnimation() << "\n"
				  << "\tSpeed : " << GetSpeed() << "\n"
				  << "\tHitPoints : " << GetHitPoints() << "\n"
				  << "\tPosition : " << GetPosition() << "\n";
	}
};


/////////////////////////////////////////////
//////////////////////  RedCar.h
/////////////////////////////////////////////
#include <random>

class RedCar : public Vehicle {
	// Inheriting constructor
	using Vehicle::Vehicle;   // Inherit Base's constructors.
	float m_SpeedFactor{1.5}; // the factor by which a red car can increase its speed.

	// Since we have to modify the speed of the red car randomly, so we will use random
	// header file from C++ std library.
	// First we will define the random engine. Initialize it with a seed value.
	std::default_random_engine m_Engine{100};
	// then use Bernoulli Distribution class to get random boolean values.
	std::bernoulli_distribution m_Dist{0.5}; // distribution parameter : decide the probability
											 // of generating true values. 0.5 => 50% chance of generating true.
public:
	void SetSpeedFactor(float factor) {
		m_SpeedFactor = factor;
	}

	void Update() override {
		std::cout << "[" << GetName() << "]\n"
				  << "\tAnimation : " << GetAnimation() << "\n";
		// we are invoking the function call operator of the distribution class and it will
		// return random booleans
		if (m_Dist(m_Engine)) {
			std::cout << "\tIncrease the speen temporarily : " << GetSpeed() * m_SpeedFactor << "\n";
		}
		else {
			std::cout << "\tSpeed : " << GetSpeed() << "\n";
		}	
		std::cout << "\tHitPoints : " << GetHitPoints() << "\n"
				  << "\tPosition : " << GetPosition() << "\n";
	}
};



/////////////////////////////////////////////
//////////////////////  BlueBus.h
/////////////////////////////////////////////
class BlueBus : public Vehicle {
	using Vehicle::Vehicle;
	std::default_random_engine m_Engine{500};
	std::bernoulli_distribution m_Dist{0.5};
public:
	// If there is a space and the player honks then the bus moves out of the way.
	// To implement this we will use the random functionality. i.e. move bus out of the way randomly
	// This is how we implement honking by the player.
	void Update() override {
				std::cout << "[" << GetName() << "]\n"
				  << "\tAnimation : " << GetAnimation() << "\n";
		if (m_Dist(m_Engine)) {
			std::cout << "\tMoving out of the way\n";
		}
		std::cout << "\tSpeed : " << GetSpeed() << "\n";
		std::cout << "\tHitPoints : " << GetHitPoints() << "\n"
				  << "\tPosition : " << GetPosition() << "\n";
	}
};



/////////////////////////////////////////////
//////////////////////  YellowBus.h
/////////////////////////////////////////////
class YellowBus : public Vehicle {
	using Vehicle::Vehicle;
	std::default_random_engine m_Engine{500};
	std::bernoulli_distribution m_Dist{0.5};
public:
	void Update() override {
				std::cout << "[" << GetName() << "]\n"
				  << "\tAnimation : " << GetAnimation() << "\n";
		if (m_Dist(m_Engine)) {
			std::cout << "\tMoving out of the way\n";
		}
		std::cout << "\tSpeed : " << GetSpeed() << "\n";
		std::cout << "\tHitPoints : " << GetHitPoints() << "\n"
				  << "\tPosition : " << GetPosition() << "\n";
	}
};



Vehicle* Create(
	const std::string &type,
	int speed, 
	int hitPoints, 
	const std::string &name, 
	const std::string &animFile, 
	const Position &pos);
// Game manager has the game loop that will invoke the update methods of all the vehicles.
/////////////////////////////////////////////
//////////////////////  GameManager
/////////////////////////////////////////////
#include <vector>

class GameManager {
	std::vector<Vehicle*> m_Vehicles{};
public:
	void Run() {
		m_Vehicles.push_back(Create("redcar", 30, 10, "RedCar", "red.anim", {0, 0}));
		m_Vehicles.push_back(Create("greencar", 30, 15, "GreenCar", "green.anim", {100, 0}));
		m_Vehicles.push_back(Create("yellowbus", 25, 20, "YellowBus", "yellow.anim", {100, 200}));
		m_Vehicles.push_back(Create("bluebus", 25, 25, "BlueBus", "blue.anim", {200, 200}));

		int count{5};
		using namespace std;
		while (count != 0) {
			std::this_thread::sleep_for(1s);
			system("cls");
			for (auto vehicle : m_Vehicles)
				vehicle->Update();
			if (count == 2) {
				m_Vehicles.push_back(Create("redcar", 30, 15, "RedCar", "red.anim", {50, 50}));
			}
			if (count ==3) {
				m_Vehicles.push_back(Create("yellowbus", 20, 20, "YellowBus", "yellow.anim", {150, 250}));
			}
			count--;
		}
	}

	~GameManager() {
		for (auto &v : m_Vehicles)
			delete v;
	}
};




// Factory Method
Vehicle* Create(
	const std::string &type,
	int speed, 
	int hitPoints, 
	const std::string &name, 
	const std::string &animFile, 
	const Position &pos) 
{
	if (type == "redcar") {
		return new RedCar{speed, hitPoints, name, animFile, pos};
	} else if (type == "greencar") {
		return new GreenCar{speed, hitPoints, name, animFile, pos};
	} else if (type == "yellowbus") {
		return new YellowBus{speed, hitPoints, name, animFile, pos};
	} else if (type == "bluebus") {
		return new BlueBus{speed, hitPoints, name, animFile, pos};
	}

	return nullptr;
}



int main() {
	GameManager game;
	game.Run();
	return 0;
}


/*
	
	Use of Prototype Design Pattern : 
		Now when every time a new instance of the vehicle is created during the gameplay, it
		will cause a lag because the animation has to be loaded from a file. To avoid the lag,
		we can try implementing the Prototype Design Pattern.

	So instead of creating a new instance from the scratch, we will create a copy of the existing one.
	

*/