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

void Platform::PropagateModelDeltaTime(double timeStepSeconds)
{
	this->erikPos += timeStepSeconds * this->erikVel;
}

double Platform::ErikGetSystemPos()
{
	return this->erikPos;
}

double Platform::ErikGetSystemVel()
{
	return this->erikVel;
}