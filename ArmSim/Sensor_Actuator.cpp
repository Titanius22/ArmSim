#include "Sensor_Actuator.h"
#include <string>

// for Actuator
Sensor_Actuator::Sensor_Actuator(Platform* _ptrPlatform, int _sensor_ID, std::string _name, Actuator* aPtr)
	: Sensor(_ptrPlatform, _sensor_ID, _name, SensorSource::ACTUATOR), ptrActuator(aPtr)
{

}

double Sensor_Actuator::getSensorMeasurement()
{
	// TODO: add latency, accuracy, etc...
	return this->ptrActuator->getRealActuationValue();
}

double Sensor_Actuator::getRealValue()
{
	return this->ptrActuator->getRealActuationValue();
}