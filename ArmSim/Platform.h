#ifndef PLATFORM_H
#define PLATFORM_H

// include
#include <list>
#include <string>
#include "Sensor.h"
#include "Actuator.h"
#include "PivotPoint.h"

//class Sensor;

class Platform
{

friend class SimManager;

public:
    enum class System_Property { // TODO: add units associated with the properties
        OtherStuff,
        MoreStuff,

        ANG_VEL,
        ANG_POS,
		ANG_ACC
    };
    
    Platform() = delete;
    Platform(std::string _name, double _armLength);

    void AddActuator(Actuator* a);
    void AddSensor(Sensor* s);
    Sensor* GetPtrToSensor(int _sensorID);
    Actuator* GetPtrToActuator(int _actuatorID);
    std::list<Sensor*> GetSensorList() const;
    std::list<Actuator*> GetActuatorList() const;

    void PropagateModelDeltaTime(uint32_t timeStep_ms);

    std::string GetName();
    double GetSystemPos();
    double GetSystemVel();
	double GetSystemAcc();
    
    void MarkThatGncHasInitialized();

private:
    std::list<Actuator*> actuatorList;
    std::list<Sensor*> sensorList;
    PivotPoint pivotPoint;

    std::string name;

    double ang_acc;
	double ang_pos;
	double ang_vel;
	
	double armLength;          // length of pendulum
    double const m = 1.0;      // mass
    double damping = 0;        // damping
    double force_actuator = 0; // force from an actuator

    double totalEnergy;
    double minPotentialEnergy;

    bool gncInialized = false; // used to ensure that stuff doesn't get added to the plafrom after GNC is initialized

    double GetPotentialEnergy();
    double GetKineticEnergy();
    void SetAngPos_Absolute(double newAngPos);
    void SetAngPos_Add(double deltaAngPosToApply);
    double CalaculateAngularAcceration(double theta, double omega);
    void RK4_StepForward(double dt);
};

#endif 

// --- End of File ---