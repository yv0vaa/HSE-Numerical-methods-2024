#include "../include/u_derivative.hpp"
#include <iostream>

void print_arr(double *a, int size) {
    std::cout << "(";
    for (int i = 0; i < size - 1; i++) {
        std::cout << a[i] << ", ";
    }
    std::cout << a[size - 1] << ")";
}

int main() {
    double u[4] = {10, 1160, 10, 1160};
    double *derivative = u_derivative(u);
    std::cout << "u = ";
    print_arr(u, 4);
    std::cout << "\nu' = ";
    print_arr(derivative, 4);
    std::cout << std::endl;
}
