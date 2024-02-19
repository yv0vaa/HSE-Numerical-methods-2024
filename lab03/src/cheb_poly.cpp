#include "../include/cheb_poly.hpp" 
#include <string>

std::vector<std::vector<long long>> cheb_poly(int n) {
	std::vector<std::vector<long long>> result {
		{1},
		{1, 0}
	};
	for (int i = 2; i <= n; i++) {
		// std::cout << "CALCULATING FOR n = " << i << "\n"; 
		std::vector<long long> tmp(result[i - 1].size() + 1);
		for (int j = 0; j < result[i - 1].size(); j++) {
			tmp[j] = 2 * result[i - 1][j];
		}

		// std::cout << "	Multiplying by 2 * x polynom T_" << i - 1 << " = ";
		// for (int a : result[i-1]) {
		// 	std::cout << a << ' ';
		// }
		// std::cout << "\n	";
		// for (int a : tmp) {
		// 	std::cout << a << ' ';
		// }
		// std::cout << "\n";
		
		for (int j = 2; j <= i; j++) {
			tmp[j] -= result[i - 2][j - 2];
		}

		// std::cout << "	";
		// for (int a : tmp) {
		// 	std::cout << a << ' ';
		// }
		// std::cout << "\n";

		result.push_back(tmp);
	}
	return result;
}

std::string format_coeff(int coeff, int power) {
	if (coeff == 0) return "";
	if (coeff == 1) {
		if (power == 0) return " + 1";
		if (power == 1) return " + x";
		if (power > 1) return " + x^" + std::to_string(power);
	}
	if (coeff == -1) {
		if (power == 0) return " - 1";
		if (power == 1) return " - x";
		if (power > 1) return " - x^" + std::to_string(power);
	}
	if (coeff > 1) {
		if (power > 1) return " + " + std::to_string(coeff) + "*x^" + std::to_string(power);
		if (power == 1) return " + " + std::to_string(coeff) + "*x";
		if (power == 0) return " + " + std::to_string(coeff);
	}
	
	if (coeff < -1) {
		if (power > 1) return " - " + std::to_string(-coeff) + "*x^" + std::to_string(power);
		if (power == 1) return " - " + std::to_string(-coeff) + "*x";
		if (power == 0) return " -" + std::to_string(-coeff);
	}
} 

void print_cheb_poly(const std::vector<long long> &coeff) {
	if (coeff.size() > 1) {
		std::cout << coeff[0] << "*x^" << coeff.size() - 1;
	} else {
		std::cout << coeff[0];
		return;
	}
	
	for (int i = 1; i < coeff.size(); i++) {
		std::cout << format_coeff(coeff[i], coeff.size() - i - 1);
	}
	std::cout << "\n";
}