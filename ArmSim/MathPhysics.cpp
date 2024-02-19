#include "MathPhysics.h"

const double MathPhysics::pi = 3.1415f;
const double MathPhysics::g = 9.81f;

double MathPhysics::RadToDeg(double inputRad)
{
	return (inputRad / (2 * pi)) * 360;
}

double MathPhysics::DegToRad(double inputDeg)
{
	return (inputDeg / 360) * (2*pi);
}

double MathPhysics::CalaculatePotentialEnergy(double m, double h)
{
	return m * g * h;
}

double MathPhysics::CalaculateKineticEnergy(double m, double v)
{
	return 0.5f * m * v * v;
}

double MathPhysics::CalaculateV_viaEnergy(double totalEnergy, double potentialEnergy, double m)
{
	double kineticEnergy = totalEnergy - potentialEnergy;
	double v = sqrt((2 * kineticEnergy) / m);
	
	return v;
}
