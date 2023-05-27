#ifndef PLATFORM_H
#define PLATFORM_H

// include
#include <list>
#include "Sensor.h" //leave commented out to prevent circular references
#include "Actuator.h"
#include "PivotPoint.h"

//class Sensor;

class Platform
{
public:
    enum class System_Property { // TODO: add units associated with the properties
        OtherStuff,
        MoreStuff,

        ANG_VEL,
        ANG_POS,
		ANG_ACC
    };
    
    Platform();

    void AddActuator(Actuator* a);
    void AddSensor(Sensor* s);

    void PropagateModelDeltaTime(uint32_t timeStep_ms);

    Sensor* GetPtrToSensor(int _sensorID);
    Actuator* GetPtrToActuator(int _actuatorID);
    
    float GetSystemPos();
    float GetSystemVel();
	float GetSystemAcc();

private:
    std::list<Actuator*> actuatorList;
    std::list<Sensor*> sensorList;
    PivotPoint pivotPoint;

    float erikVel = 5;
    float erikPos = 0;

	float ang_acc;
	float ang_pos;
	float ang_vel;
	
	float l;
	float const g = 9.81f;
};

#endif 

// --- End of File ---