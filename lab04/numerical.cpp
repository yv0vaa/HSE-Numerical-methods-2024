#include <cmath>
#include <math.h>
#include <numbers>
#include <iomanip>
#include <iostream>
#include <string>

int N = 5;

long double no_cos_x_i(int i) {
    return ((2 * i - 1) * std::numbers::pi_v<long double>) / (2 * (N + 1));
}

long double numerical_a_k(int k) {
    long double sum = 0.0;
    for (int i = 1; i <= N + 1; i++) {
        long double x_i = no_cos_x_i(i);
        sum += std::exp(x_i) * T_k(std::cos(x_i), k);
    }
    return 2 / (N + 1) * sum;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        N = std::stoi(argv[1]);
    }

}