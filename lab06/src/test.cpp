#include "../include/u_derivative.hpp"
#include <iostream>

int main() {
    double u[4] = {10, 1160, 10, 1160};
    double *p = u;
    double *derivative = u_derivative(p);
}
