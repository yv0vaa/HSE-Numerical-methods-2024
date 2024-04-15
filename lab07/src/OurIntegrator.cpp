#include <iostream>
#include <cmath>
#include <cstring>
#include <numbers>
#include "../include/Observer.hpp"
#include "../include/TimeStepper.hpp"
#include "../include/ODEIntegrator.hpp"
#include "../include/RHS.hpp"
#include "../../lab06/include/u_derivative.hpp"

constexpr static int N = 4;

double degrees_to_radians(double alpha) {
    return alpha * (std::numbers::pi_v<double> / 180.0);
}

int main() {
    int best_alpha = 0;
    double best_range = 0.0;
    for (int degrees = 40; degrees <= 60; degrees++) {
        double v_0 = 1640.0;
        double alpha = degrees_to_radians(degrees);
        double t_start = 0.0;
        double t_finish = 1000.0;
        double h = 1e-6;
        double y[N] = {0.0, v_0 * std::cos(alpha), 0.0, v_0 * std::sin(alpha)};
        double y_end[N];
        double epsabs = 1e-6;
        double tau = 1e-2;
        Observer observer_instance(ObserveMethod::CheckMaxRange);
        RHS rhs;
        TimeStepper_RKF45<RHS> stepper(&rhs);
        ODE_Integrator<TimeStepper_RKF45<RHS>, Observer> integrator(&stepper, &observer_instance,h);
        integrator(t_start, y, t_finish, y_end);
        std::cout << "For α = " << degrees << "° max range is " << y[0] << "m\n";
        if (best_range < y[0]) {
            best_alpha = degrees;
            best_range = y[0];
        }
    }
    std::cout << "--------------------------------\n" << "Best angle was " << best_alpha << "° with range " << best_range << "m" << std::endl;    
}