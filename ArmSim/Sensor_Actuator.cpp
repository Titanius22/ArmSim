#include "Sensor_Actuator.h"

// for Actuator
Sensor_Actuator::Sensor_Actuator(Platform* _ptrPlatform, int _sensor_ID, Actuator* aPtr)
	: Sensor(_ptrPlatform, _sensor_ID, SensorSource::ACTUATOR), ptrActuator(aPtr)
{

}

float Sensor_Actuator::getSensorMeasurement()
{
	// TODO: add latency, accuracy, etc...
	return this->ptrActuator->getRealActuationValue();
}

float Sensor_Actuator::getRealValue()
{
	return this->ptrActuator->getRealActuationValue();
}