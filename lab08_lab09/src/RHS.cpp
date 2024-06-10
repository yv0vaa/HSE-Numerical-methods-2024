#include "../include/RHS.hpp"

void RHS::operator()(double a_y[N], double a_y_dot[N],
                     std::vector<double> &a_rhs) const {
    double r = norm(a_y);
    double r3 = std::pow(r, 3);
    double r5 = std::pow(r, 5);
    double r7 = std::pow(r, 7);
    double Re2 = Re * Re;
    a_rhs[0] = -(mu * a_y[0]) / r3 +
               (15 * j2 * Re2 * mu * a_y[0] * a_y[2] * a_y[2]) / (2 * r7) -
               (3 * j2 * Re2 * mu * a_y[0]) / (2 * r5);
    a_rhs[1] = -(mu * a_y[1]) / r3 +
               (15 * j2 * Re2 * mu * a_y[1] * a_y[2] * a_y[2]) / (2 * r7) -
               (3 * j2 * Re2 * mu * a_y[1]) / (2 * r5);
    a_rhs[2] = -(mu * a_y[2]) / r3 - (3 * j2 * Re2 * mu * a_y[2]) / r5 -
               (15 * j2 * Re2 * mu * std::pow(a_y[2], 3)) / (2 * r7) -
               (3 * j2 * Re2 * mu * a_y[2]) / (2 * r5);
}