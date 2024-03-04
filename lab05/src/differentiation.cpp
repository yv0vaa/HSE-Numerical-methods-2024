#include "../include/differentiation.hpp"
#include "../include/AAD22.hpp"
#include <iostream>
#include <cstdio>

//for now some random stuff, Not sure if this file is needed at all :)
double func(double x, double y) {
    return std::exp(x * x + y);
}

AAD22 F(const AAD22 &x, const AAD22 &y) {
    return exp(x * x + y);
}

int main() {
    std::cout << Differentiator<WhichD::X, DiffMethod::Stencil3>(&func, 1.0, 0.0) << std::endl;
    std::cout << Differentiator<WhichD::X, DiffMethod::FwdAAD>(&F, 1.0, 0.0) << std::endl;
}
