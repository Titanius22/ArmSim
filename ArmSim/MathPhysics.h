#pragma once
class MathPhysics
{
public:
	MathPhysics() = delete;

	static double const pi;
	static double const g;

	static double CalaculatePotentialEnergy(double m, double h);
	static double CalaculateKineticEnergy(double m, double v);
	static double CalaculateV_viaEnergy(double totalEnergy, double potentialEnergy, double m);
};