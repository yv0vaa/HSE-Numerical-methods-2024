#ifndef RHS_HPP
#define RHS_HPP

class RHS {
  public:
    constexpr static int N = 4;
    RHS();
    void operator()(double a_t, double a_y[N], double a_rhs[N]) const;
};

#endif