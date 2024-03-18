// #include "../include/Pressure.hpp"
#include "../include/CD.hpp"
#include "../include/u_derivative.hpp"
#include <iostream>

int main() {
    double u[4] = {10000, 1160, 100000, 1160};
    double *p = u;
    double *derivative = u_derivative(p);
}
