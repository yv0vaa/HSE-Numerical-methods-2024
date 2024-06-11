#include <cmath>
#include <numbers>
#include <iostream>
#include <gsl/gsl_fft_real.h>
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
F Exp_FFT(F x, int N, bool use_numerical_a_k) {
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
    
    for (int i = 0; i < N; i++) {
        sum += data[i];
    }

    gsl_fft_real_wavetable_free(real);
    gsl_fft_real_workspace_free(work);
    return sum;
}

// Recommended N is at least 500!
