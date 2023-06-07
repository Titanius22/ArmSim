#include "Sensor_SystemProperties.h"
#include <string>

Sensor_SystemProperties::Sensor_SystemProperties(
	Platform* _ptrPlatform, int _sensor_ID, std::string _name,
	Platform::System_Property _propertyToMeasure, 
	Type_PtrToPlatformMethod funcPtr
) : 
	Sensor(_ptrPlatform, _sensor_ID, _name, 
	SensorSource::SYSTEM_PROPERTY), 
	propertyToMeasure(_propertyToMeasure)
{
	this->ptrToPlatformMethodThatGetsSystemProperty = funcPtr;
}

float Sensor_SystemProperties::getSensorMeasurement()
{
	// TODO: add latency, accuracy, etc...
	return getRealValue();
}

float Sensor_SystemProperties::getRealValue()
{
	return (*(this->ptrPlatform).*(this->ptrToPlatformMethodThatGetsSystemProperty))();
}