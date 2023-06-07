#ifndef SENSOR_SYSTEMPROPERTIES_H
#define SENSOR_SYSTEMPROPERTIES_H

#include "Platform.h"
#include "Sensor.h"
#include <functional>
#include <string>

#include "TypeDefs.h"


class Sensor_SystemProperties : public Sensor
{
public:
    Sensor_SystemProperties(Platform* _ptrPlatform, int _sensor_ID, std::string _name, Platform::System_Property _propertyToMeasure, Type_PtrToPlatformMethod funcPtr);

    float getSensorMeasurement() override;
    float getRealValue() override;

private:
    Platform::System_Property propertyToMeasure;
    Type_PtrToPlatformMethod ptrToPlatformMethodThatGetsSystemProperty;
};

#endif 

// --- End of File ---