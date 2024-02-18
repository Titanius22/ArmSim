#ifndef GROUNDCONTROL_H
#define GROUNDCONTROL_H

// include
#include <winsock2.h>
#include "../ArmSim/Command_Platform.h"

class GroundControl
{
public:
    GroundControl();
    ~GroundControl();
    
    void Start();
    
    int SetUpClient(const char* ipAdress);
    int UserCmdSending(Command_Platform* pCmd);
    int ShutDownClient();
   
    
private:
    SOCKET ConnectSocket;

};

#endif 

// --- End of File ---