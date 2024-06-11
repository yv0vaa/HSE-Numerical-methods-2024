#include <iostream>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_math.h>
#include <numbers>
#include "../include/Exp.hpp"


double integrand(double x, void *params) {
    int N = *(int *)params;
    double fx = static_cast<double>(Exp(static_cast<long double>(x), N, false));
    double gx = std::exp(x);
    return pow(fabs(fx - gx),  2);
}

// Max N that works for me is 1200
int main(int argc, char** argv) {
    int N = 100;
    if (argc > 1) N = std::stoi(argv[1]);

    const double a =  0.0;
    const double b =  std::numbers::pi;
    double result, error;

    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);

    gsl_function F;
    F.function = &integrand;
    F.params = &N;

    gsl_integration_qags(&F, a, b, 0, 1e-13, 1000, w, &result, &error);

    gsl_integration_workspace_free(w);

    std::cout << "Uniform norm on [0; pi]  ||std::exp - Exp|| = " << pow(result, 0.5) << " (± " << pow(error, 0.5) << ")" << std::endl;

    return  0;
}
