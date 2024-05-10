#include "../include/Observer.hpp"
#include <iostream>

bool Observer::operator()(double a_curr_t, double const *a_curr_y) {
    std::cout << "t: " << a_curr_t << '\n';
    std::cout << "x: " << a_curr_y[0] << '\n';
    std::cout << "y: " << a_curr_y[1] << '\n';
    std::cout << "z: " << a_curr_y[2] << '\n'; 
    return true;
}
