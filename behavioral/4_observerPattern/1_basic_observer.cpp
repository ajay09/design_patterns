/*

		---------------------		m_Observers                     ---------------------
		|      Subject      |-------------------------------------->|     Observer      |
		---------------------				                        ---------------------
		| Attach(Observer)  |				                        | Update()          |
		| Detach(Observer)  |				                        ---------------------
		| Notify()	        |  for all o in obeservers {        	        /_\
		---------------------      o->Update()		        	             |
		        /_\            }			        	                     |
		         |					        	                             |
		         |					        	                             |
		         |					        	                             |
		         |					        	                             |
		---------------------			m_pSubject                  ---------------------
		|  ConcreteSubject  |<--------------------------------------| ConcreteObserver  |
		---------------------					                    ---------------------
		| GetState()        | return subjectState	                | Update()          |   observerState = subject->GetState()
		| SetState()        |					                    ---------------------
		---------------------					                    | observerState     |
		| subjectState      |					                    ---------------------
		---------------------

		- ConcreteSubject and ConcreteObject are loosely coupled.
		  It doesn't know how many ConcreteObjects are registred with it.
*/

////////////////////////////////////
/////////////////////  Observer.h
////////////////////////////////////
class Observer {
public:
	virtual void Update() = 0;
	~Observer() = default;
};


////////////////////////////////////
//////////////////////  Subject.h
////////////////////////////////////
#include <list>

class Subject {
	std::list<Observer*> m_Observers;
public:
	void Notify() {
		for (auto observer : m_Observers) {
			observer->Update();
		}
	}

	void Attach(Observer& ob) {
		m_Observers.push_back(&ob);
	}

	void Detach(Observer& ob) {
		// Removes from the container all the elements that compare equal to val. 
		// This calls the destructor of these objects and reduces the container size by the number of elements removed.
		m_Observers.remove(&ob);
	}

	virtual ~Subject() = default;
};



////////////////////////////////////////
//////////////////   ConcreteSubject.h
////////////////////////////////////////
#include <string>
class ConcreteSubject : public Subject {
	std::string m_SubjectState;
public:
	const std::string GetState() const {
		return m_SubjectState;
	}

	void SetState(const std::string state) {
		m_SubjectState = state;
		Notify();
	}
};


////////////////////////////////////////
//////////////////  ConcreteObserver.h
////////////////////////////////////////
#include <iostream>

class ConcreteObserver : public Observer {
	// Once the subject calls Update() for an observer the observer needs to get the state of the subject.
	ConcreteSubject *m_pSubject;
public:
	ConcreteObserver(ConcreteSubject *pSubject) : m_pSubject{pSubject} {}

	void Update() override {
		std::cout << "[ConcreteObserver] Received notification. State is : "
		          << m_pSubject->GetState() << std::endl;
	}
};










int main() {
	ConcreteSubject sub;
	ConcreteObserver ob1(&sub);
	ConcreteObserver ob2(&sub);

	sub.Attach(ob1);
	sub.Attach(ob2);

	std::cout << "Changing state of the subject...\n";
	sub.SetState("C++");

	return 0;
}



