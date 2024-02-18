#ifndef SENSOR_H
#define SENSOR_H

// include
#include <string>
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
    Sensor(Platform* _ptrPlatform, int _sensor_ID, std::string _name, SensorSource _source);
    virtual ~Sensor() = 0;

    virtual double getSensorMeasurement() = 0;
    virtual double getRealValue() = 0;
    
    int getSensorID();
    std::string GetName();
    Units::Unit getUnit();
    

protected:
     
    Platform* ptrPlatform;
    int sensor_ID;
    std::string name;
    SensorSource source;
    Units::Unit unit;
};

#endif 

// --- End of File ---