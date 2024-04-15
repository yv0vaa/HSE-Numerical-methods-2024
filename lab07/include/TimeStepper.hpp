#ifndef TIME_STEPPER_HPP
#define TIME_STEPPER_HPP
#include <utility>
#include <cmath>
template <typename RHS> class TimeStepper_RKF45 {
    private:
        RHS const * const m_rhs;
        constexpr static double alpha[] {
            0.0, 
            0.5,
            0.5,
            1.0,
            2.0 / 3.0,
            0.2
        };
        constexpr static double beta[6][5] {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {1.0 / 4.0, 1.0 / 4.0, 0, 0, 0},
            {0.0, -1.0, 2.0, 0, 0},
            {7.0 / 27.0, 10.0 / 27.0, 0, 1.0 / 27.0, 0},
            {28.0 / 625.0, -1.0 / 5.0, 546.0 / 625.0, 54.0 / 625.0, -328.0 / 625.0}
        };
        constexpr static double gamma[] {
            1.0 / 24.0 ,
            0.0,
            0.0,
            5.0 / 48.0,
            27.0 / 56.0,
            125.0 / 336.0 
        };
        constexpr static double delta[] {
            1.0 / 8.0,
            0.0,
            2.0 / 3.0,
            1.0 / 16.0,
            -27.0 / 56.0,
            -125.0 / 336.0
        };
    public:
        constexpr static int N = RHS::N; // ?
        double m_epsilon = 0.001;
        TimeStepper_RKF45(RHS const * a_rhs, double a_epsilon) : m_rhs(a_rhs), m_epsilon(a_epsilon) {};

        std::pair<double, double> operator()(double a_t, double a_y[N], double h, double a_y_next[N]) {
            double k[6][N];
            this->m_rhs->operator()(a_t, a_y, k[0]);
            for (int i = 1; i < 6; i++) {
                double tmp_buffer[N];
                for (int p = 0; p < N; p++) {
                    tmp_buffer[p] = a_y[p];
                }
                for (int j = 0; j < i; j++) {
                    for (int l = 0; l < N; l++) {
                        tmp_buffer[l] += h * beta[i][j] * k[j][l];
                    }
                }
                this->m_rhs->operator()(a_t, tmp_buffer, k[i]);
            }
            double D[N];
            for (int i = 0; i < N; i++) {
                D[i] = 0;
            }
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < N; j++) {
                    a_y_next[j] = a_y[j] + gamma[i] * k[i][j]; 
                    D[j] += h * delta[i] * k[i][j]; 
                }
            }
            double err = 0;
            for (int i = 0; i < N; i++) {
                err = std::max(err, std::abs(D[i]));
            }
            if (err < m_epsilon) {
                return {a_t + h, h};
            }
            return {a_t + h, 0.9 * h * std::pow(m_epsilon / err, 0.2)};
        }
};

#endif