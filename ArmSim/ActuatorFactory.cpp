#include "ActuatorFactory.h"
#include "Actuator.h"
#include "Actuator_Linear.h"
#include <string>

ActuatorFactory::ActuatorFactory(Platform* _platform)
	: ptrPlatform(_platform)
{

}

void ActuatorFactory::CreateActuator_AndAddToPlatform(
	uint8_t _actuator_ID, std::string _name,
	float _posX, float _posY, float _posZ,
	float _forceVecX, float _forceVecY, float _forceVecZ)
{
	Actuator* newActuator = new Actuator_Linear(this->ptrPlatform, _actuator_ID, _name, Actuator::ActuatorType::JAB, _posX, _posY, _posZ, _forceVecX, _forceVecY, _forceVecZ);
	
	this->ptrPlatform->AddActuator(newActuator);
}