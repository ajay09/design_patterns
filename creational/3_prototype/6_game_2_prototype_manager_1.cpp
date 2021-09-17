/*
	The Car and Bus Classes act as prototypes.

	But in the Factory we are not utilizing it fully, as we are creating each object 
	from scratch. Instead of creating the instance from scratch for all vehicle types,
	we can clone an existing instance.

	So when the game starts we will create just one instance of car and bus. And when the
	game needs a new instance of either of these two classes, we can clone the existing
	instance. So we have to store the instances and create their prototypes.
						||
					    \/
	This can be managed in a separate class  =>  the Prototype Manager class.
	It manages the prototypes that the clients can clone and use.
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
#include <memory>

class Vehicle;
using VehiclePtr = std::shared_ptr<Vehicle>;
using AnimationPtr = std::shared_ptr<Animation>;


class Vehicle {
	int m_Speed;
	int m_HitPoints;
	std::string m_Name;
	AnimationPtr m_pAnimation;
	Position m_Position;
	std::string m_Color;
public:
	Vehicle() {
		m_pAnimation = std::make_shared<Animation>();
	}
	Vehicle(int speed, int hitPoints, const std::string &name, const std::string &animFile, const Position &pos, const std::string &color)
	 : m_Speed{speed}, m_HitPoints{hitPoints}, m_Name{name}, m_Position{pos}, m_Color{color} 
	 {
	 	m_pAnimation = std::make_shared<Animation>(animFile);
	 }

	 // copy constructor
	Vehicle(const Vehicle &other) : 
		m_Speed{other.m_Speed}, 
		m_HitPoints{other.m_HitPoints},
		m_Name{other.m_Name}, 
		m_Position{other.m_Position},
		m_Color{other.m_Color}
	{
		m_pAnimation = std::make_shared<Animation>();
		m_pAnimation->SetAnimationData(other.GetAnimation());
	}

	// copy assignment operator
	Vehicle& operator=(const Vehicle &other) {
		if (this != &other) {
			m_Speed = other.m_Speed;
			m_HitPoints = other.m_HitPoints;
			m_Name = other.m_Name;
			m_Position = other.m_Position;
			m_Color = other.m_Color;
			m_pAnimation = std::make_shared<Animation>();
			m_pAnimation->SetAnimationData(other.GetAnimation());
		}
		return *this;
	}

	// move constructor
	Vehicle(Vehicle &&other) noexcept : 
		m_Speed{other.m_Speed}, 
		m_HitPoints{other.m_HitPoints},
		m_Name{std::move(other.m_Name)},
		m_Position{other.m_Position},
		m_Color{std::move(other.m_Color)}
	{
		m_pAnimation = std::move(other.m_pAnimation);
		
		other.m_Speed = 0;
		other.m_HitPoints = 0;
		other.m_Name.clear();
		other.m_Position = {0, 0};
		other.m_pAnimation = nullptr;
	}

	// move assignment operator
	Vehicle& operator=(Vehicle &&other) noexcept {
		if (this != &other) {
			m_Speed = other.m_Speed;
			m_HitPoints = other.m_HitPoints;
			m_Name = other.m_Name;
			m_Position = other.m_Position;
			m_Color = other.m_Color;
			m_pAnimation = std::move(other.m_pAnimation);

			other.m_Speed = 0;
			other.m_HitPoints = 0;
			other.m_Name.clear();
			other.m_Color.clear();
			other.m_Position = {0, 0};
			other.m_pAnimation = nullptr;
		}
		return *this;
	}


	virtual ~Vehicle() { }

	int GetSpeed() const { return m_Speed; }
	Position GetPosition() const { return m_Position; }
	const std::string& GetName() const { return m_Name; }
	int GetHitPoints() const { return m_HitPoints; }
	const std::string& GetAnimation() const { return m_pAnimation->GetAnimationData(); }
	void SetSpeed(int speed) { m_Speed = speed; };
	void SetPosition(const Position &pos) { m_Position = pos; }
	void SetName(const std::string &name) { m_Name = name; }
	void SetHitPoints(int points) { m_HitPoints = points; }
	void SetAnimationData(const std::string &animData) {
		m_pAnimation->SetAnimationData(animData);
	}
	void SetColor(const std::string &color) {
		m_Color = color;
	}
	const std::string& GetColor() const { return m_Color; }

	// It will be invoked by the game engine for all the vehicles.
	// The game objects will have to perform their tasks, eg. taking input or animating objects.
	// But in our case we will only print the details of the object
	virtual void Update() = 0;

	virtual VehiclePtr Clone() = 0;
};



/////////////////////////////////////////////
//////////////////////  Car.h
/////////////////////////////////////////////
#include <random>

class Car : public Vehicle {
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
		std::cout << "[" << GetColor() << "]\n"
				  << "\tAnimation : " << GetAnimation() << "\n";
		// we are invoking the function call operator of the distribution class and it will
		// return random booleans
		if (GetColor() == "Red" && m_Dist(m_Engine)) {
			std::cout << "\tIncrease the speen temporarily : " << GetSpeed() * m_SpeedFactor << "\n";
		}
		else {
			std::cout << "\tSpeed : " << GetSpeed() << "\n";
		}	
		std::cout << "\tHitPoints : " << GetHitPoints() << "\n"
				  << "\tPosition : " << GetPosition() << "\n";
	}

	VehiclePtr Clone() override {
		std::cout << "Cloning->" << GetName() << "\n";
		return std::make_shared<Car>(*this);
	}
};



/////////////////////////////////////////////
//////////////////////  Bus.h
/////////////////////////////////////////////
class Bus : public Vehicle {
	using Vehicle::Vehicle;
	std::default_random_engine m_Engine{500};
	std::bernoulli_distribution m_Dist{0.5};
public:
	void Update() override {
				std::cout << "[" << GetColor() << "]\n"
				  << "\tAnimation : " << GetAnimation() << "\n";
		if (m_Dist(m_Engine)) {
			std::cout << "\tMoving out of the way\n";
		}
		std::cout << "\tSpeed : " << GetSpeed() << "\n";
		std::cout << "\tHitPoints : " << GetHitPoints() << "\n"
				  << "\tPosition : " << GetPosition() << "\n";
	}

	VehiclePtr Clone() override {
		std::cout << "Cloning->" << GetName() << "\n";
		return std::make_shared<Bus>(*this);
	}
};



// Prototype Manager class
/////////////////////////////////////////////
//////////////////////  VehiclePrototype.h
//////////////////////  This will store all the prototypes of the Vehicles
//////////////////////  and create a copy whenever a new instance is required.
//////////////////////
////////////////////// This class should have only one instance.
////////////////////// Anyway if the client creates multiple instances, all the 
////////////////////// instances will share the same state.
/////////////////////////////////////////////
#include <unordered_map>
#include <vector>

class VehiclePrototype {
	static std::unordered_map<std::string, VehiclePtr> m_Prototypes;
	VehiclePrototype() = default;
public:
	// This function will just return a vector of strings representing the type of prototype
	static std::vector<std::string> GetKeys();
	static void RegisterPrototype(const std::string &key, VehiclePtr prototype);
	static VehiclePtr DeregisterPrototype(const std::string &key);
	static VehiclePtr GetPrototype(const std::string &key);
};


std::unordered_map<std::string, VehiclePtr> VehiclePrototype::m_Prototypes;

std::vector<std::string> VehiclePrototype::GetKeys() {
	std::vector<std::string> keys;
	keys.reserve(m_Prototypes.size());
	for (const auto &entry : m_Prototypes) {
		keys.push_back(entry.first);
	}
	return keys;
}

void VehiclePrototype::RegisterPrototype(const std::string &key, VehiclePtr prototype) {
	if (m_Prototypes.find(key) == end(m_Prototypes)) {
		m_Prototypes[key] = prototype;
	} else {
		std::cout << "Key already exists\n";
	}
}

VehiclePtr VehiclePrototype::DeregisterPrototype(const std::string &key) {
	if (m_Prototypes.find(key) != end(m_Prototypes)) {
		auto vehicle = m_Prototypes[key];
		m_Prototypes.erase(key);
		return vehicle;
	}
	return nullptr;
}

VehiclePtr VehiclePrototype::GetPrototype(const std::string &key) {
	if (m_Prototypes.find(key) != end(m_Prototypes)) {
		return m_Prototypes[key]->Clone();
	}
	std::cout << key << " is not registered with Prototype Manager.\n";
	return nullptr;
}




// Game manager has the game loop that will invoke the update methods of all the vehicles.
/////////////////////////////////////////////
//////////////////////  GameManager
/////////////////////////////////////////////
#include <vector>

VehiclePtr GetRedCar() {
	auto vehicle = VehiclePrototype::GetPrototype("car") ;
	vehicle->SetColor("Red") ;
	vehicle->SetHitPoints(10) ;
	vehicle->SetSpeed(30) ;
	vehicle->SetPosition({0,0}) ;
	Animation anim{"red.anim"} ;
	vehicle->SetAnimationData(anim.GetAnimationData()) ;
	return vehicle ;
}
VehiclePtr GetGreenCar() {
	auto vehicle = VehiclePrototype::GetPrototype("car") ;
	vehicle->SetColor("Green") ;
	vehicle->SetHitPoints(5) ;
	vehicle->SetSpeed(30) ;
	vehicle->SetPosition({100,0}) ;
	Animation anim{"green.anim"} ;
	vehicle->SetAnimationData(anim.GetAnimationData()) ;
	return vehicle ;
}
VehiclePtr GetYellowBus() {
	auto vehicle = VehiclePrototype::GetPrototype("bus") ;
	vehicle->SetColor("Yellow") ;
	vehicle->SetHitPoints(20) ;
	vehicle->SetSpeed(25) ;
	vehicle->SetPosition({100,200}) ;
	Animation anim{"ybus.anim"} ;
	vehicle->SetAnimationData(anim.GetAnimationData()) ;
	return vehicle ;
}
VehiclePtr GetBlueBus() {
	auto vehicle = VehiclePrototype::GetPrototype("bus") ;
	vehicle->SetColor("Blue") ;
	vehicle->SetHitPoints(25) ;
	vehicle->SetSpeed(25) ;
	vehicle->SetPosition({200,200}) ;
	Animation anim{"bbus.anim"} ;
	vehicle->SetAnimationData(anim.GetAnimationData()) ;
	return vehicle ;
}

class GameManager {
	std::vector<VehiclePtr> m_Vehicles{};
public:
	void Run() {
		m_Vehicles.push_back(GetRedCar());
		m_Vehicles.push_back(GetGreenCar());
		m_Vehicles.push_back(GetYellowBus());
		m_Vehicles.push_back(GetBlueBus());

		int count{5};
		using namespace std;
		while (count != 0) {
			std::this_thread::sleep_for(1s);
			system("clear");
			
			for (auto vehicle : m_Vehicles)
				vehicle->Update();

			if (count == 2) {
				auto vehicle = m_Vehicles[0]->Clone();
				vehicle->SetPosition({50, 50});
				vehicle->SetHitPoints(15);
				m_Vehicles.push_back(vehicle);
			}
			if (count ==3) {
				auto vehicle = m_Vehicles[2]->Clone();
				vehicle->SetPosition({150, 250});
				vehicle->SetSpeed(10);
				m_Vehicles.push_back(vehicle);
			}
			count--;
		}
	}
};







int main() {
	VehiclePrototype::RegisterPrototype("car", std::make_shared<Car>());
	VehiclePrototype::RegisterPrototype("bus", std::make_shared<Bus>());
	GameManager mgr;
	mgr.Run();
	return 0;
}