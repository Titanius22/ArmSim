#ifndef COMMAND_PLATFORM_H
#define COMMAND_PLATFORM_H

// include
#include <stdint.h>

class Command_Platform
{
public:
    enum class CommanndType : uint8_t {
        DO_NOTHING = 0,
        CHANGE_ACTUATOR_VALUE = 1
    };

    const static int COMMAND_SIZE_BYTES = (2 * 32) / 8;
    
    // Big four
    Command_Platform() = delete; // We must call the special constructor
    ~Command_Platform() = default;
    Command_Platform(const Command_Platform&) = default;
    Command_Platform& operator = (const Command_Platform&) = default;
    
    // Custom Constructors
    Command_Platform(void* _binCmd); // create from binary
    Command_Platform(CommanndType _cmdType); // DO_NOTHING
    Command_Platform(CommanndType _cmdType, uint8_t _actuator_ID, double _actuatorValue); // CHANGE_ACTUATOR_VALUE

    CommanndType GetCommandType() const;
    uint8_t GetActuatorID() const;
    double GetActuatorValue() const;

    const void* GetCommandBits() const;

private:
     
    uint8_t binCmd[COMMAND_SIZE_BYTES];
    /*
    First 32 bits
    ((uint8_t) binCmd)[0] => CommanndType
    ((uint8_t) binCmd)[1] => Actuator_ID
    ((uint8_t) binCmd)[2] => blank
    ((uint8_t) binCmd)[3] => blank
    
    Second 32 bits
    ((double) binCmd)[1] => ActuatorValue
    */

    void setCommandType(Command_Platform::CommanndType _cmdType);
    void setActuatorID(uint8_t _actuator_ID);
    void setActuatorValue(double _actuatorValue);
};

#endif 

// --- End of File ---