#ifndef EXP_HPP
#define EXP_HPP

#include <cfloat>
#include <climits>
#include <cmath>
#include <type_traits>

namespace ADAAI {
template <typename F> constexpr inline F Ln2;
template <> constexpr inline float Ln2<float> = 1 / M_LOG2Ef;
template <> constexpr inline double Ln2<double> = 1 / M_LOG2E;
template <> constexpr inline long double Ln2<long double> = 1 / M_LOG2El;

template <typename F> constexpr inline F Eps;
template <> constexpr inline float Eps<float> = FLT_EPSILON;
template <> constexpr inline double Eps<double> = DBL_EPSILON;
template <> constexpr inline long double Eps<long double> = LDBL_EPSILON;

template <typename F> constexpr inline F sqrt2;
template <> constexpr inline float sqrt2<float> = M_SQRT2f;
template <> constexpr inline double sqrt2<double> = M_SQRT2;
template <> constexpr inline long double sqrt2<long double> = M_SQRT2l;

template <typename F> constexpr F Exp(F x) {
    static_assert(std::is_floating_point_v<F>);
    F n;
    F y = x / Ln2<F>;
    y = std::modf(y, &n);
    if (y > 0.5 || y < -0.5) {
        if (y > 0) {
            n += 1;
            y = 1 - y;
        } else {
            n -= 1;
            y++;
        }
    }
    if (n < INT_MIN) {
        return 0.0;
    }
    if (n > INT_MAX) {
        return 1 / 0.0;
    }
    n = (int)n;
    F delta = 10.0 * Eps<F>;
    F f1 = 1.0;
    F x1 = y * Ln2<F>;
    F cpy = x1;
    F k = 1.0;
    while (sqrt2<F> * x1 > delta) {
        f1 += x1;
        x1 *= cpy;
        x1 /= k;
        k += 1;
    }
    return std::ldexp(n, f1);
}
}  // namespace ADAAI

#endif