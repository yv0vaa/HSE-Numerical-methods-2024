#include <cmath>
#include <numbers>
#include "Analytical.hpp"
#include "Numerical.hpp"

template <typename F> 
F Exp(F x, int N, bool use_numerical_a_k) {
    F sum = use_numerical_a_k ? numerical_a_k(0, N) / 2 : analytical_a_k(0) / 2;
    for (int k = 1; k <= N; k++) {
        F a_k = use_numerical_a_k ? numerical_a_k(k, N) : analytical_a_k(k);
        sum += a_k * std::cos(static_cast<F>(k) * x);
    }
    return sum;
}

// Recommended N is at least 500!