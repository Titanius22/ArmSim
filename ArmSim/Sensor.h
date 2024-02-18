#ifndef SENSOR_H
#define SENSOR_H

// include
#include <string>
//#include "Platform.h" //leave commented out to prevent circular references
#include "Units.h"
#include "Device.h"

class Platform; // added to prevent circular references


class Sensor : public Device
{
    friend class SimManager;

public:
    enum class SensorSource {
        ACTUATOR,
        SYSTEM_PROPERTY
    };

    Sensor() = delete; // We must call the special constructor
    Sensor(Platform* _ptrPlatform, int _sensor_ID, std::string _name, SensorSource _source);
    virtual ~Sensor() = 0;

    virtual double getSensorMeasurement() = 0; // this is the measured value (after noise and latency)
    
    int getSensorID();
    std::string GetName() override;
    Units::Unit GetUnit() override;
    

protected:
     
    Platform* ptrPlatform;
    int sensor_ID;
    std::string name;
    SensorSource source;
    Units::Unit unit;

    virtual double getRealValue() = 0;  // TODO: figure out how to block everyone but the platform from accessing this
};

#endif 

// --- End of File ---