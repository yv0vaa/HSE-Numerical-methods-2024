#ifndef DIFFERENTIATOR_HPP
#define DIFFERENTIATOR_HPP
#include "AAD22.hpp"
#include <cmath>

enum class DiffMethod {
    Stencil3,
    Stencil3Extra,
    Stencil5,
    Stencil5Extra,
    FwdAAD
};

const double H_CONST = 1e-5;

enum class WhichD { X, Y, XY, XX, YY };

template <WhichD w, DiffMethod M, typename Callable>
double Differentiator(const Callable &F, double x, double y) {
    double hx = H_CONST, hy = H_CONST;
    if (abs(x) > 1) {
        hx *= abs(x);
    }
    if (abs(y) > 1) {
        hy *= abs(y);
    }
    if constexpr (M == DiffMethod::Stencil3) {
        switch (w) {
        case WhichD::X:
            return (F(x + hx, y) - F(x - hx, y)) / (2 * hx);
        case WhichD::Y:
            return (F(x, y + hy) - F(x, y - hy)) / (2 * hy);
        case WhichD::XX:
            return (F(x + hx, y) - 2 * F(x, y) + F(x - hx, y)) / (hx * hx);
        case WhichD::YY:
            return (F(x, y + hy) - 2 * F(x, y) + F(x, y - hy)) / (hy * hy);
        case WhichD::XY:
            return (F(x + hx, y + hy) - F(x - hx, y + hy) - F(x + hx, y - hy) +
                    F(x - hx, y - hy)) /
                   (4 * hx * hy);
        }
    } else if constexpr (M == DiffMethod::Stencil3Extra) {
        int n = 3;
        switch (w) {
        case WhichD::X:
            return (n * n *
                        Differentiator<WhichD::X, DiffMethod::Stencil3>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::X, DiffMethod::Stencil3>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        case WhichD::Y:
            return (n * n *
                        Differentiator<WhichD::Y, DiffMethod::Stencil3>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::Y, DiffMethod::Stencil3>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        case WhichD::XX:
            return (n * n *
                        Differentiator<WhichD::XX, DiffMethod::Stencil3>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::XX, DiffMethod::Stencil3>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        case WhichD::YY:
            return (n * n *
                        Differentiator<WhichD::YY, DiffMethod::Stencil3>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::YY, DiffMethod::Stencil3>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        case WhichD::XY:
            return (n * n *
                        Differentiator<WhichD::XY, DiffMethod::Stencil3>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::XY, DiffMethod::Stencil3>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        }
    } else if constexpr (M == DiffMethod::Stencil5) {
        switch (w) {
        case WhichD::X:
            return (F(x - 2 * hx, y) / 12 - 2 * F(x - hx, y) / 3 +
                    2 * F(x + hx, y) / 3 - F(x + 2 * hx, y) / 12) /
                   hx;
        case WhichD::Y:
            return (F(x, y - 2 * hy) / 12 - 2 * F(x, y - hy) / 3 +
                    2 * F(x, y + hy) / 3 - F(x, y + 2 * hy) / 12) /
                   hy;
        case WhichD::XX:
            return (-F(x - 2 * hx, y) / 12 + 4 * F(x - hx, y) / 3 -
                    5 * F(x, y) / 2 + 4 * F(x + hx, y) / 3 -
                    F(x + 2 * hx, y) / 12) /
                   (hx * hx);
        case WhichD::YY:
            return (-F(x, y - 2 * hy) / 12 + 4 * F(x, y - hy) / 3 -
                    5 * F(x, y) / 2 + 4 * F(x, y + hy) / 3 -
                    F(x, y + 2 * hy) / 12) /
                   (hy * hy);
        case WhichD::XY:
            double d_coeffs[5];
            for (int i = 0; i < 5; i++) {
                double y_coeff = i - 2;
                double y_value = y + hy * y_coeff;
                d_coeffs[i] =
                    F(x - 2 * hx, y_value) / 12 - 2 * F(x - hx, y_value) / 3 +
                    2 * F(x + hx, y_value) / 3 - F(x + 2 * hx, y_value) / 12;
                d_coeffs[i] /= hx;
            }
            return (d_coeffs[0] / 12 - 2 * d_coeffs[1] / 3 +
                    2 * d_coeffs[3] / 3 - d_coeffs[4] / 12) /
                   hy;
        }
    } else if constexpr (M == DiffMethod::Stencil5Extra) {
        int n = 3;
        switch (w) {
        case WhichD::X:
            return (n * n *
                        Differentiator<WhichD::X, DiffMethod::Stencil5>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::X, DiffMethod::Stencil5>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        case WhichD::Y:
            return (n * n *
                        Differentiator<WhichD::Y, DiffMethod::Stencil5>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::Y, DiffMethod::Stencil5>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        case WhichD::XX:
            return (n * n *
                        Differentiator<WhichD::XX, DiffMethod::Stencil5>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::XX, DiffMethod::Stencil5>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        case WhichD::YY:
            return (n * n *
                        Differentiator<WhichD::YY, DiffMethod::Stencil5>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::YY, DiffMethod::Stencil5>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        case WhichD::XY:
            return (n * n *
                        Differentiator<WhichD::XY, DiffMethod::Stencil5>(
                            F, x + hx / n, y + hy / n) -
                    Differentiator<WhichD::XY, DiffMethod::Stencil5>(F, x + hx,
                                                                     y + hy)) /
                   (n * n - 1);
        }
    } else if constexpr (M == DiffMethod::FwdAAD) {
        AAD22 AAD22_res = F(AAD22::X(x), AAD22::Y(y));
        switch (w) {
        case WhichD::X:
            return AAD22_res.d_x();
        case WhichD::Y:
            return AAD22_res.d_y();
        case WhichD::XX:
            return AAD22_res.d_xx();
        case WhichD::YY:
            return AAD22_res.d_yy();
        case WhichD::XY:
            return AAD22_res.d_xy();
        }
    }
    return 0;  // Should not be reached
}

#endif
