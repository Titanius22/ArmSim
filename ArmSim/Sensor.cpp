#include "Platform.h"
#include <string>

Sensor::Sensor(Platform* _ptrPlatform, int _sensor_ID, std::string _name, SensorSource _source):
	Device(Device::DeviceType::SENSOR)
{
	this->ptrPlatform = _ptrPlatform;
	this->sensor_ID = _sensor_ID;
	//TODO: add check against existing sensor_IDs

	this->name = _name;

	this->source = _source;
	this->unit = Units::Unit::Undefined;
}

Sensor::~Sensor()
{

}

std::string Sensor::GetName()
{
	return this->name;
}

int Sensor::getSensorID()
{
	return this->sensor_ID;
}

Units::Unit Sensor::GetUnit()
{
	return this->unit;
}

Sensor::SensorSource Sensor::GetSensorSource()
{
	return this->source;
}

// --- End of File ---