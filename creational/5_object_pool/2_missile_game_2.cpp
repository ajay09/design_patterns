/*
	Shooting missiles game

	Using a pool of missiles.
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


// Instead of new to create Missile, we use factory method
//////////////////////////////////////////////////
/////////////////////////// MissilePool.h
/////////////////////////// It should be Singleton or Monostate.
//////////////////////////////////////////////////
// #pragma once
#include <vector>
#include <memory>
using MissilePtr = std::shared_ptr<Missile>;
class MissilePool {
	static std::vector<MissilePtr> m_pMissilePool;
	MissilePool() = default;
public:
	static MissilePtr AcquireMissile();
	static void ReleaseMissile(const MissilePtr&);
};

//////////////////////////////////////////////////
/////////////////////////// MissilePool.cpp
//////////////////////////////////////////////////
std::vector<MissilePtr> MissilePool::m_pMissilePool;
#include <iostream>

MissilePtr MissilePool::AcquireMissile() {
	for (auto &m : m_pMissilePool) {
		if (!m->IsVisible()) {
			std::cout << "Using an existing missile\n";
			m->SetVisible(true);
			return m;
		}
	}
	auto m = std::make_shared<Missile>();
	m_pMissilePool.push_back(m);
	return m;
}

void MissilePool::ReleaseMissile(const MissilePtr &m) {
	std::cout << "Returning an existing missile instance.\n";
	m->SetVisible(false);
}


//////////////////////////////////////////////////
/////////////////////////// main.cpp
//////////////////////////////////////////////////
#include <thread>
#include <vector>

std::vector<std::shared_ptr<Missile>> missiles{};

void Fire() {
	// missiles.push_back(std::make_shared<Missile>());
	// missiles.push_back(std::make_shared<Missile>());
	missiles.push_back(MissilePool::AcquireMissile());
	missiles.push_back(MissilePool::AcquireMissile());
}

void Animate() {
	for (auto &m : missiles) {
		m->Update();
	}
}

void Explode() {
	std::cout << "X\n";
	for (auto &m : missiles) {
		MissilePool::ReleaseMissile(m);
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