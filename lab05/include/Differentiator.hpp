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

const double H_CONST = 1e-4;

enum class WhichD { X, Y, XY, XX, YY };

template <WhichD w, DiffMethod M, typename Callable>
double Differentiator(Callable const &F, double x, double y) {
    if constexpr (M == DiffMethod::Stencil3) {
        double res = 0;
        double h = H_CONST;
        switch (w) {
        case WhichD::X:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            return (F(x + h, y) - F(x - h, y)) / (2 * h);
        case WhichD::Y:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            return (F(x, y + h) - F(x, y - h)) / (2 * h);
        case WhichD::XX:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            return (F(x + h, y) - 2 * F(x, y) + F(x - h, y)) / (h * h);
        case WhichD::YY:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            return (F(x, y + h) - 2 * F(x, y) + F(x, y - h)) / (h * h);
        case WhichD::XY:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            double hx = H_CONST;
            if (abs(x) > 1) {
                hx *= abs(x);
            }
            return (F(x + hx, y + h) - F(x - hx, y + h) - F(x + hx, y - h) + F(x - hx, y - h)) /
                   (4 * hx * h);
        }
    } else if constexpr (M == DiffMethod::Stencil3Extra) {
        double h = H_CONST;
        int n = 3;
        switch (w) {
        case WhichD::X:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            return (F(x + h, y + h) - n * n * F(x + (h / n), y + (h / n)) -
                    (1 - n * n) * F(x, y) - 
                    h * Differentiator<WhichD::Y, DiffMethod::Stencil3>(F, x, y) * (1 - n)) / (h * (1 - n));
        case WhichD::Y:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            return (F(x + h, y + h) - n * n * F(x + (h / n), y + (h / n)) - 
                    (1 - n * n) * F(x, y) - 
                    h * Differentiator<WhichD::X, DiffMethod::Stencil3>(F, x, y) * (1 - n)) / (h * (1 - n));
        case WhichD::XX:
            return 2 * ((h * h * h * F(x + h / n, y + h / n) - F(x + h, y + h) -
                    (n * n * n - 1) * F(x, y) - (n * n - 1) * h *
                    (Differentiator<WhichD::X, DiffMethod::Stencil3>(F, x, y) +
                    Differentiator<WhichD::Y, DiffMethod::Stencil3>(F, x, y))) / 
                    ((n - 1) * h * h) - 
                    Differentiator<WhichD::XY, DiffMethod::Stencil3>(F, x, y) - 
                    Differentiator<WhichD::YY, DiffMethod::Stencil3>(F, x, y) / 2);  
        case WhichD::YY: 
            return 2 * ((h * h * h * F(x + h / n, y + h / n) - F(x + h, y + h) -
                    (n * n * n - 1) * F(x, y) -
                    (n * n - 1) * h *
                    (Differentiator<WhichD::X, DiffMethod::Stencil3>(F, x, y) +
                    Differentiator<WhichD::Y, DiffMethod::Stencil3>(F, x, y))) /
                    ((n - 1) * h * h) - 
                    Differentiator<WhichD::XY, DiffMethod::Stencil3>(F, x, y) - 
                    Differentiator<WhichD::XX, DiffMethod::Stencil3>(F, x, y) / 2); 
        case WhichD::XY:
            return n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                    h * (n * n - 1) *
                    (Differentiator<WhichD::X, DiffMethod::Stencil3>(F, x, y) +
                    Differentiator<WhichD::Y, DiffMethod::Stencil3>(F, x, y)) /
                    (h * h * (n - 1)) -
                    Differentiator<WhichD::YY, DiffMethod::Stencil3>(F, x, y) / 2 -
                    Differentiator<WhichD::XX, DiffMethod::Stencil3>(F, x, y) / 2;
        }
    } else if constexpr (M == DiffMethod::Stencil5) {
        double res = 0;
        double h = H_CONST;
        switch (w) {
        case WhichD::X:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            return (F(x - 2 * h, y) / 12 - 2 * F(x - h, y) / 3 +
                    2 * F(x + h, y) / 3 - F(x + 2 * h, y) / 12) /
                   h;
        case WhichD::Y:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            return (F(x, y - 2 * h) / 12 - 2 * F(x, y - h) / 3 +
                    2 * F(x, y + h) / 3 - F(x, y + 2 * h) / 12) /
                    h;
        case WhichD::XX:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            return (-F(x - 2 * h, y) / 12 + 4 * F(x - h, y) / 3 -
                    5 * F(x, y) / 2 + 4 * F(x + h, y) / 3 -
                    F(x + 2 * h, y) / 12) /
                    (h * h);
        case WhichD::YY:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            return (-F(x, y - 2 * h) / 12 + 4 * F(x, y - h) / 3 -
                    5 * F(x, y) / 2 + 4 * F(x, y + h) / 3 -
                    F(x, y + 2 * h) / 12) /
                    (h * h);
        case WhichD::XY:
            double d_coeffs[5];
            for (int i = 0; i < 5; i++) {
                double y_coeff = i - 2;
                double y_value = y + h * y_coeff;
                d_coeffs[i] =
                    F(x - 2 * h, y_value) / 12 - 2 * F(x - h, y_value) / 3 +
                    2 * F(x + h, y_value) / 3 - F(x - 2 * h, y_value) / 12;
                d_coeffs[i] /= h;
            }
            res = d_coeffs[0] / 12 - 2 * d_coeffs[1] / 3 + 2 * d_coeffs[3] / 3 -
                  d_coeffs[4] / 12;
            res /= h;
            break;
        }
        return res;
    } else if constexpr (M == DiffMethod::Stencil5Extra) {
        double h = H_CONST;
        int n = 3;
        switch (w) {
        case WhichD::X:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            return (F(x + h, y + h) - n * n * F(x + (h / n), y + (h / n)) - 
                    (1 - n * n) * F(x, y) - h * 
                    Differentiator<WhichD::Y, DiffMethod::Stencil5>(F, x, y) * 
                    (1 - n)) / (h * (1 - n));
        case WhichD::Y:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            return (F(x + h, y + h) - n * n * F(x + (h / n), y + (h / n)) -
                    (1 - n * n) * F(x, y) - h * 
                    Differentiator<WhichD::X, DiffMethod::Stencil5>(F, x, y) * 
                    (1 - n)) / (h * (1 - n));
        case WhichD::XX:
            return 2 * (n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                    h * (n * n - 1) *
                    (Differentiator<WhichD::X, DiffMethod::Stencil5>(F, x, y) +
                    Differentiator<WhichD::Y, DiffMethod::Stencil5>(F, x, y)) /
                    (h * h * (n - 1)) -
                    Differentiator<WhichD::XY, DiffMethod::Stencil5>(F, x, y) -
                    Differentiator<WhichD::YY, DiffMethod::Stencil5>(F, x, y) / 2);
        case WhichD::YY:
            return 2 *
                   (n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                    h * (n * n - 1) *
                    (Differentiator<WhichD::X, DiffMethod::Stencil5>(F, x, y) +
                    Differentiator<WhichD::Y, DiffMethod::Stencil5>(F, x, y)) /
                    (h * h * (n - 1)) -
                    Differentiator<WhichD::XY, DiffMethod::Stencil5>(F, x, y) -
                    Differentiator<WhichD::XX, DiffMethod::Stencil5>(F, x, y) / 2);
        case WhichD::XY:
            return n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                    h * (n * n - 1) * 
                    (Differentiator<WhichD::X, DiffMethod::Stencil5>(F, x, y) +
                    Differentiator<WhichD::Y, DiffMethod::Stencil5>(F, x, y)) /
                    (h * h * (n - 1)) -
                    Differentiator<WhichD::YY, DiffMethod::Stencil5>(F, x, y) / 2 -
                    Differentiator<WhichD::XX, DiffMethod::Stencil5>(F, x, y) / 2;
        }
    } else if constexpr (M == DiffMethod::FwdAAD) {
        AAD22 AAD22_res = F(AAD22::X(x), AAD22::Y(y));
        double res = 0;
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