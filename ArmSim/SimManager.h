#ifndef SIMMANAGER_H
#define SIMMANAGER_H

// include
#include <fstream>
#include <iostream>
#include "Platform.h"

class SimManager
{
private:
    uint32_t cycleTimeStep_ms;
    double currentSimTime;
    Platform* platform;
    std::ofstream exportFile;
    bool realTimeLive = false;

public:
    SimManager();
    void Configure();
    void StartRun();
    void ExportToFile(Platform* _platform);
};

#endif 

// --- End of File ---