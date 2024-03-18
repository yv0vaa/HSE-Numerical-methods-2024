#ifndef CD_HPP
#define CD_HPP

#include <cmath>

class CD {
    constexpr static int arr_size = 37; // numers of reference points 
	constexpr static double CD_val[] = { 
		0.115,
		0.115,
		0.116,
		0.116,
		0.117,
		0.119,
		0.12,
		0.122,
		0.125,
		0.137,
		0.17,
		0.247,
		0.44,
		0.43,
		0.41,
		0.402,
		0.4,
		0.392,
		0.385,
		0.375,
		0.365,
		0.357,
		0.35,
		0.345,
		0.337,
		0.33,
		0.325,
		0.319,
		0.311,
		0.307,
		0.3,
		0.295,
		0.288,
		0.281,
		0.275,
		0.27,
		0.265,		
	};
public:
	double operator()(double M) const;
};

#endif