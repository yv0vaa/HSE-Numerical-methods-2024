#ifndef EXP_HPP
#define EXP_HPP

#include "consts.hpp"

#include <climits>
#include <cmath>
#include <type_traits>

namespace ADAAI {
template <typename F> constexpr F Exp(F x) {
    static_assert(std::is_floating_point_v<F>);
    F n, y = std::modf(x / Ln2<F>, &n);
    if (y > 0.5 || y < -0.5) {
        if (y > 0) {
            n += 1;
            y-=1;
        } else {
            n -= 1;
            y+=1;
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
    while (sqrt2<F> * x1 > delta || -(sqrt2<F> * x1) > delta) {
        f1 += x1;
        x1 *= cpy;
        k += 1;
        x1 /= k;
    }
    return std::ldexp(f1, static_cast<int> (n));
}
}  // namespace ADAAI

#endif
