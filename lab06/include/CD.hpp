#ifndef CD_HPP
#define CD_HPP

#include <cmath>

class CD {
	// constexpr static double *M_i = {};
    constexpr static int arr_size = 31; // numers of reference points 
	constexpr static double CD_val[] = { /* TODO */ };
public:
	double operator()(double M) const;
};

#endif