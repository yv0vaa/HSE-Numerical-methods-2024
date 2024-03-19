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

    double x = u[0];
    double v_x = u[1];
    double y = u[2];
    double v_y = u[3];

    double S = pi * d * d / 4.0;

    static double ans_vector[4];

    double v = sqrt(v_x * v_x + v_y * v_y);
    double A = sqrt(density_instance.pressure(y) / density_instance(y));
    double M = v / A;
    std::cout << "M=" << M << "\n"; // What to do with such big M?

    double Q = CD_instance(M) * density_instance(y) * v * v  * S / 2.0;
    ans_vector[0] = v_x;  
    ans_vector[1] = -Q * (v_x / v) / m;
    ans_vector[2] = v_y;
    ans_vector[3] = -(Q * (v_y / v) / m) - g;
    return ans_vector;
}