#include "../include/Pressure.hpp"

double Pressure::operator()(double height) const {
	// simple case when rl = 0
	if (this->h1 <= height && height <= this->h2) {
		return p1 * std::exp((-this->g * (height - this->h1)) / (this->R * this->T1)); 
	}
	// TODO: deal with other cases
	double r, h, T, p;
	if (this->h0 <= height && height <= this->h1) {

	} else if (this->h2 <= height && height <= this->h3) {

	}
	return p * std::exp((this->g * std::log(1 - (r * (height - h)) / T)) / (this->R * r));
}