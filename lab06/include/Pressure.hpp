#ifndef PRESSURE_HPP
#define PRESSURE_HPP

#include <cmath>

class Pressure {
	constexpr static double h0 = 0.0;
	constexpr static double h1 = 11000.0;
	constexpr static double h2 = 20000.0;
	constexpr static double h3 = 32000.0;
	constexpr static double r0 = 6.5 * 1e-3;
	constexpr static double r1 = 0.0;
	constexpr static double r2 = 1e-3;
	constexpr static double r3 = -2.8 * 1e-3;
	constexpr static double R = 287.0528;
	constexpr static double g = 9.80655;   
	constexpr static double p0 = 101325.0;
	constexpr static double T0 = 288.15;
	/*T1, T2, T3 and p1, p2, p3 will be computed "dynamically*/
public:
	double operator()(double height) const;
};

#endif