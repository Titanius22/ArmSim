#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H

// include
#include "Platform.h"
#include "Command_Platform.h"

class PlatformController
{
public:
    PlatformController() = delete; // We must call the special constructor
    PlatformController(Platform* _ptrPlatform);

    void ReceiveCommand(Command_Platform* _command);    

private:
     
    Platform* ptrPlatform;
    
};

#endif 

// --- End of File ---