#include "../include/Dencity.hpp"
#include <iostream>
double Density::pressure(double height) const {
	if (this->h[0] <= height && height <= this->h[1]){
		return this->p[0] * std::exp((this->g * std::log(1 - (this->r[0] * (height - this->h[0])) / (this->T[0]))) / (this->R * this->r[0]));
	} else if (this->h[1] <= height && height <= this->h[2]) {
		return this->p[1] * std::exp((-this->g * (height - this->h[1])) / (this->R * this->T[1]));
	} else if (this->h[2] <= height && height <= this->h[3]) {
		return this->p[2] * std::exp((this->g * std::log(1 - (this->r[2] * (height - this->h[2])) / (this->T[2]))) / (this->R * this->r[2]));
	}
	return this->p[3] * std::exp((this->g * std::log(1 - (this->r[3] * (height - this->h[3])) / (this->T[3]))) / (this->R * this->r[3]));
}

double Density::operator()(double height) const {
	return this->pressure(height) / (this->R * this->temperature(height));
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

Density::Density() {
	for (int i = 1; i < 4; i++) {
		this->T[i] = this->temperature(this->h[i]);
		this->p[i] = this->pressure(this->h[i]);
	}
}