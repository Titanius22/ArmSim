#include <string>
#include <cmath>
#include "Platform.h"
#include "MathPhysics.h"

Platform::Platform(std::string _name, double _armLength)
{
	this->name = _name;
	this->SetAngPos_Absolute(0);
	this->ang_vel = 0;

	this->armLength = _armLength;

	this->totalEnergy = GetKineticEnergy() + GetPotentialEnergy();
	this->ang_acc = CalaculateAngularAcceration(this->ang_pos, this->ang_vel);
}

void Platform::AddActuator(Actuator* ptr)
{
	assert(this->gncInialized == false); //setup error, stuff should not be added after GNC initialzes
	this->actuatorList.push_back(ptr);
}

void Platform::AddSensor(Sensor* ptr)
{
	assert(this->gncInialized == false); //setup error, stuff should not be added after GNC initialzes
	this->sensorList.push_back(ptr);
}

void Platform::PropagateModelDeltaTime(uint32_t timeStep_ms)
{
	double timeStep_sec = double(timeStep_ms) / 1000.0;

	this->RK4_StepForward(timeStep_sec);
}

Sensor* Platform::GetPtrToSensor(int _sensorID)
{
	Sensor* returnPtr = NULL;

	for (Sensor* sensor : this->sensorList) {
		if (_sensorID == sensor->getSensorID())
		{
			returnPtr = sensor;
			break;
		}
	}

	assert(returnPtr);
	return returnPtr;
}

Actuator* Platform::GetPtrToActuator(int _actuatorID)
{
	Actuator* returnPtr = NULL;

	for (auto const& actuator : this->actuatorList) {
		if (_actuatorID == actuator->getActuatorID())
		{
			returnPtr = actuator;
			break;
		}
	}

	assert(returnPtr);
	return returnPtr;
}

std::list<Sensor*> Platform::GetSensorList() const
{
	return this->sensorList;
}

std::list<Actuator*> Platform::GetActuatorList() const
{
	return this->actuatorList;
}

std::string Platform::GetName()
{
	return this->name;
}

double Platform::GetSystemPos()
{
	return this->ang_pos;
}

double Platform::GetSystemVel()
{
	return this->ang_vel;
}

double Platform::GetSystemAcc()
{
	return this->ang_acc;
}


double Platform::GetPotentialEnergy()
{
	assert(this->ang_pos <= (MathPhysics::pi/2));
	assert(this->ang_pos >= -(3/2 * MathPhysics::pi));
	double h = this->armLength * sin(this->ang_pos);

	return MathPhysics::CalaculatePotentialEnergy(m, h);
}

double Platform::GetKineticEnergy()
{
	return MathPhysics::CalaculateKineticEnergy(m, this->ang_vel * this->armLength);
}


void Platform::SetAngPos_Absolute(double newAngPos)
{
	const double minLimit = -(3.0f / 2.0f) * MathPhysics::pi;
	const double maxLimit = (1.0f / 2.0f) * MathPhysics::pi;

	double correctedVal = newAngPos;
	
	while ((correctedVal < minLimit) || (correctedVal > maxLimit))
	{
		if (correctedVal < minLimit)
		{
			correctedVal += (2.0f * MathPhysics::pi);
		}
		else if (correctedVal > maxLimit)
		{
			correctedVal -= (2.0f * MathPhysics::pi);
		}
		else
		{
			assert(false);
		}
	}

	this->ang_pos = correctedVal;
}

void Platform::SetAngPos_Add(double deltaAngPosToApply)
{
	SetAngPos_Absolute(this->ang_pos + deltaAngPosToApply);
}

double Platform::CalaculateAngularAcceration(double theta, double omega)
{
	// TODO: maybe change to calculate this once per cycle and save as a class variable
	double summedActuatorforceAtArmEnd = 0;
	double equivForceAtEnd = 0;
	double forceRatio = 0;

	for (auto const& actuator : this->actuatorList) {
		forceRatio = actuator->getPosOnArm() / this->armLength;
		equivForceAtEnd = forceRatio * actuator->getRealActuationValue();

		summedActuatorforceAtArmEnd += equivForceAtEnd;
	}

	// F = ma
	// sum force of system      =  gravity force     - dampening        +  external force
	// m*(l*alpha)              = -m*g*cos(theta)    - damp*(l*omega)   +  Actuator force

	// solve for acc; divide (m*l)
	// alpha                    = -(g/l)*cost(theta) - (damp*omega)/m   +  force_act/(m*l)

	return -((MathPhysics::g / this->armLength) * cos(theta)) + ((this->damping * -omega)/this->m) + (summedActuatorforceAtArmEnd/(this->m * this->armLength));
}

void Platform::RK4_StepForward(double dt)
{
	// see: https://gist.githubusercontent.com/Twinklebear/3935244/raw/2e96c1e4f7fae9362f3e77f15dc486ff5512035b/code.cpp
	
	double dtheta_k1 = this->ang_vel;
	double dw_k1 = CalaculateAngularAcceration(this->ang_pos, this->ang_vel);
	
	double dw_k2 = CalaculateAngularAcceration((this->ang_pos + (dtheta_k1*dt) / 2.0), (this->ang_vel + (dw_k1*dt) / 2.0));
	double dtheta_k2 = this->ang_vel + ((dw_k2 * dt) / 2.0);

	double dw_k3 = CalaculateAngularAcceration((this->ang_pos + (dtheta_k2 * dt) / 2.0), (this->ang_vel + (dw_k2 * dt) / 2.0));
	double dtheta_k3 = this->ang_vel + (dw_k3 * dt) / 2.0;
	
	double dw_k4 = CalaculateAngularAcceration((this->ang_pos + (dtheta_k3 * dt)), (this->ang_vel + (dw_k3 * dt)));
	double dtheta_k4 = this->ang_vel + (dw_k4 * dt);

	double dw = dt * (dw_k1 + (2 * dw_k2) + (2.0 * dw_k3) + dw_k4) / 6.0;
	double dtheta = dt * (dtheta_k1 + (2.0 * dtheta_k2) + (2.0 * dtheta_k3) + dtheta_k4) / 6.0;

	this->ang_vel += dw;
	this->SetAngPos_Add(dtheta);
	this->ang_acc = CalaculateAngularAcceration(this->ang_pos, this->ang_vel);
}

void Platform::MarkThatGncHasInitialized()
{
	this->gncInialized = true;
}