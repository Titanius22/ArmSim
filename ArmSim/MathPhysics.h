#ifndef MATHPHYSICS_H
#define MATHPHYSICS_H

class MathPhysics
{
public:
	MathPhysics() = delete;

	static double const pi;
	static double const g;

	static double RadToDeg(double inputRad);
	static double DegToRad(double inputDeg);

	static double CalaculatePotentialEnergy(double m, double h);
	static double CalaculateKineticEnergy(double m, double v);
	static double CalaculateV_viaEnergy(double totalEnergy, double potentialEnergy, double m);
};

#endif 