#ifndef VOLATILITY_HPP
#define VOLATILITY_HPP

// Class denoted by the sigma variable in the lecture 
class Volatility {
private:
    // definition of sigma function that I made up
    double val[4] = { 0.23, 0.28, 0.22, 0.25 };
    double step_len = 0.25;
public:
    double operator()(double tau);
    double integral_of_squared_from_zero_to(double tau);
};


#endif