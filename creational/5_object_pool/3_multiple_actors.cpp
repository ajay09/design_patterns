/*
	Shooting actors game

	Till now we have not included Aliens in the game.

	We can use an object pool for the Aliens as well.
*/

// Represents all kinds of actors in the game.
//////////////////////////////////////////////////
/////////////////////////// Actor.h
//////////////////////////////////////////////////
// #pragma once
class Actor {
	bool m_IsVisible{true};
public:
	void SetVisible(bool v) { m_IsVisible = v; }
	bool IsVisible() const { return m_IsVisible; }
	virtual void Update() = 0;
	virtual ~Actor() = default;
};


//////////////////////////////////////////////////
/////////////////////////// Alien.h
//////////////////////////////////////////////////
// #pragma once
class Alien : public Actor{
public:
	Alien();
	~Alien();
	void Update() override;
};


//////////////////////////////////////////////////
/////////////////////////// Missile.h
//////////////////////////////////////////////////
// #pragma once
class Missile : public Actor {
public:
	Missile();
	~Missile();
	// to animate the actor
	void Update() override;
};


//////////////////////////////////////////////////
/////////////////////////// Alien.cpp
//////////////////////////////////////////////////
#include <iostream>

Alien::Alien() {
	std::cout << "++++++ Alien()\n";
}

Alien::~Alien() {
	std::cout << "~~~~~~ Alien()\n";
}

void Alien::Update() {
	std::cout << "@ ";
}


//////////////////////////////////////////////////
/////////////////////////// Missile.cpp
//////////////////////////////////////////////////
#include <iostream>

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


// Instead of new to create actors and Aliens, we use factory method
//////////////////////////////////////////////////
/////////////////////////// ActorPool.h
/////////////////////////// It should be Singleton or Monostate.
//////////////////////////////////////////////////
// #pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

using ActorPtr = std::shared_ptr<Actor>;

class ActorPool {
	static std::unordered_map<std::string, std::vector<ActorPtr>> m_pActorPool;
	ActorPool() = default;
	static ActorPtr Create(const std::string &key);
public:
	static ActorPtr AcquireActor(const std::string&);
	static void ReleaseActor(const ActorPtr&, const std::string&);
};

//////////////////////////////////////////////////
/////////////////////////// ActorPool.cpp
//////////////////////////////////////////////////
std::unordered_map<std::string, std::vector<ActorPtr>> ActorPool::m_pActorPool;
#include <iostream>

ActorPtr ActorPool::Create(const std::string &key) {
	std::cout << "[Pool] Creating a new " << key << ".\n";
	if (key == "missile") {
		return std::make_shared<Missile>();
	} else if (key == "alien") {
		return std::make_shared<Alien>();
	}
	return nullptr;
}

ActorPtr ActorPool::AcquireActor(const std::string& key) {
	if (m_pActorPool.find(key) != end(m_pActorPool)) {
		for (auto &m : m_pActorPool[key]) {
			if (!m->IsVisible()) {
				std::cout << "Using an existing " << key << "\n";
				// Reset state
				m->SetVisible(true);
				return m;
			}
		}
	}
	auto m = Create(key);
	m_pActorPool[key].push_back(m);
	return m;
}

void ActorPool::ReleaseActor(const ActorPtr &m, const std::string &key) {
	std::cout << "Returning the actor instance.\n";
	m->SetVisible(false);
}


//////////////////////////////////////////////////
/////////////////////////// main.cpp
//////////////////////////////////////////////////
#include <thread>
#include <vector>

std::vector<std::shared_ptr<Actor>> actors{};

void Fire() {
	// actors.push_back(std::make_shared<Missile>());
	// actors.push_back(std::make_shared<Missile>());
	actors.push_back(ActorPool::AcquireActor("missile"));
	actors.push_back(ActorPool::AcquireActor("alien"));
}

void Animate() {
	for (auto &m : actors) {
		m->Update();
	}
}

void Explode() {
	std::cout << "X\n";
	for (auto &m : actors) {
		ActorPool::ReleaseActor(m, "missile");
	}
	actors.clear();
	using namespace std;
	std::this_thread::sleep_for(1s);
	std::cout << "\n\n";
}

void GameLoop() {
	int counter{0};
	int loop{2};
	while (loop) {
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
			--loop;
		}
	}
	using namespace std;
	this_thread::sleep_for(1s);
}

int main() {
	GameLoop();

	return 0;
}