#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H

// include
#include "Platform.h"
#include "Command_Platform.h"

#include <winsock2.h>

class PlatformController
{
public:
    PlatformController() = delete; // We must call the special constructor
    PlatformController(Platform* _ptrPlatform);
    ~PlatformController();

    void ReceiveCommand(Command_Platform* _command);
    int HandleCommands();

private:
     
    int StartServer();
    int ShutdownServer();

    Platform* ptrPlatform;
    SOCKET ClientSocket;
};

#endif 

// --- End of File ---