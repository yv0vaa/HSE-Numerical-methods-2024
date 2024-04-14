#include "../include/Observer.hpp"
#include <iostream>

bool Observer::operator()(double a_curr_t, int a_n,
                    double const *a_curr_y) {
    switch (observe_method)
    {
        case ObserveMethod::ReturnCoordinates:
            if (a_curr_y[2] > 0) {
                std::cout << "t: " << a_curr_t << "\n";
                std::cout << "x: " << a_curr_y[0] << "\n";
                std::cout << "y: " << a_curr_y[2] << "\n";
                return true;
            }
            else {
                return false;
            }
            break;
        case ObserveMethod::CheckMaxRange:
            if (a_curr_y[2] > 0) {
                return true;
            } else {
                return false;
            }
    }
}
