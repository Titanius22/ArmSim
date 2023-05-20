#ifndef SENSOR_SYSTEMPROPERTIES_H
#define SENSOR_SYSTEMPROPERTIES_H

#include "Platform.h"
#include "Sensor.h"
#include <functional>

#include "TypeDefs.h"


class Sensor_SystemProperties : public Sensor
{
public:
    Sensor_SystemProperties(Platform* _ptrPlatform, int _sensor_ID, Platform::System_Property _propertyToMeasure, ptrToPlatformMethod funcPtr);

    double getSensorMeasurement() override;
    double getRealValue() override;

private:
    Platform::System_Property propertyToMeasure;
    ptrToPlatformMethod ptrToPlatformMethodThatGetsSystemProperty;
};

#endif 

// --- End of File ---