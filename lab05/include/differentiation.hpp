#ifndef DIFFERENTIATION_HPP
#define DIFFERENTIATION_HPP
#include "AAD22.hpp"
#include <cmath>
enum class DiffMethod {
    Stencil3,
    Stencil3Extra,
    Stencil5,
    Stencil5Extra,
    FwdAAD
};

enum class WhichD { X, Y, XY, XX, YY };
template <WhichD w, DiffMethod M, typename Callable>
double Differentiator(Callable const &F, double x, double y);

#endif