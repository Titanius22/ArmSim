#ifndef ACTUATOR_H
#define ACTUATOR_H

// include
//#include "Platform.h" //leave commented out to prevent circular references
#include "Units.h"

class Platform; // added to prevent circular references


class Actuator
{
public:
    enum class ActuatorType {
        JAB,
        HOOK,
        CROSS,
        KICK
    };
    
    Actuator() = delete; // We must call the special constructor
    Actuator(
        Platform* _ptrPlatform, int _actuator_ID, ActuatorType _actuatorType,
        double _posX, double _posY, double _posZ
    );

    double getCommandedActuationValue();
    void setCommandedActuationValue(double newVal);
    virtual double getRealActuationValue() = 0;
    
    int getActuatorID();
    Units::Unit getUnit();

protected:
    Platform* ptrPlatform;
    int actuator_ID;
    ActuatorType actuatorType;
    
    double posX, posY, posZ;

    double actuationValue;
    Units::Unit unit;
    
};

#endif 

// --- End of File ---