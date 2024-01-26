#ifndef EXP_HPP
#define EXP_HPP

#include <cfloat>
#include <cmath>
#include <type_traits>

namespace ADAAI{
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
    // e^x = 2^xlog_2e = 2^x/ln2 = 2^y
    // std::modf y = y_0 + y_1
    // y < 0 => y_0, y_1 < 0 => make |y_1| < 0.5
    // int n = (int) y_0 BUT CHECK y_0 fits in to int

    // y_0 < INT_MIN => return 0,0
    // y_0 > INT_MAX => return +inf

    // 2^y = 2^(n + y_1) = 2^n * 2^y1 = 2^n * e^y_1ln2
    // absolute precision delta = 10.0 * Eps<F>
    F delta = 10.0 * Eps<F>;
    while (/* condition */) {
        /* code */
    }
}
}  // namespace

#endif