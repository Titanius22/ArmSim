#include "Actuator_Linear.h"


Actuator_Linear::Actuator_Linear(
    Platform* _ptrPlatform, uint8_t _actuator_ID, ActuatorType _actuatorType,
    float _posX, float _posY, float _posZ,
    float _forceVecX, float _forceVecY, float _forceVecZ
) :
    Actuator(_ptrPlatform, _actuator_ID, _actuatorType, _posX, _posY, _posZ),
    forceVecX(_forceVecX), forceVecY(_forceVecY), forceVecZ(_forceVecZ)
{
    
}

float Actuator_Linear::getRealActuationValue()
{
    return this->actuationValue;
}