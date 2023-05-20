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
    enum class System_Property { // TODO: add units associated with the properties
        ARM_ANGLE,
        OtherStuff,
        MoreStuff,

        ERIK_VEL,
        ERIK_POS
    };
    
    Platform();

    void AddActuator(Actuator* a);
    void AddSensor(Sensor* s);

    void PropagateModelDeltaTime(double timeStepSeconds);

    double ErikGetSystemPos();
    double ErikGetSystemVel();

private:
    std::list<Actuator*> actuatorList;
    std::list<Sensor*> sensorList;
    PivotPoint pivotPoint;

    double erikVel = 5;
    double erikPos = 0;
};

#endif 

// --- End of File ---