#include "../include/Analytical.hpp"
long double analytical_a_k(int k) {
    long double exp_pi = (k % 2 == 0) ? std::exp(std::numbers::pi_v<long double>) : -std::exp(std::numbers::pi_v<long double>);
    return 2 * (exp_pi - 1) / (static_cast<double>(k * k + 1) * std::numbers::pi_v<long double>);
}
