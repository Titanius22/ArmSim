#include "GuidNavCtrl.h"

#include <cmath>
#include "Sensor_Actuator.h"
#include "Sensor_SystemProperties.h"
#include "Platform.h"
#include "MathPhysics.h"

GuidNavCtrl::GuidNavCtrl(Platform* _platform):
	pPlatform(_platform)
{

}

GuidNavCtrl::~GuidNavCtrl()
{

}

void GuidNavCtrl::Initialize()
{
	// iterator over all the sensors, pick the ones GNC wants
	std::list<Sensor*> platSensorList = this->pPlatform->GetSensorList();
	for (Sensor* pSensor : platSensorList) {
		if (pSensor->GetSensorSource() == Sensor::SensorSource::SYSTEM_PROPERTY)
		{
			// switch statements 
			switch (((Sensor_SystemProperties*)pSensor)->GetPropertyToMeasure()) {
			case Platform::System_Property::ANG_POS:
				this->sensorMap[GuidNavCtrl::GncSensorMapping::SystemTheta] = pSensor;
				break;
			case Platform::System_Property::ANG_VEL:
				this->sensorMap[GuidNavCtrl::GncSensorMapping::SystemOmega] = pSensor;
				break;
			case Platform::System_Property::ANG_ACC:
				this->sensorMap[GuidNavCtrl::GncSensorMapping::SystemAlpha] = pSensor;
				break;
			case Platform::System_Property::MoreStuff:
			case Platform::System_Property::OtherStuff:
			default:
				assert(false);
				break;
			}
		}
		else if (pSensor->GetSensorSource() == Sensor::SensorSource::ACTUATOR)
		{
			if (this->sensorMap.find(GuidNavCtrl::GncSensorMapping::SystemActuator_Main) != this->sensorMap.end()) {
				// already exists. code not set up for more than 1 actuator
				assert(false);
			}
			this->sensorMap[GuidNavCtrl::GncSensorMapping::SystemActuator_Main] = pSensor;
		}
		else
		{
			assert(false);
		}

		// TODO: maybe don't need this any more
		this->sensorList.push_back(pSensor);
	}

	// iterator over all the actuators, pick the ones GNC wants
	std::list<Actuator*> platActuatorList = this->pPlatform->GetActuatorList();
	for (Actuator* pActuator : platActuatorList) {

		if (this->actuatorMap.find(GuidNavCtrl::GncActuatorMapping::SystemActuator_Main) != this->actuatorMap.end()) {
			// already exists. code not set up for more than 1 actuator
			assert(false);
		}
		this->actuatorMap[GuidNavCtrl::GncActuatorMapping::SystemActuator_Main] = pActuator;

		// TODO: maybe don't need this any more
		this->actuatorList.push_back(pActuator);
	}

	this->gncInialized = true;
	this->pPlatform->MarkThatGncHasInitialized();
}

void GuidNavCtrl::SolveAndApplyNextSolution()
{
	double maxLimit = MathPhysics::DegToRad(-80);
	double minLimit = MathPhysics::DegToRad(-100);

	double theta = this->sensorMap[GuidNavCtrl::GncSensorMapping::SystemTheta]->getSensorMeasurement();
	
	if ((theta > minLimit) && (theta < maxLimit))
	{
		double omega = this->sensorMap[GuidNavCtrl::GncSensorMapping::SystemOmega]->getSensorMeasurement();
		int directionSign = 0;
		if (std::signbit(omega)) // negative number; counterclockwise
		{
			directionSign = -1;
		}
		else if (std::signbit(omega)) // positive number; clockwise
		{
			directionSign = 1;
		}
		// else exactly zero
		directionSign *= -1;  // Want the force to be opposite of vel to slow it down

		this->actuatorMap[GuidNavCtrl::GncActuatorMapping::SystemActuator_Main]->setCommandedActuationValue(directionSign * 5);
	}
}
