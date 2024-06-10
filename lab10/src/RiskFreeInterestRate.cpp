#include "../include/RiskFreeInterestRate.hpp"
#include <cassert>

double RiskFreeInterestRate::operator()(double tau) {
    assert (0 <= tau <= 1);
    if (0 <= tau && tau < step_len) {
        return val[0];
    }
    if (step_len <= tau && tau < 2 * step_len) {
        return val[1];
    }
    if (2 * step_len <= tau && tau < 3 * step_len) {
        return val[2];
    }
    return val[3];
}

double RiskFreeInterestRate::integral_from_zero_to(double tau) {
    assert (0 <= tau && tau <= 1);
    double res = 0;
    if (tau < step_len) {
        return val[0] * tau;
    }
    res += val[0] * step_len;
    if (tau < 2 * step_len) {
        return res + val[1] * (tau - 1 * step_len);
    }
    res += val[1] * step_len;
    if (tau < 3 * step_len) {
        return res + val[2] * (tau - 2 * step_len);
    }
    res += val[2] * step_len;
    return res + val[3] * (tau - 3 * step_len);
}