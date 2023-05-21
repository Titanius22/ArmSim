#include "Sensor_SystemProperties.h"

Sensor_SystemProperties::Sensor_SystemProperties(
	Platform* _ptrPlatform, int _sensor_ID, 
	Platform::System_Property _propertyToMeasure, 
	ptrToPlatformMethod funcPtr
) : 
	Sensor(_ptrPlatform, _sensor_ID, 
	SensorSource::SYSTEM_PROPERTY), 
	propertyToMeasure(_propertyToMeasure)
{
	this->ptrToPlatformMethodThatGetsSystemProperty = funcPtr;
}

double Sensor_SystemProperties::getSensorMeasurement()
{
	// TODO: add latency, accuracy, etc...
	return getRealValue();
}

double Sensor_SystemProperties::getRealValue()
{
	return (*(this->ptrPlatform).*(this->ptrToPlatformMethodThatGetsSystemProperty))();
}