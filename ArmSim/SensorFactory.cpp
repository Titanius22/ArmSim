#include "SensorFactory.h"
#include "Sensor_Actuator.h"
#include "Sensor_SystemProperties.h"

SensorFactory::SensorFactory(Platform* _platform)
	: ptrPlatform(_platform)
{

}

void SensorFactory::CreateSensorAndAddToPlatform(int _sensor_ID, Actuator& aPtr)
{
	Sensor* newSensor = new Sensor_Actuator(this->ptrPlatform, _sensor_ID, aPtr);
	
	this->ptrPlatform->AddSensor(newSensor);
}

void SensorFactory::CreateSensorAndAddToPlatform(int _sensor_ID, Platform::System_Property _propertyToMeasure)
{
	ptrToPlatformMethod funcPtrToReturn = this->get_PtrToFuncThatGetsSystemProperty(_propertyToMeasure);
	
	Sensor* newSensor = new Sensor_SystemProperties(this->ptrPlatform, _sensor_ID, _propertyToMeasure, funcPtrToReturn);
	
	this->ptrPlatform->AddSensor(newSensor);
}

ptrToPlatformMethod SensorFactory::get_PtrToFuncThatGetsSystemProperty(Platform::System_Property _propertyToMeasure)
{
	// TODO: need to make return type better
	
	//TODO: change to use the C++11 version.....std::function<double (int, int)> func
	double (Platform::*funcPtrToReturn)(void);

	switch (_propertyToMeasure) {
		case Platform::System_Property::ERIK_POS:
			funcPtrToReturn = &Platform::ErikGetSystemPos;
			break; //optional
		case Platform::System_Property::ERIK_VEL:
			funcPtrToReturn = &Platform::ErikGetSystemVel;
			break; //optional
		case Platform::System_Property::ARM_ANGLE:
		case Platform::System_Property::OtherStuff:
		case Platform::System_Property::MoreStuff:
		default: //Optional
			funcPtrToReturn = NULL;
			assert(false);
	}

	return funcPtrToReturn;
}