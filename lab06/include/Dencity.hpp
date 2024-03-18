#ifndef PRESSURE_HPP
#define PRESSURE_HPP

#include <cmath>

class Density {
	double temperature(double height) const;
	constexpr static double h[4] = {0.0, 11000.0, 20000.0, 32000.0};
	constexpr static double r[4] = {6.5 * 1e-3, 0.0, -1e-3, -2.8 * 1e-3};
	constexpr static double R = 287.0528;
	constexpr static double g = 9.80655;   
	double p[4] = {101325.0, 0, 0, 0};
	double T[4] = {288.15, 0, 0, 0};
public:
	double pressure(double height) const;
	Density() {
		for (int i = 1; i < 4; i++) {
			this->T[i] = this->temperature(this->h[i]);
			this->p[i] = this->pressure(this->h[i]);
		}
	}
	double operator()(double height) const;
};

#endif
