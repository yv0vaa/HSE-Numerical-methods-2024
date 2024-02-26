#include <cmath>
#include <math.h>
#include <numbers>
#include <iomanip>
#include <iostream>

// Calculate analytically found a_k
long double analytical_a_k(int k) {
    long double exp_pi = (k % 2 == 0) ? 1 : -1 * std::exp(std::numbers::pi_v<long double>);
    // return 1 / static_cast<long double>(k * k + 1) * (exp_pi - 1);
    return 2 * (exp_pi - 1) / (static_cast<double>(k * k + 1) * std::numbers::pi_v<long double>);
}

int main() {
    std::cout << std::fixed << std::setprecision(40) << analytical_a_k(3) << std::endl;
    std::cout << "-1.536844224867568618148459569031990245179845747934621719083874918" << std::endl;
}