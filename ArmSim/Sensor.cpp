#include "Sensor.h"

Sensor::Sensor(int _sensor_ID)
{
	this->sensor_ID = _sensor_ID;
	//TODO: add check against existing sensor_IDs
}

Units::Unit Sensor::getUnit()
{
	return this->unit;
}

// --- End of File ---