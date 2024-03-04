#include "differentiation.hpp"
#include <iostream>
#include <cstdio>

//for now some random stuff, Not sure if this file is needed at all :)
double func(double x, double y) {
    return (x*x + y);
}
	int main() {
    std::cout
        << Differentiator<WhichD::XY, DiffMethod::Stencil5>(
               &func, 4.0, 6.0) << std::endl;
}
