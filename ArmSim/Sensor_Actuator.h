#ifndef SENSOR_ACTUATOR_H
#define SENSOR_ACTUATOR_H

#include "Actuator.h"
#include "Sensor.h"
#include "Platform.h"
#include <string>

class Sensor_Actuator : public Sensor
{
public:
    //Sensor_Actuator() = default; // throws compiler error
    Sensor_Actuator(Platform* _ptrPlatform, int _sensor_ID, std::string _name, Actuator* aPtr);

    float getSensorMeasurement() override;
    float getRealValue() override;


private:
    Actuator* ptrActuator;
};

#endif 

// --- End of File ---