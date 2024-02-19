#ifndef GUIDNAVCTRL_H
#define GUIDNAVCTRL_H

#include <list>
#include <map>
#include "Sensor.h"
#include "Actuator.h"
#include "Platform.h"

class GuidNavCtrl
{
public:
	enum class GncSensorMapping {
		SystemTheta,
		SystemOmega,
		SystemAlpha,
		SystemActuator_Main
	};

	enum class GncActuatorMapping {
		SystemActuator_Main
	};

	GuidNavCtrl() = delete;
	GuidNavCtrl(Platform* _platform);
	~GuidNavCtrl();

	void Initialize();
	void SolveAndApplyNextSolution();

private:
	Platform* pPlatform;
	std::list<Sensor*> sensorList;
	std::map<GuidNavCtrl::GncSensorMapping, Sensor*> sensorMap;

	std::list<Actuator*> actuatorList;
	std::map<GuidNavCtrl::GncActuatorMapping, Actuator*> actuatorMap;

	bool gncInialized = false; // used to ensure that stuff doesn't get added to the plafrom after GNC is initialized


};

#endif 