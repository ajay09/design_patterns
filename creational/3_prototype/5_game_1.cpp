/*
	A 2D game.
	Different kind of vehicles move on the road.
	The player has to navigate through the traffic.
	As the player move we will randomly generate different kinds of vehicles
	so that the road looks busy. The player may not be able to avoid the traffic
	always and may collide with some vehicle. This would decrease the health
	of the player but he will continue riding the vehicle.

	We will spawn power ups and even health kits to restore player's health.

	We will create classes that will represent different kinds of vehicles that are moving
	on the road, e.g. Red Car, Green Car, Blue Car, Yellow Bus, Blue Bus
	Why not create a single class Car that may represent all the different cars?
	The reason is vehicles will have different kinds of animations, eg.
		- Animate how the vehicle move on the road.
		- when the player collides with the vehicle.
		  depending on the kind of vehicle the player collides with we will show
		  a different kind of animation.
		Thus we don't want to use a single class to represent all kinds of cars.
		- Differnt vehicles will move at different speeds depending on the kind of vehicle
		  that the player collides will damage to the player may very.
		- For larger vehicles like Trucks and Buses, they can move out of the way if the
		  player honks.
		- We will add some behavior to Red Cars. they can increase their speed for a short
		  while when the player is around these cars. Thus the player has to be extra careful.
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
	Animation(std::string &file);
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
Animation::Animation(std::string &file) {
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
	Vehicle(int speed, int hitPoints, std::string &name, std::string &animFile, Position &pos)
	 : m_Speed{speed}, m_HitPoints{hitPoints}, m_Name{name}, m_Position{pos} 
	 {
	 	m_pAnimation = new Animation[animFile];
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
	using Vehile::Vehile;   // Inherit Base's constructors.
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
	using Vehile::Vehile;   // Inherit Base's constructors.
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
			std::cout << "\tSpeed : " << GetSpeed() << "\n"
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
public:
	// If there is a space and the player honks then the bus moves out of the way.
	// To implement this we will use the random functionality.
	void Update() override {

	}
};