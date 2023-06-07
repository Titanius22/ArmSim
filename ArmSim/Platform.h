#ifndef PLATFORM_H
#define PLATFORM_H

// include
#include <list>
#include <string>
#include "Sensor.h" //leave commented out to prevent circular references
#include "Actuator.h"
#include "PivotPoint.h"

//class Sensor;

class Platform
{

friend class SimManager;

public:
    enum class System_Property { // TODO: add units associated with the properties
        ARM_ANGLE,
        OtherStuff,
        MoreStuff,

        ERIK_VEL,
        ERIK_POS
    };
    
    Platform() = delete;
    Platform(std::string _name);

    void AddActuator(Actuator* a);
    void AddSensor(Sensor* s);

    void PropagateModelDeltaTime(uint32_t timeStep_ms);

    Sensor* GetPtrToSensor(int _sensorID);
    Actuator* GetPtrToActuator(int _actuatorID);

    std::string GetName();
    
    float ErikGetSystemPos();
    float ErikGetSystemVel();

private:
    std::list<Actuator*> actuatorList;
    std::list<Sensor*> sensorList;
    PivotPoint pivotPoint;

    std::string name;

    float erikVel = 5;
    float erikPos = 0;
};

#endif 

// --- End of File ---