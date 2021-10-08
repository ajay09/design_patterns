// Multiple Dispatch
// Even after double dispatch we might face some issue.
// suppose if we want to determine the call based on two arguments instead of one.
// This is not just related to visitor patter, but a general idea that applies
// at many places.

#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <typeindex>
#include <map>

using namespace std;

/*
struct GameObject {
	virtual ~GameObject() = default;
};

struct Planet : GameObject{};
struct Asteroid : GameObject{};
struct Spaceship : GameObject{};

// Depending upon which of these collide you have different results
// and we might want to have separate functions for each of them.

void spaceship_planet() {  cout << "spaceship lands on planet\n";  }

void asteroid_planet() {   cout << "asteroid burns up in atmosphere\n";  }

void asteroid_spaceship() {	cout << "asteroid hits and destroys spaceship\n"; }


// A general interface which dispatches the above functions depending upon 
// the actual type of the game objects.
void collide(GameObject &first, GameObject &second) {

}
*/

struct GameObject;
void collide(GameObject&, GameObject&);

// Approach - 1
// expose the type-index of each of GameObject
struct GameObject {
	virtual ~GameObject() = default;
	virtual type_index type() const = 0;
	// Making collide a member function
	virtual void collide(GameObject &other) {
		::collide(*this, other);
	}
};

// CRTP
// take derived type as a template argument
template <typename T> struct GameObjectImpl : GameObject {
	type_index type() const override {
		return typeid(T);
	}
};

struct Planet : GameObjectImpl<Planet>{};
struct Asteroid : GameObjectImpl<Asteroid>{};
struct Spaceship : GameObjectImpl<Spaceship>{};
// Suppose we want to add a new object 
// This won't work because it inherits the type() from GameObjectImpl<Spaceship>
// struct ArmedSpaceship : Spaceship {};
struct ArmedSpaceship : Spaceship {
	type_index type() const override {
		return typeid(ArmedSpaceship);
	};
};



// Depending upon which of these collide you have different results
// and we might want to have separate functions for each of them.

void spaceship_planet() {  cout << "spaceship lands on planet\n";  }

void asteroid_planet() {   cout << "asteroid burns up in atmosphere\n";  }

void asteroid_spaceship() {	cout << "asteroid hits and destroys spaceship\n"; }

void asteroid_armed_spaceship() {	cout << "spaceship shoots the asteroid\n"; }

map<pair<type_index, type_index>, void(*)(void)> outcomes{
	{{typeid(Spaceship), typeid(Planet)}, spaceship_planet}, {{typeid(Planet), typeid(Spaceship)}, spaceship_planet},
	{{typeid(Asteroid), typeid(Planet)}, asteroid_planet}, {{typeid(Planet), typeid(Asteroid)}, asteroid_planet},
	{{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship}, {{typeid(Spaceship), typeid(Asteroid)}, asteroid_spaceship},
	{{typeid(Asteroid), typeid(ArmedSpaceship)}, asteroid_armed_spaceship}, {{typeid(ArmedSpaceship), typeid(Asteroid)}, asteroid_armed_spaceship}
};

// A general interface which dispatches the above functions depending upon 
// the actual type of the game objects.
void collide(GameObject &first, GameObject &second) {
	auto it = outcomes.find({first.type(), second.type()});
	if (it != outcomes.end()) {
		it->second();
	} else {
		cout << "objects pass each other harmlessly\n";
	}
}

int main() {

	Spaceship spaceship;
	Asteroid asteroid;
	Planet planet;
	ArmedSpaceship armed_spaceship;

	//collide(planet, spaceship);
	planet.collide(spaceship);
	collide(planet, asteroid);
	collide(asteroid, spaceship);
	collide(asteroid, armed_spaceship);
	collide(planet, planet);

	return 0;
}



/*
struct GameObject {
	virtual ~GameObject() = default;
};

struct Planet : GameObject{};
struct Asteroid : GameObject{};
struct Spaceship : GameObject{};

// Depending upon which of these collide you have different results
// and we might want to have separate functions for each of them.

void spaceship_planet() {  cout << "spaceship lands on planet\n";  }

void asteroid_planet() {   cout << "asteroid burns up in atmosphere\n";  }

void asteroid_spaceship() {	cout << "asteroid hits and destroys spaceship\n"; }


// A general interface which dispatches the above functions depending upon 
// the actual type of the game objects.
void collide(GameObject &first, GameObject &second) {
	
}
*/