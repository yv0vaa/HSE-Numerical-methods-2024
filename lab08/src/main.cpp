#include <iostream>
#include <cmath>
#include <cstring>
#include <numbers>
#include "../include/Observer.hpp"
#include "../include/EverhartStepper.hpp"
#include "../include/ODEIntegrator.hpp"
#include "../include/RHS.hpp"

int main() {
    Observer observer_instance;
    RHS rhs;
    TimeStepperEverhart<RHS> stepper(&rhs, 1e-12);
    ODE_Integrator<TimeStepperEverhart<RHS>, Observer> integrator(&stepper, &observer_instance, 1.0);
    double r[] = {
        0.0,
        0.0,
        7500
    };
    double r_dot[] = {
        std::sqrt(398600.4 / 7500),
        0.0,
        0.0
    };
    double r_end[3], r_end_dot[3];
    integrator(0, r, r_dot, 3.1e7, r_end, r_end_dot);   
}