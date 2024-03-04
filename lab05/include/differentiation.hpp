#include <cmath>
#include "AAD22.hpp"
enum class DiffMethod{
	Stencil3,
	Stencil3Extra,
	Stencil5,
	Stencil5Extra,
	FwdAAD
};

enum class WhichD{
	X,
	Y,
	XY,
	XX,
	YY
};

template <WhichD w, DiffMethod M, typename Callable>
double Differentiator(Callable const &F, double x, double y) {
    if constexpr(M == DiffMethod::Stencil3) {
        double res = 0;
        double h = 1e-4;
        switch (w) { 
        case WhichD::X:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            res = F(x - h, y) - F(x + h, y);
            res /= h;
            break;
        case WhichD::Y:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            res = F(x, y - h) - F(x, y + h);
            res /= h;
            break;
        case WhichD::XX:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            res = F(x - h, y) -2 * F(x,y) + F(x + h, y);
            res /= (h * h);
            break;
        case WhichD::YY:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            res = F(x, y - h) - 2 * F(x,y) + F(x, y + h);
            res /= (h * h);
            break;
        case WhichD::XY:
            res = F(x + h, y + h) - F(x - h, x + h) - F(x + h, x - h) + F(x - h, y - h);
            res /= (h * h);
            res /= 4;
            break;
        }
        return res;
	} else if constexpr(M == DiffMethod::Stencil3Extra) {
        double res = 0;
        double h = 1e-4;
        int n = 3;
        switch (w) {
        case WhichD::X:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            res = F(x + h, y + h) / 12 - n * n * F(x + (h / n), y + (h / n)) -
                  (1 - n * n) * F(x, y) -
                  h *
                      Differentiator<w, DiffMethod::Stencil3>(
                          F, x, y) *
                      (1 - n);
            res /= h;
            res /= (1 - n);
            break;
        case WhichD::Y:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            res = F(x + h, y + h) / 12 - n * n * F(x + (h / n), y + (h / n)) -
                  (1 - n * n) * F(x, y) -
                  h *
                      Differentiator <w, DiffMethod::Stencil3>(
                          F, x, y) *
                      (1 - n);
            res /= h;
            res /= (1 - n);
            break;
        case WhichD::XX:
            res = n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                  h * (n * n - 1) *
                      (Differentiator<WhichD::X, DiffMethod::Stencil3>(F, x, y) +
                       Differentiator<WhichD::Y, DiffMethod::Stencil3>(F, x, y));
            res -= Differentiator<WhichD::XY, DiffMethod::Stencil3>(F, x, y);
            res -= ( Differentiator<WhichD::YY, DiffMethod::Stencil3>(F, x, y) / 2 );
            res *= 2;
            res /= (h * h);
            res /= (n - 1);
            break;
        case WhichD::YY:
            res = n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                  h * (n * n - 1) *
                      (Differentiator<WhichD::X, DiffMethod::Stencil3>(F, x, y) +
                       Differentiator<WhichD::Y, DiffMethod::Stencil3>(F, x, y));
            res -= Differentiator<WhichD::XY, DiffMethod::Stencil3>(
                F, x, y);
            res -=
                (Differentiator<WhichD::XX, DiffMethod::Stencil3>(
                     F, x, y) /
                 2);
            res *= 2;
            res /= (h * h);
            res /= (n - 1);
            break;
        case WhichD::XY:
            res = n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                  h * (n * n - 1) *
                      (Differentiator<WhichD::X, DiffMethod::Stencil3>(F, x, y) +
                       Differentiator<WhichD::Y, DiffMethod::Stencil3>(F, x, y));
            res -=
                (Differentiator<WhichD::YY, DiffMethod::Stencil3>(
                     F, x, y) /
                 2);
            res -=
                (Differentiator<WhichD::XX, DiffMethod::Stencil3>(
                     F, x, y) /
                 2);
            res /= (h * h);
            res /= (n - 1);
            break;
        }
        return res;
    } else if constexpr(M == DiffMethod::Stencil5) {
            double res = 0;
            double h = 1e-4;
            switch (w) {
            case WhichD::X:
                if (abs(x) > 1) {
                    h *= abs(x);
                }
                res = F(x - 2 * h, y) / 12 - 2 * F(x - h, y) / 3 +
                    2 * F(x + h, y) / 3 - F(x + 2*h, y)/12;
                res /= h;
                break;
            case WhichD::Y:
                if (abs(y) > 1) {
                    h *= abs(y);
                }
                res = F(x, y - 2 * h) / 12 - 2 * F(x, y - h) / 3 +
                    2 * F(x, y + h) / 3 - F(x, y + 2 * h) / 12;
                res /= h;
                break;
            case WhichD::XX:
                if (abs(x) > 1) {
                    h *= abs(x);
                }
                res = -F(x - 2 * h, y) / 12 + 4 * F(x - h, y) / 3 -
                      5 * F(x,y) / 2 + 
                      4 * F(x + h, y) / 3 - F(x + 2 * h, y) / 12;
                res /= (h * h);
                break;
            case WhichD::YY:
                if (abs(y) > 1) {
                    h *= abs(y);
                }
                res = -F(x, y - 2 * h) / 12 + 4 * F(x, y - h) / 3 - 5 * F(x,y) / 2 + 4 * F(x, y + h) / 3 - F(x, y + 2 * h) / 12;
                res /= (h * h);
                break;
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
                res = d_coeffs[0] / 12 - 2 * d_coeffs[1] / 3 +
                      2 * d_coeffs[3] / 3 - d_coeffs[4] / 12;
                res /= h;
                break;
            }
            return res;
    } else if constexpr(M == DiffMethod::Stencil5Extra) {
        double res = 0;
        double h = 1e-4;
        int n = 3;
        switch (w) {
        case WhichD::X:
            if (abs(x) > 1) {
                h *= abs(x);
            }
            res = F(x + h, y + h) / 12 - n * n * F(x + (h / n), y + (h / n)) -
                  (1 - n * n) * F(x, y) -
                  h *
                      Differentiator<w, DiffMethod::Stencil5>(F, x,
                                                                          y) *
                      (1 - n);
            res /= h;
            res /= (1 - n);
            break;
        case WhichD::Y:
            if (abs(y) > 1) {
                h *= abs(y);
            }
            res = F(x + h, y + h) / 12 - n * n * F(x + (h / n), y + (h / n)) -
                  (1 - n * n) * F(x, y) -
                  h *
                      Differentiator<w, DiffMethod::Stencil5>(F, x,
                                                                          y) *
                      (1 - n);
            res /= h;
            res /= (1 - n);
            break;
        case WhichD::XX:
            res = n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                  h * (n * n - 1) *
                      (Differentiator<WhichD::X, DiffMethod::Stencil5>(F, x, y) +
                       Differentiator<WhichD::Y, DiffMethod::Stencil5>(F, x, y));
            res -= Differentiator<WhichD::XY, DiffMethod::Stencil5>(
                F, x, y);
            res -=
                (Differentiator<WhichD::YY, DiffMethod::Stencil5>(
                     F, x, y) /
                 2);
            res *= 2;
            res /= (h * h);
            res /= (n - 1);
            break;
        case WhichD::YY:
            res = n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                  h * (n * n - 1) *
                      (Differentiator<WhichD::X, DiffMethod::Stencil5>(F, x, y) +
                       Differentiator<WhichD::Y, DiffMethod::Stencil5>(F, x, y));
            res -= Differentiator<WhichD::XY, DiffMethod::Stencil5>(
                F, x, y);
            res -=
                (Differentiator<WhichD::XX, DiffMethod::Stencil5>(
                     F, x, y) /
                 2);
            res *= 2;
            res /= (h * h);
            res /= (n - 1);
            break;
        case WhichD::XY:
            res = n * n * n * F(x + (h / n), y + (h / n)) - F(x + h, y + h) -
                  h * (n * n - 1) *
                      (Differentiator<WhichD::X, DiffMethod::Stencil5>(F, x, y) +
                       Differentiator<WhichD::Y, DiffMethod::Stencil5>(F, x, y));
            res -=
                (Differentiator<WhichD::YY, DiffMethod::Stencil5>(
                     F, x, y) /
                 2);
            res -=
                (Differentiator<WhichD::XX, DiffMethod::Stencil5>(
                     F, x, y) /
                 2);
            res /= (h * h);
            res /= (n - 1);
            break;
        }
        return res;
    } else if constexpr(M == DiffMethod::FwdAAD) {
        AAD22 AAD22_res = F(AAD22::X(x),AAD22::Y(y));
        double res = 0;
        switch (w) {
        case WhichD::X:
            res = AAD22_res.d_x();
            break;
        case WhichD::Y:
            res = AAD22_res.d_y();
            break;
        case WhichD::XX:
            res = AAD22_res.d_xx();
            break;
        case WhichD::YY:
            res = AAD22_res.d_yy();
            break;
        case WhichD::XY:
            res = AAD22_res.d_xy();
            break;
        }
        return res;
        }
    return 0; // Should not be reached
    }	
