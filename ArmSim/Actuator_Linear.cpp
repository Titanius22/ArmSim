#include "Actuator_Linear.h"
#include <string>


Actuator_Linear::Actuator_Linear(
    Platform* _ptrPlatform, uint8_t _actuator_ID, std::string _name, ActuatorType _actuatorType,
    double _posX, double _posY, double _posZ,
    double _forceVecX, double _forceVecY, double _forceVecZ
) :
    Actuator(_ptrPlatform, _actuator_ID, _name, _actuatorType, _posX, _posY, _posZ),
    forceVecX(_forceVecX), forceVecY(_forceVecY), forceVecZ(_forceVecZ)
{
    
}

double Actuator_Linear::getRealActuationValue()
{
    return this->actuationValue;
}