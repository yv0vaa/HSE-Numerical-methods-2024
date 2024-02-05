#ifndef EXP_HPP
#define EXP_HPP

#include "consts.hpp"
#include <assert.h>
#include <climits>
#include <cmath>
#include <iostream>
#include <type_traits>

namespace ADAAI {
template <typename F> constexpr inline int MkExpTaylorOrder() {
    F ln2_2 = Ln2<F> / 2, tail = sqrt2<F>, delta = Eps<F> * 10;
    for (int i = 1; i < 1000; ++i) {
        if (tail < delta)
            return i;
        tail = tail * ln2_2 / i;
    }
    assert(false);
}

enum class MethodE {
    Taylor,
    Pade
}; template <MethodE M = MethodE::Pade, typename F>
constexpr F Exp(F x) {
    static_assert(std::is_floating_point_v<F>);
    F n, y = std::modf(x / Ln2<F>, &n);
    if (y > 0.5 || y < -0.5) {
        if (y > 0) {
            n += 1;
            y -= 1;
        } else {
            n -= 1;
            y += 1;
        }
    }
    if (n < INT_MIN) {
        return 0.0;
    }
    if (n > INT_MAX) {
        return 1 / 0.0;
    }
    F x1 = y * Ln2<F>;
    if constexpr (M == MethodE::Taylor) {
        F delta = 10.0 * Eps<F>, f1 = 1.0,  k = 1.0;
        F cpy = x1;
        constexpr int N = MkExpTaylorOrder<F>();
        for (int i = 0; i < N; ++i) {
            f1 += x1;
            x1 *= cpy;
            k += 1;
            x1 /= k;
        }
        return std::ldexp(f1, static_cast<int>(n));
    } else {
        F denominator = 0.0, numerator =  0.0;
        if constexpr (std::is_same_v<float, F>) {
            F a[] = {1.0, 0.5, 3.0 / 28.0, 1.0 / 84.0, 1.0 / 1680.0};
            for (int i = 4; i >= 0; i--) {
                numerator += a[i];
                numerator *= x1;
                denominator += (i % 2 == 0 ? a[i] : -a[i]);
                denominator *= x1;

            }
        } else if constexpr (std::is_same_v<double, F>) {
            F a[] = {1.0, 0.5, 3.0 / 26.0, 5.0 / 312.0, 5.0 / 3432.0, 1.0 / 11440., 1.0 / 308880.0, 1.0 / 17297280.0};
            for (int i = 7; i >= 0; i--) {
                numerator += a[i];
                numerator *= x1;
                denominator += (i % 2 == 0 ? a[i] : -a[i]);
                denominator *= x1;

            }
        } else {
            F a[] = {1.0, 0.5, 7.0 / 60.0, 1.0 / 60.0, 1.0 / 624.0, 1.0 / 9360.0, 1.0 / 205920.0, 1.0 / 7207200.0, 1.0 / 518918400.0};
            for (int i = 8; i >= 0; i--) {
                numerator += a[i];
                numerator *= x1;
                denominator += (i % 2 == 0 ? a[i] : -a[i]);
                denominator *= x1;

            }
        }
        return std::ldexp(numerator / denominator, static_cast<int>(n));
    }
}
}  // namespace ADAAI

#endif
