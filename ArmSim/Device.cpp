#include "Device.h"

Device::~Device()
{

}

Device::Device(DeviceType _deviceType)
	:deviceType(_deviceType)
{

}

Device::DeviceType Device::GetDeviceType()
{
	return Device::DeviceType::ACTUATOR;
}
