#include "Platform.h"

Sensor::Sensor(Platform* _ptrPlatform, int _sensor_ID, SensorSource _source)
{
	this->ptrPlatform = _ptrPlatform;
	this->sensor_ID = _sensor_ID;
	//TODO: add check against existing sensor_IDs

	this->source = _source;
	this->unit = Units::Unit::Undefined;
}

Sensor::~Sensor()
{

}

int Sensor::getSensorID()
{
	return this->sensor_ID;
}

Units::Unit Sensor::getUnit()
{
	return this->unit;
}

// --- End of File ---