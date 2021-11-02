/*
    In 4_sensor_2.cpp we saw how to register observers for specific kind of notificaitons.

    Now, assume there are multiple subjects (sensors). The objects want to depend on readings from different
    kinds of sensors, e.g. temperature, wind-speed, rainfall

    If  the observers depend on multiple subject then there will be lot of dependencies between the classes.
    All the objects will have to keep track of their subjets.

    One way of reducing the dependecy between the subjects and the observers is to indroduce
    another component and that component will take care of the interaction between the subject
    and the observers. It is called the "Change-Manager"

    When the subjects observe a change they will send a notificaiton to the change manager and the change manager
    notifies the observers.
    The change manager is an example of the mediator design pattern.

    - Change manager is responsible for managing the mapping between the subjects and their observers.
      Thus the subjects don't have to maintain the Observers.

    - The observers will register with the change manager.

    - When the state of a subject changes, it will notify the change manager that will in
      turn send update to the observers.
*/

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




		                                            ---------------------    
		              ;-----m_Mapping-------------- |   ChangeManager   |---------m_Mapping----------------;
		              |      		                ---------------------                                  |                    
                      |                                     /|\                                              | 
                     \|/                   ________m_pMgr____|                                              \|/                            
            ---------------------          |   |                                                   ---------------------                                                                                        
            |      Sensor       |<---------|---|-----------------------pSensor---------------------|  OnValueChanged   |                                                                                        
	        ---------------------          |   |                                            	   ---------------------                                                                                        
                     /_\                   |   |                                                            /_\                                                                                        
          ____________|_____________       |   |                                             ________________|_________________                                                                                        
          |                        |       |   |                                             |               |                |                               
  ---------------------   -------------------  |                                        ------------  -----------------  -------------
  | TemperatureSensor |   | WindSpeedSensor |  |                                        | Recorder |  | SimpleDisplay |  | Billboard |
  ---------------------   -------------------  |                                        ------------  -----------------  -------------
            |                                  |        
            |__________________________________|  




            Since we have only one instance of the ChangeManager in our implementation so it
            can also be implemented as a Singleton.
*/

// Subject
/////////////////////////////////////////////
/////////////////////        Sensor.h
/////////////////////////////////////////////
class Sensor {
public:
    virtual float GetValue() const = 0;
    virtual void Notify() = 0;
    virtual ~Sensor() = default;
};

// Observer
///////////////////////////////////////////
////////////////////////  OnValuechanged.h
///////////////////////////////////////////
class OnValueChanged {
public:
    //  Using pSensor the Observers can know with Subject sent them the notification.
    virtual void Notify(Sensor *pSensor) = 0;
    virtual ~OnValueChanged() = default;
};


/////////////////////////////////////////////
/////////////////////        ChangeManager.h
/////////////////////////////////////////////
#include <unordered_map>
#include <list>
class ChangeManager {
    // A mapping between the subjects and their observers.
    std::unordered_map<Sensor *, std::list<OnValueChanged*>> m_Mapping;
public:
    void Register(Sensor *pSensor, OnValueChanged *pValueChanged) {
        m_Mapping[pSensor].push_back(pValueChanged);
    }

    void DeRegister(Sensor *pSensor, OnValueChanged *pValueChanged) {
        m_Mapping[pSensor].remove(pValueChanged);
    }

    void Notify(Sensor *pSensor) {
        for (auto ob : m_Mapping[pSensor]) {
            ob->Notify(pSensor);
        }
    }
};





//////////////////////////////////////////////
////////////////////////  TemperatureSensor.h
//////////////////////////////////////////////
class TemperatureSensor : public Sensor {
    float m_Temp;
    ChangeManager *m_pMgr;
public:
    TemperatureSensor(ChangeManager *pMgr) : m_pMgr{pMgr} {}

    void Notify() override {
        m_pMgr->Notify(this);
    }

    void SetTemp(float value) {
        m_Temp = value;
        Notify();
    }

    float GetValue() const override {
        return m_Temp;
    }
};



//////////////////////////////////////////////
////////////////////////  WindSpeedSensor.h
//////////////////////////////////////////////
class WindSpeedSensor : public Sensor {
    float m_Speed;
    ChangeManager *m_pMgr;
public:
    WindSpeedSensor(ChangeManager *pMgr) : m_pMgr{pMgr} {}

    void Notify() override {
        m_pMgr->Notify(this);
    }

    // to simulate the change in wind speed.
    void SetSpeed(float value) {
        m_Speed = value;
        Notify();
    }

    float GetValue() const override {
        return m_Speed;
    }
};




///////////////////////////////////////
////////////////////////   Billboard.h
///////////////////////////////////////
#include <iostream>
class Billboard : public OnValueChanged {
public:
    void Notify(Sensor *pSensor) override {
        std::cout << "[BILLBOARD] " << pSensor->GetValue() << "\n";
    }
};



///////////////////////////////////////
////////////////////////   Recorder.h
///////////////////////////////////////
#include <iostream>
class Recorder : public OnValueChanged {
public:
    void Notify(Sensor *pSensor) override {
        std::cout << "[RECORDER] " << pSensor->GetValue() << "\n";
    }
};


///////////////////////////////////////////
////////////////////////   SimpleDisplay.h
///////////////////////////////////////////
#include <iostream>
class SimpleDisplay : public OnValueChanged {
public:
    void Notify(Sensor *pSensor) override {
        std::cout << "[SIMPLEDISPLAY] " << pSensor->GetValue() << "\n";
    }
};





int main() {
    ChangeManager mgr;
    TemperatureSensor sensor{&mgr};
    WindSpeedSensor windSensor{&mgr};

    Billboard bb;
    SimpleDisplay sd;
    Recorder rec;

    mgr.Register(&sensor, &bb);
    mgr.Register(&sensor, &sd);
    mgr.Register(&sensor, &rec);

    mgr.Register(&windSensor, &bb);

    std::cout << "Temperature changing...\n";
    sensor.SetTemp(21.3f);
    
    std::cout << "Wind speed changing...\n";
    windSensor.SetSpeed(50);

    return 0;
}