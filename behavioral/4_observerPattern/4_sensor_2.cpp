/*
    Temperatur Sensor

    Displaying the data from the sensor on different kinds of objects.
    e.g. Analog Display
         Computer
         Mobie Phone
         Bill Board
         Database

    When the temp. changes a notification is sent to all of the devices and the devices handle the notification
    in their own ways.


		---------------------		m_Subscribers                   ---------------------
		| TemperatureSensor |-------------------------------------->|  OnValueChanged   |
		---------------------				                        ---------------------
		| Attach(View*)     |				                                /_\
		| Detach(View*)     |		                                         |
		| Notify()	        |                                     	         |        
		---------------------                  	            	             |
                                                    _________________________|________________________________
                                                    |                        |                               |
                                        ---------------------          ---------------------          ---------------------
                                        | Recorder          |          | SimpleDisplay     |          | Billboard        |
                                        ---------------------    	   ---------------------          ---------------------

    -  In this case the Observers don't have pointers to the Subject.
       It's not required as they don't have to fetch any data from the Subject.
    
    - In this case the data is sent as part of the notification itself.

Every observer get a notification when the temp. changes.
Suppose Billboard and SimpleDisplay don't want to handle the notification if the 
change in the temperature is very low.

How to ensure this?
    Sol-1 => They can store the prev temp. and on receiving the notification they can check the
              change in the temp and if change is low then they can discard the notification.

            Problem : But this means if you have 100s of observers, all of them will still get
                      the notification and they will simply discard the notification if they don't
                      want to display the change.

                      Also all the observers which don't want to display small changes will have to
                      include similar code and if the threshold changes in future then we have to 
                      make changes at many places.

    Sol-2 => Change the notification mechanism in such a way that the observers can register for
             specific kinds of notificaitons.

            We will have to categorize the change in the temperature and we can use enum to represent these
            categories.

            Thus instead of observers handling the notificaiton and ignoring based on some values, let
            the observers register for specific notifcaitons only.
             

*/

// Observer
///////////////////////////////////////////
////////////////////////  OnValuechanged.h
///////////////////////////////////////////
class OnValuechanged {
public:
    virtual void Notify(float value) = 0;
    virtual ~OnValuechanged() = default;
};


// Subject
//////////////////////////////////////////////
////////////////////////  TemperatureSensor.h
//////////////////////////////////////////////
#include <list>
#include <iostream>
#include <unordered_map>

// Categories to register small and large changes in the temp.
enum class TemperatureChange {SMALL, LARGE};

class TemperatureSensor {
    std::unordered_map<TemperatureChange, std::list<OnValuechanged*>> m_pSubscribers;
    float m_Temp;
    float m_Change;

    void Notify(TemperatureChange tc, float value) {
        for (auto subs : m_pSubscribers[tc])
            subs->Notify(value);
    }
public:
    void Register(TemperatureChange tc, OnValuechanged *pSub) {
        m_pSubscribers[tc].push_back(pSub);
    }

    void Deregister(TemperatureChange tc, OnValuechanged *pSub) {
        m_pSubscribers[tc].remove(pSub);
    }

    void Notify(float value) {
        if (m_Change > 0.5f) {                  // large change observer are notified only if change > 0.5
            Notify(TemperatureChange::LARGE, value);
        }
        Notify(TemperatureChange::SMALL, value); // small change observers are notified everytime.
    }

    void SetTemp(float value) {
        std::cout <<  "--------------------- TEMPERATURE CHANGED ---------------------\n";
        m_Change = abs(m_Temp - value);
        m_Temp = value;
        Notify(m_Temp);
    }
};




///////////////////////////////////////
////////////////////////   Billboard.h
///////////////////////////////////////
#include <iostream>
class Billboard : public OnValuechanged {
public:
    void Notify(float value) override {
        std::cout << "[BILLBOARD] " << value << "\n";
    }
};



///////////////////////////////////////
////////////////////////   Recorder.h
///////////////////////////////////////
#include <iostream>
class Recorder : public OnValuechanged {
public:
    void Notify(float value) override {
        std::cout << "[RECORDER] " << value << "\n";
    }
};


///////////////////////////////////////////
////////////////////////   SimpleDisplay.h
///////////////////////////////////////////
#include <iostream>
class SimpleDisplay : public OnValuechanged {
public:
    void Notify(float value) override {
        std::cout << "[SIMPLEDISPLAY] " << value << "\n";
    }
};





int main() {
    TemperatureSensor sensor;
    Billboard bb;
    SimpleDisplay sd;
    Recorder rec;

    sensor.Register(TemperatureChange::LARGE, &bb);
    sensor.Register(TemperatureChange::LARGE, &sd);
    sensor.Register(TemperatureChange::SMALL, &rec);

    sensor.SetTemp(21.3f);
    sensor.SetTemp(21.9f);
    sensor.SetTemp(25.3f);
    sensor.SetTemp(21.3f);

    return 0;
}