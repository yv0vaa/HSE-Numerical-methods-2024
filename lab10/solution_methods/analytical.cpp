#include <gsl/gsl_cdf.h>
#include <iostream>
#include <cmath>
#include "../include/Volatility.hpp"
#include "../include/RiskFreeInterestRate.hpp"

constexpr int K = 100;
constexpr int n = 500;
constexpr int S_tau_max = 0.9 * K;
constexpr int tau_max = 1;

double C(double a_S_tau_max, double a_tau_max) {
    Volatility sigma;
    RiskFreeInterestRate r;
    double V = sigma.integral_of_squared_from_zero_to(a_tau_max);
    double r_integral = r.integral_from_zero_to(a_tau_max);
    double d_plus = (std::log(a_S_tau_max / K) + r_integral + V / 2) / std::sqrt(V);
    double d_minus = (std::log(a_S_tau_max / K) + r_integral - V / 2) / std::sqrt(V);
    return a_S_tau_max * gsl_cdf_ugaussian_P(d_plus) - K * std::exp(-r_integral) * gsl_cdf_ugaussian_P(d_minus);
}

int main() {
    double res = C(S_tau_max, tau_max);
    std::cout << "Result: " << res << "\n";
    return 0;
}