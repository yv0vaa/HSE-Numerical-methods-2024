#ifndef AAD22_HPP
#define AAD22_HPP

#include <cmath>

class AAD22 {
private:
    double val;
    double d1[2]; // d_x, d_y
    double d2[3]; // d_xx, d_yy, d_xy 

public:
    AAD22() = delete;
    constexpr AAD22(double c) : 
        val(c), 
        d1{0, 0}, 
        d2{0, 0, 0} 
        {};

private:
    constexpr AAD22(int i, double v) : // i = 0 for 'x', i = 1 for 'y' 
        val(v),  
        d1{(i == 0) ? 1.0 : 0.0, (i == 0) ? 0.0 : 1.0}, 
        d2{0, 0, 0} 
        {};

public:
    double value() const { return val; }
    double d_x() const { return d1[0]; }
    double d_y() const { return d1[2]; }
    double d_xx() const { return d2[0]; }
    double d_yy() const { return d2[1]; }
    double d_xy() const { return d2[2]; }

    constexpr static AAD22 X(double v) { return AAD22(0, v); }
    constexpr static AAD22 Y(double v) { return AAD22(1, v); }

    // Operators overloading

    AAD22 &operator+() const {
        AAD22 res = *this;
        return res;
    }

    AAD22 &operator-() const {
        AAD22 res(0);

        res.val = -(this->val);

        res.d1[0] = -(this->d1[0]);
        res.d1[1] = -(this->d1[1]);

        res.d2[0] = -(this->d2[0]);
        res.d2[1] = -(this->d2[1]);
        res.d2[2] = -(this->d2[2]);

        return res;
    }

    AAD22 &operator+=(const AAD22 &other) {
        this->val += other.val;

        this->d1[0] += other.d1[0];
        this->d1[1] += other.d1[1];

        this->d2[0] += other.d2[0];
        this->d2[1] += other.d2[1];
        this->d2[2] += other.d2[2];

        return *this;
    }

    AAD22 &operator-=(const AAD22 &other) {
        *this += (-other);
        return *this;
    }

    AAD22 &operator*=(const AAD22 &g) {
        AAD22 f = *this;

        this->val = f.val * g.val;

        this->d1[0] = f.d1[0] * g.val + f.val * g.d1[0];
        this->d1[1] = f.d1[1] * g.val + f.val * g.d1[1];
        
        this->d2[0] = 2.0 * f.d1[0] * g.d1[0] + f.d2[0] * g.val + f.val * g.d2[0];
        this->d2[1] = 2.0 * f.d1[1] * g.d1[1] + f.d2[1] * g.val + f.val * g.d2[1];
        this->d2[2] = f.d1[0] * g.d1[1] + f.d1[1] * g.d1[0] + f.d2[2] * g.val + f.val * g.d2[2];

        return *this;
    }

    AAD22 &operator/=(const AAD22 &g) {
        AAD22 f = *this;

        this->val = f.val / g.val;

        this->d1[0] = (f.d1[0] * g.val - f.val * g.d1[0]) / pow(g.val, 2);
        this->d1[1] = (f.d1[1] * g.val - f.val * g.d1[1]) / pow(g.val, 2);
        
        this->d2[0] = (-g.val * (2.0 * f.d1[0] * g.d1[0] + f.val * g.d2[0]) + f.d2[0] * pow(g.val, 2) + 2.0 * f.val * pow(g.d1[0], 2)) / pow(g.val, 3);
        this->d2[1] = (-g.val * (2.0 * f.d1[1] * g.d1[1] + f.val * g.d2[1]) + f.d2[1] * pow(g.val, 2) + 2.0 * f.val * pow(g.d1[1], 2)) / pow(g.val, 3);
        this->d2[2] = (-g.val * (f.d1[0] * g.d1[1] + f.d1[1] * g.d1[0] + f.val * g.d2[2]) + f.d2[2] * pow(g.val, 2) + 2.0 * f.val * g.d1[0] * g.d1[1]) / pow(g.val, 3);

        return *this;
    }

    friend AAD22 operator+(AAD22 thiss, const AAD22 &other);
    friend AAD22 operator-(AAD22 thiss, const AAD22 &other);
    friend AAD22 operator*(AAD22 thiss, const AAD22 &other);
    friend AAD22 operator/(AAD22 thiss, const AAD22 &other);
    friend AAD22 sin(const AAD22 &f);
    friend AAD22 cos(const AAD22 &f);
    friend AAD22 exp(const AAD22 &f);
};

AAD22 operator+(AAD22 thiss, const AAD22 &other) {
    return thiss += other;
}
AAD22 operator-(AAD22 thiss, const AAD22 &other) {
    return thiss -= other;
}
AAD22 operator*(AAD22 thiss, const AAD22 &other) {
    return thiss *= other;
}
AAD22 operator/(AAD22 thiss, const AAD22 &other) {
    return thiss /= other;
}

AAD22 sin(const AAD22 &f) {
    AAD22 res = AAD22(0);
    double sin_val = std::sin(f.val);
    double cos_val = std::cos(f.val);

    res.val = sin_val;

    res.d1[0] = cos_val * f.d1[0];
    res.d2[1] = cos_val * f.d1[1];

    res.d2[0] = cos_val * f.d2[0] - sin_val * pow(f.d1[0], 2);
    res.d2[1] = cos_val * f.d2[1] - sin_val * pow(f.d1[1], 2);
    res.d2[2] = cos_val * f.d2[2] - sin_val * f.d1[0] * f.d1[1];

    return res;
}

AAD22 cos(const AAD22 &f) {
    AAD22 res = AAD22(0);
    double sin_val = std::sin(f.val);
    double cos_val = std::cos(f.val);
    
    res.val = cos_val;

    res.d1[0] = -sin_val * f.d1[0];
    res.d2[1] = -sin_val * f.d1[1];

    res.d2[0] = -sin_val * f.d2[0] - cos_val * pow(f.d1[0], 2);
    res.d2[1] = -sin_val * f.d2[1] - cos_val * pow(f.d1[1], 2);
    res.d2[2] = -sin_val * f.d2[2] - cos_val * f.d1[0] * f.d1[1];

    return res;
}

AAD22 exp(const AAD22 &f) {
    AAD22 res = AAD22(0);
    double exp_val = std::exp(f.val);

    res.val = exp_val;

    res.d1[0] = exp_val * f.d1[0];
    res.d1[1] = exp_val * f.d1[1];

    res.d2[0] = exp_val * (pow(f.d1[0], 2) + f.d2[0]);
    res.d2[1] = exp_val * (pow(f.d1[1], 2) + f.d2[1]);
    res.d2[2] = exp_val * (f.d1[0] * f.d1[1] + f.d2[2]);

    return res;
}

#endif