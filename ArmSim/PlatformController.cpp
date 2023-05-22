#include "PlatformController.h"
#include "Command_Platform.h"

PlatformController::PlatformController(Platform* _ptrPlatform)
{
	this->ptrPlatform = _ptrPlatform;
}

void PlatformController::ReceiveCommand(Command_Platform* command)
{
	Command_Platform::CommanndType commandType = command->GetCommandType();
	if (commandType == Command_Platform::CommanndType::DO_NOTHING)
	{
		// ... do nothing
	}
	else if(commandType == Command_Platform::CommanndType::CHANGE_ACTUATOR_VALUE)
	{
		uint8_t actuatorID = command->GetActuatorID();
		Actuator* pActuator = this->ptrPlatform->GetPtrToActuator(actuatorID);

		pActuator->setCommandedActuationValue(command->GetActuatorValue());

	}
	else
	{
		assert(false);
	}
}


// --- End of File ---