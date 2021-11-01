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



	Automatic Observer Registration.
    - When a player is created close to the alarm, it automatically registers itself for notification.
    - When a player is killed it automatically deregisters itself form the alarm.

*/

// Subject
//////////////////////////////////////////////////
//////////////////////////////   Alarm.h
//////////////////////////////////////////////////
#include <list>
#include <iostream>

class AlarmObserver;

class Alarm {
	std::list<AlarmObserver*> m_pObservers;
public:
	void Attach(AlarmObserver *pOb) ;
	void Detach(AlarmObserver *pOb) ;
	void Notify();

	void SetAlarmOn() {
		std::cout << "Alarm is set on!!!\n";
		Notify();
	}
};


////////////////////////////////////////////////
//////////////////////////////  AlarmObserver.h
////////////////////////////////////////////////
class AlarmObserver {
protected:
    Alarm *m_pAlarm;
public:
    AlarmObserver(Alarm *pAlarm) : m_pAlarm{pAlarm} {}
	virtual void AlarmOn() = 0;
	virtual ~AlarmObserver() = default;
};



void Alarm::Attach(AlarmObserver *pOb) {
    m_pObservers.push_back(pOb);
}

void Alarm::Detach(AlarmObserver *pOb) {
    m_pObservers.remove(pOb);
}

void Alarm::Notify() {
    for (auto pOb : m_pObservers) {
        pOb->AlarmOn();
    }
}




////////////////////////////////////////////////
//////////////////////////////  Soldier.h
////////////////////////////////////////////////
#include <iostream>

class Soldier : public AlarmObserver {
public:
    Soldier(Alarm *pAlarm) :  AlarmObserver{pAlarm} {
        m_pAlarm->Attach(this);
    }

    ~Soldier() {
        m_pAlarm->Detach(this);
    }

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
    HeavyGunner(Alarm *pAlarm) :  AlarmObserver{pAlarm} {
        m_pAlarm->Attach(this);
    }

    ~HeavyGunner() {
        m_pAlarm->Detach(this);
    }

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
    Tank(Alarm *pAlarm) :  AlarmObserver{pAlarm} {
        m_pAlarm->Attach(this);
    }

    ~Tank() {
        m_pAlarm->Detach(this);
    }

	void AlarmOn() override {
		std::cout << "Tank alerted! Firing...!!\n";
	}
};




int main() {
	Alarm alarm{};

	Soldier soldier{&alarm};
	HeavyGunner heavyGunner{&alarm};
	Tank tank{&alarm};


	alarm.SetAlarmOn();

	return 0;
}