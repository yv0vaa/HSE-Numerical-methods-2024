#include "../include/CD.hpp"
#include <cmath>

double CD::operator()(double M) const {
    if (M < 0.4) return this->CD_val[0];
    if (M <= 2) {
        for (int i = 0; i + 1 < this->arr_size; i++) {
            double M_i = 0.4 + i * 0.05;
            double M_i_1 = 0.4 + (i + 1) * 0.05;
            if (M_i <= M && M <= M_i_1) {
                double CD_i = this->CD_val[i];
                double CD_i_1 = this->CD_val[i + 1];
                return CD_i + (CD_i_1 - CD_i) * 20 * (M - M_i);
            }
        }
    }
    return this->a * pow(M, -b);
}
