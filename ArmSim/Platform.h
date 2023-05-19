#ifndef PLATFORM_H
#define PLATFORM_H

// include
#include <list>
//#include "Sensor.h"
#include "Actuator.h"
#include "PivotPoint.h"

class Sensor;

class Platform
{
public:
    enum System_Property {
        ARM_ANGLE,
        OtherStuff,
        MoreStuff
    };
    
    Platform();

    void AddActuator(Actuator* a);
    void AddSensor(Sensor* s);

    void PropagateModelDeltaTime(double timeStepSeconds);

private:
    std::list<Actuator*> actuatorList;
    std::list<Sensor*> sensorList;
    PivotPoint pivotPoint;
};

#endif 

// --- End of File ---