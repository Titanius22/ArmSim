#include "Actuator_Linear.h"


Actuator_Linear::Actuator_Linear(
    Platform* _ptrPlatform, int _actuator_ID, ActuatorType _actuatorType,
    double _posX, double _posY, double _posZ,
    double _forceVecX, double _forceVecY, double _forceVecZ
) :
    Actuator(_ptrPlatform, _actuator_ID, _actuatorType, _posX, _posY, _posZ),
    forceVecX(_forceVecX), forceVecY(_forceVecY), forceVecZ(_forceVecZ)
{
    
}

double Actuator_Linear::getRealActuationValue()
{
    return this->actuationValue;
}