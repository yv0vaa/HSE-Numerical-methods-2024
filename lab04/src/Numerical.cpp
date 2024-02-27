#include "../include/Numerical.hpp"

long double T_k(long double x, int k) {
	long double t_0 = 1.0, t_1 = x;
	for (int i = 2; i <= k; i++) {
		long double cur = 2 * x * t_1 - t_0;
		t_0 = t_1;
		t_1 = cur;
	}
	return k == 0 ? t_0 : t_1;
}

long double no_cos_x_i(int i, int N) {
    return ((2 * i - 1) * std::numbers::pi_v<long double>) / (2 * (N + 1));;
}

long double numerical_a_k(int k, int N) {
    long double sum = 0.0;
    for (int i = 1; i <= N + 1; i++) {
        long double x_i = no_cos_x_i(i, N);
        long double T_k_x_i = T_k(std::cos(x_i), k);
        sum += std::exp(x_i) * T_k_x_i;
    }
    return  2 * sum / (N + 1);
}
