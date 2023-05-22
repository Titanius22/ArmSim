#ifndef ACTUATORFACTORY_H
#define ACTUATORFACTORY_H

#include "Platform.h"

class ActuatorFactory
{
public:
    ActuatorFactory() = delete;
    ActuatorFactory(Platform* _platform);

    void CreateActuator_AndAddToPlatform( // Actuator_Linear
        uint8_t _actuator_ID,
        float _posX, float _posY, float _posZ,
        float _forceVecX, float _forceVecY, float _forceVecZ);

private:    
    Platform* ptrPlatform;
};

#endif 

// --- End of File ---