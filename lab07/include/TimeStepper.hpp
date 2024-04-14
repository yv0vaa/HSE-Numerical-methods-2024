#ifndef TIME_STEPPER_HPP
#define TIME_STEPPER_HPP

template <typename RHS> class TimeStepper_RKF45 {
    private:
        RHS const * const m_rhs;
        constexpr static double alpha {
            0.0, 
            0.5,
            0.5,
            1.0,
            2.0 / 3.0,
            0.2
        };
        constexpr static double beta {
            {0},
            {0},
            {1.0 / 4.0, 1.0 / 4.0},
            {0.0, -1.0, 2.0},
            {7.0 / 27.0, 10.0 / 27.0, 0, 1.0 / 27.0},
            {28.0 / 625.0, -1.0 / 5.0, 546.0 / 625.0, 54.0 / 625.0, -328.0 / 625.0}
        };
        constexpr static double gamma {
            1.0 / 24.0 ,
            0.0,
            0.0,
            5.0 / 48.0,
            27.0 / 56.0,
            125.0 / 336.0 
        };
    public:
        constexpr static int N = RHS::N; // ?

        TimeStepper_RKF45(RHS const * a_rhs) : m_rhs(a_rhs) {};

        std::pair<double, double> operator()(double a_t, double a_y[N], double h, double a_y_next[N]) {
            double k[6][N];
            k[0][N] = this->m_rhs(a_t, a_y)
            for (int i = 1; i < 6; i++) {
                double tmp_buffer[N];
                for (int j = 0; j < i; j++) {
                    for (int l = 0; l < N; l++) {
                        tmp_buffer = a_y[l] + h * beta[i][j] * k[j][l];
                    }
                }
                k[i][N] = this->rhs(a_t, tmp_buffer);
            }
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < N; j++) {
                    a_y_next[j] = a_y[j] + gamma[i] * k[i][j]; 
                }
            }
            return {a_t + h, h}
        }
};

#endif