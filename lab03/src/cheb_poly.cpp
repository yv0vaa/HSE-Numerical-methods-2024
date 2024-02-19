#include "../include/cheb_poly.hpp" 

std::vector<std::vector<long long>> cheb_poly(int n) {
	std::vector<std::vector<long long>> result {
		{1},
		{1, 0}
	};
	for (int i = 2; i <= n; i++) {
		std::vector<long long> tmp(result[i - 1].size() + 1);
		for (int j = 0; j < i - 1; j++) {
			tmp[j] = 2 * result[i - 1][j];
		}
		for (int j = 2; j <= i; j++) {
			tmp[j] -= result[i - 2][j - 2];
		}
		result.push_back(tmp);
	}
	return result;
}