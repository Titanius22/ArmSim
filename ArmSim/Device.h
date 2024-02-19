#ifndef DEVICE_H
#define DEVICE_H

#include "Units.h"

class Device
{
public:
    enum class DeviceType {
        ACTUATOR,
        SENSOR,

        UNDEFINED
    };

    virtual ~Device() = 0;
    Device() = delete; // We must call the special constructor
    Device(DeviceType _deviceType);

    virtual std::string GetName() = 0;
    virtual DeviceType GetDeviceType() final;
    virtual Units::Unit GetUnit() = 0;

protected:
    DeviceType deviceType;
};

#endif 

