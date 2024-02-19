#include <vector>
#include <iostream>
#include <gsl/gsl_linalg.h>

enum {N = 100};

long long a_nk(long long n, long long k) {
	if (n % 2 == 0) {
		if (k % 2 == 0) return 0;
		if (k == 1) return n;
		return 2 * n;
	}
	else {
		if (k % 2 == 1) return 0;
		if (k == 0) return n;
		return 2 * n;
	}
}

long long T_0(long long n) {
	if (n % 2 == 1)	return 0;
	if (n % 4 == 0) return 1;
	return -1;
}

std::vector<std::vector<long long>> SLE_coefficients() {
	std::vector<std::vector<long long>> result(N + 1, std::vector<long long>(N + 1));
	for (int k = 0; k <= N - 1; k++) {
		result[k][k] = -1;
		for (int n = k + 1; n <= N; n++) {
			result[k][n] = a_nk(n, k);
		}
	}
	for (int n = 0; n <= N; n++) {
		result[N][n] = T_0(n);
	}
	return result;
}

// converts vector<long long> to double[]
double *v_to_array(std::vector<long long> &vec) {
	static double data[(N + 1) * (N + 1)];
	for (int j = 0; j < N + 1; j++) {
		data[j] = static_cast<double>(vec[j]);
	}
	return data;
}

// converts vector<vector<long long>> to double[]
double *vv_to_array(std::vector<std::vector<long long>> &vecvec) {
	static double data[(N + 1) * (N + 1)];
	for (int i = 0; i < N + 1; i++) {
		for (int j = 0; j < N + 1; j++) {
			data[i * (N + 1) + j] = static_cast<double>(vecvec[i][j]);
		}
	}
	return data;
}

int main() {
	std::vector<std::vector<long long>> coeffs = SLE_coefficients();
	for (int i = 0; i < coeffs.size(); i++) {
		for (int j = 0; j < coeffs[i].size(); j++) {
			std::cout << coeffs[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::vector<long long> RHS(N + 1);
	RHS[N] = 1;

	//now we need to solve linear system with[ SLE_coefficients * C = RHS ]

	// Convert 
	double *matrix = vv_to_array(coeffs);
	gsl_matrix_view A = gsl_matrix_view_array(matrix, N + 1, N + 1);
	std::cout << "A = \n";
	gsl_matrix_fprintf(stdout, &A.matrix, "%lf");

	double *vec = v_to_array(RHS);
	gsl_vector_view b = gsl_vector_view_array(vec, N + 1);
	std::cout << "b = \n";
	gsl_vector_fprintf(stdout, &b.vector, "%lf");

	gsl_vector *x = gsl_vector_alloc(N + 1);
	gsl_permutation *perm = gsl_permutation_alloc(N + 1);

	// Decompose A into the LU form:
	int signum;
	gsl_linalg_LU_decomp(&A.matrix, perm, &signum);

	// Solve the linear system
	gsl_linalg_LU_solve(&A.matrix, perm, &b.vector, x);

	// Print the solution
	std::cout << "\nx = \n";
	gsl_vector_fprintf(stdout, x, "%lf");

	// Release the memory previously allocated for x and perm
	gsl_vector_free(x);
	gsl_permutation_free(perm);
}