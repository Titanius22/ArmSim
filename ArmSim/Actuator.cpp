#include "Actuator.h"


Actuator::Actuator(
    Platform* _ptrPlatform, int _actuator_ID, ActuatorType _actuatorType,
    double _posX, double _posY, double _posZ)
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

double Actuator::getCommandedActuationValue()
{
    return this->actuationValue;
}

void Actuator::setCommandedActuationValue(double newVal)
{
    this->actuationValue = newVal;
}

int Actuator::getActuatorID()
{
    return this->actuator_ID;
}

Units::Unit Actuator::getUnit()
{
    return this->unit;
}