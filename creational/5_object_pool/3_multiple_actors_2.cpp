/*
	Shooting actors game

	Now our object pool handles creation of both Alien and Missile

	But our design still has issues.
	Consider the ActorPool::Create(const string&) function.
	It is tightly coupled with concrete actors Missile and Alien.

	It has to be modified if in future we have to add more actors.
	And changes to Alien and Missile classes will percolate to this function.
	This violates the open-closed principle.

	To make the design more flexible we have to remove the dependency of the ActorPool
	on the concrete classes. For that we will use the Factory Method.
	The ActorPool will create the instances of different types of Actors through a Factory Method.


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
	std::this_thread::sleep_for(0.4s);
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
using ActorCreator = std::function<ActorPtr()>;

class ActorPool {
	struct ActorInfo {
		std::vector<ActorPtr> m_pActors{};
		ActorCreator m_Creator;
	};
	static std::unordered_map<std::string, ActorInfo> m_pActorPool;
	ActorPool() = default;
	static ActorPtr Create(const std::string &key);
public:
	static ActorPtr AcquireActor(const std::string&);
	static void ReleaseActor(const ActorPtr&, const std::string&);

	static void RegisterCreator(const std::string&, ActorCreator);
};

//////////////////////////////////////////////////
/////////////////////////// ActorPool.cpp
//////////////////////////////////////////////////
std::unordered_map<std::string, ActorPool::ActorInfo> ActorPool::m_pActorPool;
#include <iostream>

ActorPtr ActorPool::Create(const std::string &key) {
	if (m_pActorPool.find(key) == end(m_pActorPool)) {
		std::cout << "[Pool] Creator for " << key << " is not registered.\n";
		return nullptr;
	}
	std::cout << "[Pool] Creating a new " << key << ".\n";
	auto actor = m_pActorPool[key].m_Creator();
	m_pActorPool[key].m_pActors.push_back(actor);
	return actor;
}

ActorPtr ActorPool::AcquireActor(const std::string& key) {
	if (m_pActorPool.find(key) != end(m_pActorPool)) {
		for (auto &m : m_pActorPool[key].m_pActors) {
			if (!m->IsVisible()) {
				std::cout << "Using an existing " << key << "\n";
				// Reset state
				m->SetVisible(true);
				return m;
			}
		}
	}
	return Create(key);
}

void ActorPool::ReleaseActor(const ActorPtr &m, const std::string &key) {
	std::cout << "Returning the actor instance.\n";
	m->SetVisible(false);
}

void ActorPool::RegisterCreator(const std::string &key, ActorCreator creator) {
	m_pActorPool[key].m_Creator = creator;
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
	ActorPool::RegisterCreator("alien", []() { return std::make_shared<Alien>(); });
	ActorPool::RegisterCreator("missile", []() { return std::make_shared<Missile>(); });
	GameLoop();

	return 0;
}