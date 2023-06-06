#include "Actuator.h"


Actuator::Actuator(
    Platform* _ptrPlatform, uint8_t _actuator_ID, ActuatorType _actuatorType,
    float _posX, float _posY, float _posZ)
{
    this->ptrPlatform = _ptrPlatform;
    this->actuator_ID = _actuator_ID;
    //TODO: add check against existing actuator_IDs

    this->actuatorType = _actuatorType;

    this->posX = _posX;
    this->posY = _posY;
    this->posZ = _posZ;

    this->actuationValue = 0.0f;
    this->unit = Units::Unit::Undefined;
}

Actuator::~Actuator()
{

}

float Actuator::getCommandedActuationValue()
{
    return this->actuationValue;
}

void Actuator::setCommandedActuationValue(float newVal)
{
    this->actuationValue = newVal;
}

uint8_t Actuator::getActuatorID()
{
    return this->actuator_ID;
}

Units::Unit Actuator::getUnit()
{
    return this->unit;
}