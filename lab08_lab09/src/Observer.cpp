#include "../include/Observer.hpp"
#include <iostream>

bool Observer::operator()(double a_curr_t, double const *a_curr_y) {
    std::cout << a_curr_t << ',';
    std::cout << a_curr_y[0] << ',';
    std::cout << a_curr_y[1] << ',';
    std::cout << a_curr_y[2] << '\n';
    return true;
}
