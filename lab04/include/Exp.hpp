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

template <typename F> 
F Exp_FFT(F gx,F x, int N, bool use_numerical_a_k) {
    F sum = use_numerical_a_k ? numerical_a_k(0, N) / 2 : analytical_a_k(0) / 2;
    double data[N];
    if (use_numerical_a_k) {
        for (int i = 0; i < N; i++) {
            data[i] = numerical_a_k(i, N);
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            data[i] = analytical_a_k(i);
        }
    }
    gsl_fft_real_wavetable *real;
    gsl_fft_real_workspace *work;
    work = gsl_fft_real_workspace_alloc(N);
    real = gsl_fft_real_wavetable_alloc(N);
    gsl_fft_real_transform(data, 1, N, real, work);
    gsl_fft_real_wavetable_free(real);
    for (int i = 0; i < N; i++) {
        data[i] += sum;
    }
    F minimal_difference = 1000.0;
    int ind_of_minimal_difference = 0;

    for (int i = 0; i < N; i++) {
        if (abs(data[i] - gx) < minimal_difference) {
            ind_of_minimal_difference = i;
            minimal_difference = abs(data[i] - gx);
        }
    }
    int ind = floor(x * (N + 1) / M_PI / 2);
    std::cout << "----------------" << std::endl;
    std::cout << minimal_difference << std::endl;
    std::cout << abs(data[ind]-x) << std::endl;
    std::cout << ind_of_minimal_difference << std::endl;
    std::cout << ind << std::endl;
    
    return data[ind_of_minimal_difference];
}

// Recommended N is at least 500!
