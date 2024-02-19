#include <vector>
#include <iostream>
long long a_coeficient(long long n, long long k) {
	if (n % 2 == 0) {
		if (k % 2 == 0) {
			return 0;
		}
		else if (k == 1) {
			return n;
		}
		return 2 * n;
	}
	else {
		if (k % 2 == 1) {
			return 0;
		}
		else if (k == 0) {
			return n;
		}
		return 2 * n;
	}
}

long long T_0(long long n) {
	if (n % 2 == 1) {
		return 0;
	}
	else if (n % 4 == 0) {
		return 1;
	}
	else {
		return -1;
	}
}
std::vector<std::vector<long long>> cheb_coefficients(long long N) {
	std::vector<std::vector<long long>> result(N+1);
	for (int i = 0; i < N + 1; i++) {
		result[i].resize(N + 1);
	}
	for (int k = 0; k < N; k++) {
		result[k][k] = -1;
		for (int n = k + 1; n < N + 1; n++) {
			result[k][n] = a_coeficient(n, k);
		}
	}
	for (int n = 0; n < N+1; n++) {
		result[N][n] = T_0(n);
	}
	return result;
}

int main() {
	int N = 3;
	std::vector<std::vector<long long>> test = cheb_coefficients(N);
	for (int i = 0; i < test.size(); i++) {
		for (int j = 0; j < test[i].size(); j++) {
			std::cout << test[i][j] << " ";
		}
		std::count << std::endl;
	}
	std::vector<long long> RHS(N + 1);
	RHS(N) = 1;
	//now we need to solve linear system with[ cheb coefficients = RHS ]
}