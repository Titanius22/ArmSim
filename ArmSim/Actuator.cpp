#include "Actuator.h"


Actuator::Actuator(
    int _actuator_ID,
    double _posX, double _posY, double _posZ,
    double _rotAxX, double _rotAxY, double _rotAxZ) :
    actuator_ID(_actuator_ID),
    posX(_posX), posY(_posY), posZ(_posZ), 
    rotAxX(_rotAxX), rotAxY(_rotAxY), rotAxZ(_rotAxZ)
{
    this->unit = Units::Unit::Undefined;
}

double Actuator::getRealValue()
{
    assert(false);
    return -1;
}

int Actuator::getActuatorID()
{
    return this->actuator_ID;
}

Units::Unit Actuator::getUnit()
{
    return this->unit;
}