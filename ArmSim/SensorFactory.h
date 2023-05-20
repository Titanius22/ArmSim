#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include "Sensor.h"
#include "Actuator.h"
#include "Platform.h"
#include <functional>

#include "TypeDefs.h"


class SensorFactory
{
public:
    SensorFactory() = delete;
    SensorFactory(Platform* _platform);

    Sensor* CreateSensor(int _sensor_ID, Actuator& aPtr);
    Sensor* CreateSensor(int _sensor_ID, Platform::System_Property _propertyToMeasure);

private:
    ptrToPlatformMethod get_PtrToFuncThatGetsSystemProperty(Platform::System_Property _propertyToMeasure);
    
    Platform* ptrPlatform;
};

#endif 

// --- End of File ---