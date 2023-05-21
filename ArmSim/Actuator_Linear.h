#ifndef ACTUATOR_LINEAR_H
#define ACTUATOR_LINEAR_H

// include
#include "Units.h"
#include "Actuator.h"


class Actuator_Linear : public Actuator
{
public:    
    Actuator_Linear() = delete;
    Actuator_Linear(
        Platform* _ptrPlatform, int _actuator_ID, ActuatorType _actuatorType,
        double _posX, double _posY, double _posZ,
        double _forceVecX, double _forceVecY, double _forceVecZ);

    double getRealActuationValue() override;

private:
    double forceVecX, forceVecY, forceVecZ;
};

#endif 

// --- End of File ---