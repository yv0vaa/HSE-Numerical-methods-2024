#ifndef RHS_HPP
#define RHS_HPP
#include <cmath>
#include <vector>

class RHS {
  public:
    constexpr static int N = 3;
    void operator()(double a_y[N], double a_y_dot[N],
                    std::vector<double> &a_rhs) const;

  private:
    constexpr static double mu = 398600.4;
    constexpr static double Re = 6378.137;
    constexpr static double j2 = 1.0827 * 1e-3;

    constexpr double norm(double r[N]) const {
        return std::sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
    }
};

#endif