#ifndef SENSOR_H
#define SENSOR_H

// include
#include "Platform.h"
#include "Units.h"


class Sensor
{
public:
    enum SensorSource {
        ACTUATOR,
        SYSTEM_PROPERTY
    };
    
    ///////////////// for Actuator
    ////////////////Sensor(int _sensor_ID, Actuator& aPtr);

    //////////////// for System Property
    //////////////Sensor(int _sensor_ID, Platform::System_Property _systemProperty);

    Sensor() = delete; // We must call the special constructor
    Sensor(int _sensor_ID);

    virtual double getSensorMeasurement() = 0;
    virtual double getRealValue() = 0;
    virtual Units::Unit getUnit();
    
    
//    // for System Property
//Sensor::Sensor(int _sensor_ID, Platform::System_Property _systemProperty)
//{
//	this->source = SensorSource::SYSTEM_PROPERTY;
//}


protected:
     
    int sensor_ID;
    SensorSource source;
    Units::Unit unit;
    ///////////////////////////////////Platform::System_Property _systemProperty;
};

#endif 

// --- End of File ---