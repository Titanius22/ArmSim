#include "Sensor.h"

Sensor::Sensor(Platform* _ptrPlatform, int _sensor_ID, SensorSource _source)
{
	this->ptrPlatform = _ptrPlatform;
	this->sensor_ID = _sensor_ID;
	//TODO: add check against existing sensor_IDs

	this->source = _source;
	this->unit = Units::Unit::Undefined;
}

Units::Unit Sensor::getUnit()
{
	return this->unit;
}

// --- End of File ---