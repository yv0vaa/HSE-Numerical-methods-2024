#ifndef RHS_HPP
#define RHS_HPP
#include "../../lab06/include/u_derivative.hpp"
class RHS {
  public:
    constexpr static int N = 4;
    void operator()(double a_t, double a_y[N], double a_rhs[N]) const;
};

#endif