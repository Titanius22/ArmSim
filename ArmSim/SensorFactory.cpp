#include "SensorFactory.h"
#include "Sensor_Actuator.h"
#include "Sensor_SystemProperties.h"
#include <string>

SensorFactory::SensorFactory(Platform* _platform)
	: ptrPlatform(_platform)
{

}

void SensorFactory::CreateSensor_AndAddToPlatform(int _sensor_ID, std::string _name, Actuator* aPtr)
{
	Sensor* newSensor = new Sensor_Actuator(this->ptrPlatform, _sensor_ID, _name, aPtr);
	
	this->ptrPlatform->AddSensor(newSensor);
}

void SensorFactory::CreateSensor_AndAddToPlatform(int _sensor_ID, std::string _name, Platform::System_Property _propertyToMeasure)
{
	Type_PtrToPlatformMethod funcPtrToReturn = this->get_PtrToFuncThatGetsSystemProperty(_propertyToMeasure);
	
	Sensor* newSensor = new Sensor_SystemProperties(this->ptrPlatform, _sensor_ID, _name, _propertyToMeasure, funcPtrToReturn);
	
	this->ptrPlatform->AddSensor(newSensor);
}

Type_PtrToPlatformMethod SensorFactory::get_PtrToFuncThatGetsSystemProperty(Platform::System_Property _propertyToMeasure)
{
	// TODO: need to make return type better
	
	float (Platform::*funcPtrToReturn)(void);

	switch (_propertyToMeasure) {
		case Platform::System_Property::ANG_POS:
			funcPtrToReturn = &Platform::GetSystemPos;
			break;
		case Platform::System_Property::ANG_VEL:
			funcPtrToReturn = &Platform::GetSystemVel;
			break;
		case Platform::System_Property::ANG_ACC:
			funcPtrToReturn = &Platform::GetSystemAcc;
			break;
		case Platform::System_Property::OtherStuff:
		case Platform::System_Property::MoreStuff:
		default:
			funcPtrToReturn = NULL;
			assert(false);
	}

	return funcPtrToReturn;
}