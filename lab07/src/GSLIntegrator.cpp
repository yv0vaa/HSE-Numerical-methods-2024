#include <iostream>
#include <cmath>
#include <cstring>
#include <numbers>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include "../include/Observer.hpp"
#include "../../lab06/include/u_derivative.hpp"

constexpr static int N = 4;

double degrees_to_radians(double alpha) {
    return alpha * (std::numbers::pi_v<double> / 180.0);
}

int func(double t, const double y[], double f[], void *params) {
    memcpy(f, u_derivative(y), N * sizeof(y[0]));
    return GSL_SUCCESS;
}

int main() {
    int best_alpha = 0;
    double best_range = 0.0;
    for (int degrees = 40; degrees <= 60; degrees++) {
        double v_0 = 1640.0;
        double alpha = degrees_to_radians(degrees);
        double t = 0.0;
        double h = 1e-6;
        double y[N] = {0.0, v_0 * std::cos(alpha), 0.0, v_0 * std::sin(alpha)};
        double epsabs = 1e-6;
        double tau = 1e-2;

        gsl_odeiv2_system sys = {func, NULL, N, NULL};
        gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rkf45, h, epsabs, 0.0);

        Observer observer_instance(ObserveMethod::CheckMaxRange);
        while (observer_instance(t, N, y)) {
            double t_next = t + tau;
            int status = gsl_odeiv2_driver_apply(d, &t, t_next, y);
            if (status != GSL_SUCCESS) {
                std::cerr << "Error: " << gsl_strerror(status) << std::endl;
                exit(1);
            }
            // std::cout << "At t = " << t << " x = " << y[0] << " y = " << y[2] << '\n';
        }
    
        gsl_odeiv2_driver_free(d);

        std::cout << "For α = " << degrees << "° max range is " << y[0] << "m\n";
        if (best_range < y[0]) {
            best_alpha = degrees;
            best_range = y[0];
        }
    }
    std::cout << "--------------------------------\n" << "Best angle was " << best_alpha << "° with range " << best_range << "m" << std::endl;    
}