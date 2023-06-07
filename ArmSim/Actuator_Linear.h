#ifndef ACTUATOR_LINEAR_H
#define ACTUATOR_LINEAR_H

// include
#include "Units.h"
#include "Actuator.h"
#include <string>


class Actuator_Linear : public Actuator
{
public:    
    Actuator_Linear() = delete;
    Actuator_Linear(
        Platform* _ptrPlatform, uint8_t _actuator_ID, std::string _name, ActuatorType _actuatorType,
        float _posX, float _posY, float _posZ,
        float _forceVecX, float _forceVecY, float _forceVecZ);

    float getRealActuationValue() override;

private:
    float forceVecX, forceVecY, forceVecZ;
};

#endif 

// --- End of File ---