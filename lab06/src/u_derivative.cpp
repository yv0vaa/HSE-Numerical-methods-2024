#include "../include/u_derivative.hpp"
#include "../include/Dencity.hpp"
#include "../include/CD.hpp"
#include <cmath>
#include <iostream>

#define _USE_MATH_DEFINES

constexpr static double m = 106;
constexpr static double d = 0.216;
constexpr static double pi = M_PI;
constexpr static double g = 9.80655;   

double *u_derivative(const double *u) {
    Density density_instance;
    CD CD_instance;

    double x = u[0];
    double v_x = u[1];
    double y = u[2];
    double v_y = u[3];

    double v = sqrt(v_x * v_x + v_y * v_y);
    double A = sqrt(density_instance.pressure(y) / density_instance(y));
    double M = v / A;

    double S = pi * d * d / 4.0;

    double Q = CD_instance(M) * density_instance(y) * (v * v / 2.0) * S;

    double *derivative = new double[4];
    derivative[0] = v_x;
    derivative[1] = -Q * (v_x / v) / m;
    derivative[2] = v_y;
    derivative[3] = -(Q * (v_y / v) / m) - g;
    return derivative;
}