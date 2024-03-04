#ifndef AAD22_HPP
#define AAD22_HPP
#include <cmath>

class AAD22 {
  private:
    double val;
    double d1[2];  // d_x, d_y
    double d2[3];  // d_xx, d_yy, d_xy

  public:
    AAD22() = delete;
    constexpr AAD22(double c) : val(c), d1{0, 0}, d2{0, 0, 0} {};

  private:
    constexpr AAD22(int i, double v)
        :  // i = 0 for 'x', i = 1 for 'y'
          val(v), d1{(i == 0) ? 1.0 : 0.0, (i == 0) ? 0.0 : 1.0}, d2{0, 0,
                                                                     0} {};

  public:
    double value() const;
    double d_x() const;
    double d_y() const;
    double d_xx() const;
    double d_yy() const;
    double d_xy() const;

    constexpr static AAD22 X(double v) {
        return AAD22(0, v);
    }

    constexpr static AAD22 Y(double v) {
        return AAD22(1, v);
    }

    // Operators overloading

    AAD22 operator+() const;
    AAD22 operator-() const;

    AAD22 &operator+=(const AAD22 &other);
    AAD22 &operator-=(const AAD22 &other);
    AAD22 &operator*=(const AAD22 &g);
    AAD22 &operator/=(const AAD22 &g);
    friend AAD22 operator+(AAD22 thiss, const AAD22 &other);
    friend AAD22 operator-(AAD22 thiss, const AAD22 &other);
    friend AAD22 operator*(AAD22 thiss, const AAD22 &other);
    friend AAD22 operator/(AAD22 thiss, const AAD22 &other);
    friend AAD22 sin(const AAD22 &f);
    friend AAD22 cos(const AAD22 &f);
    friend AAD22 exp(const AAD22 &f);
};

#endif