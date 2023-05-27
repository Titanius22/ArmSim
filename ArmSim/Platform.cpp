#include "Platform.h"

Platform::Platform()
{
	this->ang_pos = 0;
	this->ang_vel = 0;
	this->ang_acc = 0;

	this->l = 0.2f;
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
	/*float erikIsDumb_cantDoPhysics = 0;
	for (Actuator* actuator : this->actuatorList) {
		erikIsDumb_cantDoPhysics += actuator->getCommandedActuationValue();
	}
	
	this->erikVel += (erikIsDumb_cantDoPhysics * timeStep_sec);

	this->erikPos += timeStep_sec * this->erikVel;*/
	
	
	// WE HAVE
	this->ang_pos;
	this->ang_vel;
	this->ang_acc;
	

	// WE WANT
	float ang_pos_next;
	float ang_vel_next;
	
	
	// WE GET THAT BY.........
	ang_acc = -(g * cos(ang_pos)) / l;
	ang_vel_next = (ang_acc * timeStep_sec) + ang_vel;
	ang_pos_next = 0.5f * (ang_vel_next + ang_vel) * timeStep_sec;
	

	this->ang_pos = ang_pos_next;
	this->ang_vel = ang_vel_next;
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



float Platform::GetSystemPos()
{
	return this->ang_pos;
}

float Platform::GetSystemVel()
{
	return this->ang_vel;
}

float Platform::GetSystemAcc()
{
	return this->ang_acc;
}