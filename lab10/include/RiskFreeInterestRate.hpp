#ifndef RISK_FREE_INTEREST_RATE_HPP
#define RISK_FREE_INTEREST_RATE_HPP

// Class denoted by the r variable in the lecture
class RiskFreeInterestRate {
private:
    // given by the teacher
    double val[4] = { 0.16, 0.15, 0.14, 0.13 };
    double step_len = 0.25;
public:
    double operator()(double tau);
    double integral_from_zero_to(double tau);
};


#endif