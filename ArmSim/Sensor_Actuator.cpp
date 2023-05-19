#include "Sensor_Actuator.h"

// for Actuator
Sensor_Actuator::Sensor_Actuator(int _sensor_ID, Actuator& aPtr)
	: Sensor(_sensor_ID), ptrActuator(aPtr)
{
	this->source = SensorSource::ACTUATOR;

}

double Sensor_Actuator::getSensorMeasurement()
{
	// TODO: add latency, accuracy, etc...
	return this->ptrActuator.getRealValue();
}

double Sensor_Actuator::getRealValue()
{
	return this->ptrActuator.getRealValue();
}