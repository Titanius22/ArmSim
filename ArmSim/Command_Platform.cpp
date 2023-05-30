#include "Command_Platform.h"
#include <cstring>

////////////////////////////////////////
// Public
////////////////////////////////////////

Command_Platform::Command_Platform(void* _binCmd)
{
	std::memcpy(&binCmd, _binCmd, COMMAND_SIZE_BYTES);
}

Command_Platform::Command_Platform(CommanndType _cmdType) // DO_NOTHING command
{	
	this->setCommandType(_cmdType);
}

Command_Platform::Command_Platform(CommanndType _cmdType, uint8_t _actuator_ID, float _actuatorValue) // CHANGE_ACTUATOR_VALUE command
{
	this->setCommandType(_cmdType);
	this->setActuatorID(_actuator_ID);
	this->setActuatorValue(_actuatorValue);
}

Command_Platform::CommanndType Command_Platform::GetCommandType() const
{
	uint8_t* pData = (uint8_t*)this->binCmd;

	return (Command_Platform::CommanndType)pData[0];
}

uint8_t Command_Platform::GetActuatorID() const
{
	uint8_t* pData = (uint8_t*)this->binCmd;

	return pData[1];
}

float Command_Platform::GetActuatorValue() const
{
	float* pData = (float*)this->binCmd;

	return pData[1];
}

const void* Command_Platform::GetCommandBits() const
{
	return this->binCmd;
}

////////////////////////////////////////
// Private
////////////////////////////////////////
void Command_Platform::setCommandType(Command_Platform::CommanndType _cmdType)
{
	uint8_t* pData = (uint8_t*)this->binCmd;
	
	pData[0] = (uint8_t)_cmdType;
}

void Command_Platform::setActuatorID(uint8_t _actuator_ID)
{
	uint8_t* pData = (uint8_t*)this->binCmd;

	pData[1] = (uint8_t)_actuator_ID;
}

void Command_Platform::setActuatorValue(float _actuatorValue)
{
	float* pData = (float*)this->binCmd;

	pData[1] = _actuatorValue;
}

// --- End of File ---