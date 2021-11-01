/*
	Alert system of a Game using Observer Pattern

	If the alarm is turned on all the NPCs close to the player will move towards the player and attack.

	----------------			m_Observers		-----------------
	|    Alarm     |--------------------------->| AlarmObserver |
	----------------							-----------------
	| Attach()	   |							       /_\
	| Detach()	   |							        |
	| Notify()	   |									|
	| SetAlarmOn() |									|
	----------------								    |
								________________________|____________________________
								|						|							|
							|  Tank  |			   | Solidier |				| HeavyGunner |



	- 	
*/

////////////////////////////////////////////////
//////////////////////////////  AlarmObserver.h
////////////////////////////////////////////////
class AlarmObserver {
public:
	virtual void AlarmOn() = 0;
	virtual ~AlarmObserver() = default;
};



////////////////////////////////////////////////
//////////////////////////////  Soldier.h
////////////////////////////////////////////////
#include <iostream>

class Soldier : public AlarmObserver {
public:
	void AlarmOn() override {
		std::cout << "Soldier alerted! Firing...!!\n";
	}
};




////////////////////////////////////////////////
//////////////////////////////  HeavyGunner.h
////////////////////////////////////////////////
#include <iostream>

class HeavyGunner : public AlarmObserver {
public:
	void AlarmOn() override {
		std::cout << "HeavyGunner alerted! Launcing rocket...!!\n";
	}
};


////////////////////////////////////////////////
//////////////////////////////  Tank.h
////////////////////////////////////////////////
#include <iostream>

class Tank : public AlarmObserver {
public:
	void AlarmOn() override {
		std::cout << "Tank alerted! Firing...!!\n";
	}
};


// Subject
//////////////////////////////////////////////////
//////////////////////////////   Alarm.h
//////////////////////////////////////////////////
#include <list>
class Alarm {
	std::list<AlarmObserver*> m_pObservers;
public:
	void Attach(AlarmObserver *pOb) {
		m_pObservers.push_back(pOb);
	}

	void Detach(AlarmObserver *pOb) {
		m_pObservers.remove(pOb);
	}

	void Notify() {
		for (auto pOb : m_pObservers) {
			pOb->AlarmOn();
		}
	}

	void SetAlarmOn() {
		std::cout << "Alarm is set on!!!\n";
		Notify();
	}
};


int main() {
	Soldier soldier{};
	HeavyGunner heavyGunner{};
	Tank tank{};

	Alarm alarm{};
	alarm.Attach(&soldier);
	alarm.Attach(&heavyGunner);
	alarm.Attach(&tank);

	alarm.SetAlarmOn();

	return 0;
}