#define _USE_MATH_DEFINES 
#include <iostream>
#include <stdio.h>
#include <type_traits>
#include <cmath>
#include <math.h>
#include <cfloat>
using namespace std;

template<typename F>
constexpr inline F Ln2;
template<>
constexpr float Ln2<float> =M_LN2;
template<>
constexpr double Ln2<double> = M_LN2;
template<>
constexpr long double Ln2<long double> = M_LN2;

template<typename F>
constexpr inline F EPS;
template<>
constexpr float EPS<float> = FLT_EPSILON;
template<>
constexpr double Ln2<double> = DBL_EPSILON;
template<>
constexpr long double Ln2<long double> = LDBL_EPSILON;

template <typename F>
constexpr F Exp(F value) {
	static_assert(is_floating_point_v<F>);
	F n;
	F y = modf(value, &n);
	if ((y > 0.5) || (y < -0.5)) {
		if (y > 0) {
			n += 1;
			y = 1 - y;
		}
		else {
			n -= 1;
			y = 1 + y;
		}
	}
	if (n > INT16_MAX) return float('+inf');
	if (n < INT16_MIN) return 0;
	int new_n = (int)n;
	F delta = 10.0 * EPS<F>;
	//F ans = ldexp(new_n, f1);
	return y;
}

int main() {
	double x = 1.5;
	cout << Exp(x);
}
