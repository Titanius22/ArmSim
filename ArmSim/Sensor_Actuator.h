#ifndef SENSOR_ACTUATOR_H
#define SENSOR_ACTUATOR_H

#include "Actuator.h"
#include "Sensor.h"


class Sensor_Actuator : public Sensor
{
public:
    // for Actuator
    Sensor_Actuator(int _sensor_ID, Actuator& aPtr);

    double getSensorMeasurement();
    double getRealValue();


private:
    Actuator& ptrActuator;
};

#endif 

// --- End of File ---