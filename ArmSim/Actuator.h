#ifndef ACTUATOR_H
#define ACTUATOR_H

// include
//#include "Platform.h" //leave commented out to prevent circular references
#include "Units.h"
#include <string>

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
    
    virtual ~Actuator() = 0;
    Actuator() = delete; // We must call the special constructor
    Actuator(
        Platform* _ptrPlatform, uint8_t _actuator_ID, std::string _name, 
        ActuatorType _actuatorType,
        double _posX, double _posY, double _posZ
    );

    double getCommandedActuationValue();
    void setCommandedActuationValue(double newVal);
    virtual double getRealActuationValue() = 0;
    
    uint8_t getActuatorID();
    std::string GetName();
    Units::Unit getUnit();

protected:
    Platform* ptrPlatform;
    uint8_t actuator_ID;
    ActuatorType actuatorType;
    
    double posX, posY, posZ;
    std::string name;

    double actuationValue; // maps to Command_Platform data
    Units::Unit unit;
    
};

#endif 

// --- End of File ---