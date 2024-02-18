#ifndef ACTUATOR_H
#define ACTUATOR_H

// include
//#include "Platform.h" //leave commented out to prevent circular references
#include "Units.h"
#include <string>
#include "Device.h"

class Platform; // added to prevent circular references


class Actuator : public Device
{

    friend class Platform;
    friend class SimManager;
    friend class Sensor_Actuator;

public:
    enum class ActuatorType {
        JAB,
        HOOK,
        CROSS,
        KICK
    };
    
    //virtual ~Actuator() = 0; // TODO: make this class virtual and have specialized classes for each type of actuator
    ~Actuator();
    Actuator() = delete; // We must call the special constructor
    Actuator(
        Platform* _ptrPlatform, uint8_t _actuator_ID, std::string _name, 
        ActuatorType _actuatorType,
        double _posOnArm
    );

    double getCommandedActuationValue(); // this is the measured value (after noise and latency)
    void setCommandedActuationValue(double newVal);
    
    
    uint8_t getActuatorID();
    double getPosOnArm();
    std::string GetName() override;
    Units::Unit GetUnit() override;

protected:
    Platform* ptrPlatform;
    uint8_t actuator_ID;
    ActuatorType actuatorType;
    
    double posOnArm; // measured starting at the pivot point with a min of 0;
    //double posX, posY, posZ;
    std::string name;

    double actuationValue; // maps to Command_Platform data; force measured in Newtons
    Units::Unit unit;
    
    //virtual double getRealActuationValue() = 0; // TODO: make this class virtual and have specialized classes for each type of actuator
    double getRealActuationValue(); // TODO: figure out how to block everyone but the platform from accessing this

};

#endif 

// --- End of File ---