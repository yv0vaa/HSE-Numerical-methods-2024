#ifndef AAD22_HPP
#define AAD22_HPP
#include <cmath>
#include <iostream>

class AAD22 {
  private:
    double val;
    double d1[2];  // d_x, d_y
    double d2[3];  // d_xx, d_yy, d_xy

  public:
    AAD22() = delete;
    constexpr AAD22(double c) : val(c), d1{0, 0}, d2{0, 0, 0} {};

    // FOR TESTING PURPOSES
    friend std::ostream &operator<<(std::ostream &out, const AAD22 &a) {
        out << "{val=" << a.val << ", d1=[" << a.d1[0] << ", " << a.d1[1] 
            << "], d2=[" << a.d2[0] << ", " << a.d2[1] << ", " << a.d2[2] << "]}";
        return out;
    }

  private:
    constexpr AAD22(int i, double v)
        :  // i = 0 for 'x', i = 1 for 'y'
          val(v), d1{(i == 0) ? 1.0 : 0.0, (i == 0) ? 0.0 : 1.0}, d2{0, 0,
                                                                     0} {};

  public:
    double value() const { return val; }
    double d_x() const { return d1[0]; }
    double d_y() const { return d1[1]; }
    double d_xx() const { return d2[0]; }
    double d_yy() const { return d2[1]; }
    double d_xy() const { return d2[2]; }

    // constexpr
    static AAD22 X(double v) {
        AAD22 X = AAD22(0, v);
        // std::cout << "\ncreated x = " << X << "\n";
        return X;
    }
    // constexpr
    static AAD22 Y(double v) {
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