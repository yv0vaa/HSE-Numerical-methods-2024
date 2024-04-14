#include <iostream>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include "../../lab06/include/u_derivative.hpp"
#include "../include/Observer.hpp"
#include <cmath>
#include <numbers>

constexpr static int N = 4;

double degrees_to_radians(double alpha) {
    return alpha * (std::numbers::pi_v<double> / 180.0);
}

int func(double t, const double y[], double f[], void *params) {
    double *y_derivative = u_derivative(y);
    f[0] = y_derivative[0];
    f[1] = y_derivative[1];
    f[2] = y_derivative[2];
    f[3] = y_derivative[3];
    return GSL_SUCCESS;
}

int main() {
    int best_alpha = 0, best_range = 0;
    for (int int_alpha = 40; int_alpha <= 60; int_alpha += 1) {
        double v_0 = 1640.0;
        double alpha = degrees_to_radians(int_alpha);
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
                break;
            }
            // std::cout << "At t = " << t << " x = " << y[0] << " y = " << y[2] << '\n';
        }
        gsl_odeiv2_driver_free(d);
        std::cout << "For α = " << int_alpha << "° max range is " << y[0] << "m\n";
        if (best_range < static_cast<int>(y[0])) {
            best_range = static_cast<int>(y[0]);
            best_alpha = int_alpha;
        }
    }
    std::cout << "--------------------------------\n" << "Best angle was " << best_alpha << "° with range " << best_range << "m" << std::endl;    
}