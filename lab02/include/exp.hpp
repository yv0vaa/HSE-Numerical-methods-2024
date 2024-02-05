#ifndef EXP_HPP
#define EXP_HPP

#include "consts.hpp"
#include <assert.h>
#include <climits>
#include <cmath>
#include <type_traits>
#include <iostream>

namespace ADAAI {
template <typename F>
constexpr inline int MkExpTaylorOrder() {
    F ln2_2 = Ln2<F> / 2, tail = sqrt2<F>, delta = Eps<F> * 10;
    for (int i = 1; i < 1000; ++i) {
        if (tail < delta)
            return i;
        tail = tail * ln2_2 / i;
    }
    assert(false);
}

int N_FLOAT = MkExpTaylorOrder<float>();

template <typename F> constexpr F Exp(F x) {
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
    F delta = 10.0 * Eps<F>, f1 = 1.0, x1 = y * Ln2<F>, k = 1.0;
    F cpy = x1;
    constexpr int N = MkExpTaylorOrder<F>();
    for (int i = 0; i < N; ++i) {
        f1 += x1;
        x1 *= cpy;
        k += 1;
        x1 /= k;
    }
    return std::ldexp(f1, static_cast<int> (n));
}
}  // namespace ADAAI

#endif
