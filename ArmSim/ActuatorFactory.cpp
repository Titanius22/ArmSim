#include "ActuatorFactory.h"
#include "Actuator.h"
#include "Actuator_Linear.h"

ActuatorFactory::ActuatorFactory(Platform* _platform)
	: ptrPlatform(_platform)
{

}

void ActuatorFactory::CreateActuator_AndAddToPlatform(
	int _actuator_ID,
	double _posX, double _posY, double _posZ,
	double _forceVecX, double _forceVecY, double _forceVecZ)
{
	Actuator* newActuator = new Actuator_Linear(this->ptrPlatform, _actuator_ID, Actuator::ActuatorType::JAB, _posX, _posY, _posZ, _forceVecX, _forceVecY, _forceVecZ);
	
	this->ptrPlatform->AddActuator(newActuator);
}