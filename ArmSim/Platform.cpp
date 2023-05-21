#include "Platform.h"

Platform::Platform()
{

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
	double timeStep_sec = timeStep_ms * 1000.0f;
	
	// sum the forces to calculate vel change
	double erikIsDumb_cantDoPhysics = 0;
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



double Platform::ErikGetSystemPos()
{
	return this->erikPos;
}

double Platform::ErikGetSystemVel()
{
	return this->erikVel;
}