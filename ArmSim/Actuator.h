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
        float _posX, float _posY, float _posZ
    );

    float getCommandedActuationValue();
    void setCommandedActuationValue(float newVal);
    virtual float getRealActuationValue() = 0;
    
    uint8_t getActuatorID();
    std::string GetName();
    Units::Unit getUnit();

protected:
    Platform* ptrPlatform;
    uint8_t actuator_ID;
    ActuatorType actuatorType;
    
    float posX, posY, posZ;
    std::string name;

    float actuationValue; // maps to Command_Platform data
    Units::Unit unit;
    
};

#endif 

// --- End of File ---