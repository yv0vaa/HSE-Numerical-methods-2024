#include "../include/u_derivative.hpp"
#include "../include/Dencity.hpp"
#include "../include/CD.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

constexpr static double m = 106;

constexpr static double d = 0.216;

constexpr static double pi = M_PI;

constexpr static double g = 9.80655;   

double *u_derivative(double *u) {
    Density density_instance;
    CD CD_instance;
    double y = u[2];
    double S = pi * d * d / 4;
    static double ans_vector[4];
    double V = u[1] * u[1] + u[3] * u[3];
    V = sqrt(V);
    double A = density_instance.pressure(y) / density_instance(y);
    A = sqrt(A);
    double M = V / A;
    //std::cout << V << " " << A << " " << density_instance(y) << " " <<  density_instance.pressure(y) << "\n";
    //if u want to test(assert in CD.cpp is hidden so everything can launch)
    double Q = CD_instance(M) * density_instance(y) * V * V / 2 * S;
    ans_vector[0] = u[1];  // V_x
    ans_vector[2] = u[3];  // V_y
    ans_vector[1] = -Q * (u[1] / V) / m;
    ans_vector[3] = -Q * (u[3] / V) / m - g;
    return ans_vector;
}