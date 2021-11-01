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
class TemperatureSensor {
    std::list<OnValuechanged*> m_pSubscribers;
    float m_Temp;
public:
    void Register(OnValuechanged *pSub) {
        m_pSubscribers.push_back(pSub);
    }

    void Deregister(OnValuechanged *pSub) {
        m_pSubscribers.remove(pSub);
    }

    void Notify(float value) {
        for (auto sub : m_pSubscribers) {
            sub->Notify(value);
        }
    }

    void SetTemp(float value) {
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

    sensor.Register(&bb);
    sensor.Register(&sd);
    sensor.Register(&rec);

    sensor.SetTemp(21.3f);
    sensor.SetTemp(21.9f);
    sensor.SetTemp(25.3f);
    sensor.SetTemp(21.3f);

    return 0;
}