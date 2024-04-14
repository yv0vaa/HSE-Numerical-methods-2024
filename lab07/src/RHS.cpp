#include "../include/RHS.hpp"
#include "../../lab06/include/u_derivative.hpp"

void RHS::operator()(double a_t, double a_y[N], double a_rhs[N]) const {
	//count u(t);
    double *u_deriv = u_derivative(a_y);
    for (int i = 0; i < RHS::N; i++) {
        a_rhs[i] = u_deriv[i];
    }
}
