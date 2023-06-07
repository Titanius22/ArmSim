#include <string>
#include "Platform.h"

Platform::Platform(std::string _name)
{
	this->name = _name;
}

void Platform::AddActuator(Actuator* ptr)
{
	this->actuatorList.push_back(ptr);
}

void Platform::AddSensor(Sensor* ptr)
{
	this->sensorList.push_back(ptr);
}

void Platform::PropagateModelDeltaTime(uint32_t timeStep_ms)
{
	float timeStep_sec = float(timeStep_ms) / 1000.0f;
	
	// sum the forces to calculate vel change
	float erikIsDumb_cantDoPhysics = 0;
	for (Actuator* actuator : this->actuatorList) {
		erikIsDumb_cantDoPhysics += actuator->getCommandedActuationValue();
	}
	
	this->erikVel += (erikIsDumb_cantDoPhysics * timeStep_sec);

	this->erikPos += timeStep_sec * this->erikVel;
}

Sensor* Platform::GetPtrToSensor(int _sensorID)
{
	Sensor* returnPtr = NULL;

	for (Sensor* sensor : this->sensorList) {
		if (_sensorID == sensor->getSensorID())
		{
			returnPtr = sensor;
			break;
		}
	}

	assert(returnPtr);
	return returnPtr;
}

Actuator* Platform::GetPtrToActuator(int _actuatorID)
{
	Actuator* returnPtr = NULL;

	for (auto const& actuator : this->actuatorList) {
		if (_actuatorID == actuator->getActuatorID())
		{
			returnPtr = actuator;
			break;
		}
	}

	assert(returnPtr);
	return returnPtr;
}

std::string Platform::GetName()
{
	return this->name;
}

float Platform::ErikGetSystemPos()
{
	return this->erikPos;
}

float Platform::ErikGetSystemVel()
{
	return this->erikVel;
}