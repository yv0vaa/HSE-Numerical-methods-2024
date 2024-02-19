#include <iostream>
#include <gsl/gsl_sf_bessel.h>
#include "include/cheb_poly.hpp"

int main () {
	auto res = cheb_poly(10);
	for (auto elem : res) {
		for (int a : elem) {
			std::cout << a << ' ';
		}
		std::cout << '\n';
		print_cheb_poly(elem);
		std::cout << "\n";
	}
	/*double x = 5.0;
	double y = gsl_sf_bessel_J0 (x);
	printf ("J0(%g) = %.18e\n", x, y);*/
}