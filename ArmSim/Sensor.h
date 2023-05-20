#ifndef SENSOR_H
#define SENSOR_H

// include
//#include "Platform.h" //leave commented out to prevent circular references
#include "Units.h"

class Platform; // added to prevent circular references

class Sensor
{
public:
    enum class SensorSource {
        ACTUATOR,
        SYSTEM_PROPERTY
    };

    Sensor() = delete; // We must call the special constructor
    Sensor(Platform* _ptrPlatform, int _sensor_ID, SensorSource _source);

    virtual double getSensorMeasurement() = 0;
    virtual double getRealValue() = 0;
    
    virtual int getSensorID();
    virtual Units::Unit getUnit();
    

protected:
     
    Platform* ptrPlatform;
    int sensor_ID;
    SensorSource source;
    Units::Unit unit;
};

#endif 

// --- End of File ---