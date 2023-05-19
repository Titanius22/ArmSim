#ifndef SIMMANAGER_H
#define SIMMANAGER_H

// include
#include "Platform.h"

class SimManager
{
private:
    float timeStep;
    Platform* platform;

public:
    SimManager();
    void Configure();
    void StartRun();
};

#endif 

// --- End of File ---