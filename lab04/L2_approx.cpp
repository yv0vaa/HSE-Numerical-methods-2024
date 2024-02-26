#include <cmath>
#include <math.h>
#include <numbers>
#include <iomanip>
#include <iostream>
#include <string>

long double numerical_a_k(int k, int N);
long double analytical_a_k(int k);

long double Exp(long double x, int N, bool use_numerical_a_k) {
    long double sum = use_numerical_a_k ? numerical_a_k(0, N) / 2 : analytical_a_k(0) / 2;
    for (int k = 1; k <= N; k++) {
        long double a_k = use_numerical_a_k ? numerical_a_k(k, N) : analytical_a_k(k);
        sum += a_k * std::cos(static_cast<long double>(k) * x);
    }
    return sum;
}

// Recommended N is at least 500!
int main(int argc, char** argv) {
    int N = 100;
    if (argc > 1) {
        N = std::stoi(argv[1]);
    }
    long double x = 0.5;
    std::cout << std::fixed << std::setprecision(40) << Exp(x, N, true) << std::endl;
}