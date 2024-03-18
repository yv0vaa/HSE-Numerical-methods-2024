#include "../include/Dencity.hpp"

double Density::pressure(double height) const {
	if (this->h[1] <= height && height <= this->h[2]) {
		return this->p[1] * std::exp((-this->g * (height - this->h[1])) / (this->R * this->T[1])); 
	}
	double r, h, T, p;
	int idx = 0;
	if (this->h[2] <= height && height <= this->h[3]) {
		idx = 2;
	} else {
		idx = 3;
	}
	r = this->r[idx], h = this->h[idx], p = this->p[idx], T = this->T[idx];
	return p * std::exp((this->g * std::log(1 - (r * (height - h)) / T)) / (this->R * r));
}

double Density::operator()(double height) const {
	int idx = -1;
	if (this->h[0] <= height && height <= this->h[1]) {
		idx = 0;
	} else if (this->h[1] <= height && height <= this->h[2]) {
		idx = 1;
	} else if (this->h[2] <= height && height <= this->h[3]) {
		idx = 2;
	} else {
		idx = 3;
	}
	return this->pressure(height) / (this->R * (this->T[idx] - this->r[idx] *(height - this->h[idx])));
}

double Density::temperature(double height) const {
	int idx = -1;
	if (this->h[0] <= height && height <= this->h[1]) {
		idx = 0;
	} else if (this->h[1] <= height && height <= this->h[2]) {
		idx = 1;
	} else if (this->h[2] <= height && height <= this->h[3]) {
		idx = 2;
	} else {
		idx = 3;
	}
	return this->T[idx] - this->r[idx] * (height - this->h[idx]);
}