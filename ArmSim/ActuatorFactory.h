#ifndef ACTUATORFACTORY_H
#define ACTUATORFACTORY_H

#include "Platform.h"

class ActuatorFactory
{
public:
    ActuatorFactory() = delete;
    ActuatorFactory(Platform* _platform);

    void CreateActuator_AndAddToPlatform( // Actuator_Linear
        int _actuator_ID,
        double _posX, double _posY, double _posZ,
        double _forceVecX, double _forceVecY, double _forceVecZ);

private:    
    Platform* ptrPlatform;
};

#endif 

// --- End of File ---