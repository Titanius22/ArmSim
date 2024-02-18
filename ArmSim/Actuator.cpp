#include "Actuator.h"
#include <string>


Actuator::Actuator(
    Platform* _ptrPlatform, uint8_t _actuator_ID, std::string _name,
    ActuatorType _actuatorType,
    double _posOnArm) :
    Device(Device::DeviceType::ACTUATOR)
{
    this->ptrPlatform = _ptrPlatform;
    this->actuator_ID = _actuator_ID;
    //TODO: add check against existing actuator_IDs
    this->name = _name;

    this->actuatorType = _actuatorType;

    this->posOnArm = _posOnArm;
    //this->posX = _posX;
    //this->posY = _posY;
    //this->posZ = _posZ;

    this->actuationValue = 0.0f;
    this->unit = Units::Unit::Undefined;
}

Actuator::~Actuator()
{

}

// TODO: make this class virtual and have specialized classes for each type of actuator. This function should be defined by the specialized class, not here.
double Actuator::getRealActuationValue()
{
    return this->actuationValue;
}

double Actuator::getCommandedActuationValue()
{
    return this->actuationValue;
}

void Actuator::setCommandedActuationValue(double newVal)
{
    this->actuationValue = newVal;
}

uint8_t Actuator::getActuatorID()
{
    return this->actuator_ID;
}

std::string Actuator::GetName()
{
    return this->name;
}

Units::Unit Actuator::GetUnit()
{
    return this->unit;
}

double Actuator::getPosOnArm()
{
    return this->posOnArm;
}