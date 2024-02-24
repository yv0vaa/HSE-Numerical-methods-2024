#ifndef EXP_HPP
#define EXP_HPP

#include "consts.hpp"
#include "cheb_poly.hpp"
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
    // now calc exp(y) 
    F coefs[] = { 1.611869, 1.299692, 0.624356, 0.101961, 0.012589, 0.001249, 0.000103, 0.000007, 0.0, 0.0, 0.0 };
    F t_0 = 1.0, t_1 = y;
    F res = t_0 * coefs[0];
    res += t_1 * coefs[1];
    for (int i = 2; i < 11; i++) {
        F t_new = 2 * y * t_1 - t_0;
        res += coefs[i] * t_new;
        t_0 = t_1;
        t_1 = t_new;
    }
    return std::ldexp(res, static_cast<int>(n));
}
}  // namespace ADAAI

#endif
