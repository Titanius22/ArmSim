#ifndef ACTUATOR_H
#define ACTUATOR_H

// include
#include "Units.h"


class Actuator
{
public:
    Actuator() = delete;
    Actuator(
        int _actuator_ID,
        double _posX, double _posY, double _posZ,
        double _rotAxX, double _rotAxY, double _rotAxZ);

    double getRealValue();
    
    int getActuatorID();
    Units::Unit getUnit();

private:
    int actuator_ID;
    double posX, posY, posZ;
    double rotAxX, rotAxY, rotAxZ;
    Units::Unit unit;
    
};

#endif 

// --- End of File ---