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
        //double _posX, double _posY, double _posZ,
        double _forceVecX, double _forceVecY, double _forceVecZ);

    //double getRealActuationValue() override; // will use once Actuator is an abstract class again
    double getRealActuationValue();

private:
    double forceVecX, forceVecY, forceVecZ;
};

#endif 

// --- End of File ---