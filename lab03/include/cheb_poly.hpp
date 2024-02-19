#ifndef CHEB_POLY_HPP
#define CHEB_POLY_HPP

#include <vector>
#include "../src/cheb_poly.cpp"

std::vector<std::vector<long long>> cheb_poly(int n);

void print_cheb_poly(const std::vector<long long> &coeff);

#endif