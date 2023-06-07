#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include "Sensor.h"
#include "Actuator.h"
#include "Platform.h"

#include "TypeDefs.h"

#include <string>


class SensorFactory
{
public:
    SensorFactory() = delete;
    SensorFactory(Platform* _platform);

    void CreateSensor_AndAddToPlatform(int _sensor_ID, std::string _name, Actuator* aPtr);
    void CreateSensor_AndAddToPlatform(int _sensor_ID, std::string _name, Platform::System_Property _propertyToMeasure);

private:
    Type_PtrToPlatformMethod get_PtrToFuncThatGetsSystemProperty(Platform::System_Property _propertyToMeasure);
    
    Platform* ptrPlatform;
};

#endif 

// --- End of File ---