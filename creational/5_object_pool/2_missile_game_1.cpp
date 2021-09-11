/*
	Shooting missiles game

	The player can shoot missiles to aleins and the aliens keep popping up.
	Lets simulate the creation and destruction of the missiles.

	This implementation can cause issue. Because we are repetedly creating and 
	destroying objects on the heap and heap allocation is expensive.
	When repetitive construction and destruction of objects takes place on the heap
	it becomes fragmented.

	And this may impact the performance of the heap.
	THus we should use ObjectPool here.
*/


//////////////////////////////////////////////////
/////////////////////////// Missile.h
//////////////////////////////////////////////////
// #pragma once
class Missile {
	bool m_IsVisible{true};
public:
	void SetVisible(bool);
	bool IsVisible() const;
	Missile();
	~Missile();
	void Update();
};


//////////////////////////////////////////////////
/////////////////////////// Missile.cpp
//////////////////////////////////////////////////
#include <iostream>

void Missile::SetVisible(bool visibility) {
	m_IsVisible = visibility;
}

bool Missile::IsVisible() const {
	return m_IsVisible;
}

Missile::Missile() {
	std::cout << "+++ Missile Created\n";
}

Missile::~Missile() {
	std::cout << "~~~ Missile Destroyed\n";
}

#include<thread>
void Missile::Update() {
	std::cout << " -> ";
	using namespace std;
	std::this_thread::sleep_for(0.2s);
}



//////////////////////////////////////////////////
/////////////////////////// main.cpp
//////////////////////////////////////////////////
#include <thread>
#include <vector>

std::vector<std::shared_ptr<Missile>> missiles{};

void Fire() {
	missiles.push_back(std::make_shared<Missile>());
	missiles.push_back(std::make_shared<Missile>());
}

void Animate() {
	for (auto &m : missiles) {
		m->Update();
	}
}

void Explode() {
	std::cout << "X\n";
	for (auto &m : missiles) {
		m->SetVisible(false);
	}
	missiles.clear();
	using namespace std;
	std::this_thread::sleep_for(1s);
	std::cout << "\n\n";
}

void GameLoop() {
	int counter{0};
	while (true) {
		++counter;
		if (counter == 1) {
			// Fire the missile.
			Fire();
			std::flush(std::cout);
		} 
		else if (counter >= 1 && counter <= 5) {
			// Animate
			Animate();
			std::flush(std::cout);
		}
		else if (counter > 5) {
			// Explode
			Explode();
			std::flush(std::cout);
			counter = 0;
		}
	}
	using namespace std;
	this_thread::sleep_for(1s);
}

int main() {
	GameLoop();

	return 0;
}