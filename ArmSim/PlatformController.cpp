/*
	The Winsock2.h header file internally includes core elements from the Windows.h 
	header file, so there is not usually an #include line for the Windows.h header 
	file in Winsock applications.If an #include line is needed for the Windows.h header 
	file, this should be preceded with the #define WIN32_LEAN_AND_MEAN macro. For historical 
	reasons, the Windows.h header defaults to including the Winsock.h header file for 
	Windows Sockets 1.1. The declarations in the Winsock.h header file will conflict with 
	the declarations in the Winsock2.h header file required by Windows Sockets 2.0. The 
	WIN32_LEAN_AND_MEAN macro prevents the Winsock.h from being included by the Windows.h header.
*/
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif

//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
#include <stdio.h>

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