#include <iostream>
#include "exp.hpp"

int main() {
	float f = 3.0;
	double d = 10.0;
	long double ld = 0.001;
	std::cout << ADAAI::Exp(f) << ' ' << ADAAI::Exp(d) << ' ' << ADAAI::Exp(ld) << '\n';  
}