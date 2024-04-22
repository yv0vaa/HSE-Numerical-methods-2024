#ifndef EVERHART_STEPPER_HPP
#define EVERHART_STEPPER_HPP
#include <vector>

template <typename RHS> class TimeStepperEverhart {
    RHS const * m_rhs;
private:
    void initial_approx(std::vector<std::vector<double>> &F, double a_y[N], double a_y_dot[N], double a_t, double h) {
        m_rhs(a_t, a_y, a_y_dot, F[0]);
        for (int i = 1; i <= k; i++) {
            std::vector<double> tmp_y_dot(N), tmp_y(N);
            double t_diff = h * i / k;
            for (int j = 0; j < N; j++) {
                tmp_y_dot[j] = a_y_dot[j] + F[0][j] * t_diff;
                tmp_y[j] = a_y[j] + a_y_dot[j] * t_diff + F[0][j] * (t_diff * t_diff / 2);
            }
            m_rhs(a_t + t_diff, tmp_y, tmp_y_dot, F[i]);
        }
    }

    void compute_differences(std::vector<std::vector<std::vector<double>>> &F, double h) {
        double step = h / k;
        for (int order = 1; order <= k; order++) {
            for (int i = 0; i < F[order - 1].size() - 1; i++) {
                for (int j = 0; j < N; j++) {
                    F[order][i][j] = (F[order - 1][i + 1][j] - F[order - 1][i][j]) / (order * step);
                }
            }
        }
    }

    void compute_Bi(std::vector<std::vector<std::vector<double>>> &F, std::vector<std::vector<double>> &B, double t0, double h) {
        B[5] = F[5][0];
        // Precalculate powers of t0 and h
        double t02 = t0 * t0;
        double t03 = t02 * t0;
        double t04 = t03 * t0;
        double t05 = t04 * t0;
        double h2 = h * h;
        double h3 = h2 * h;
        double h4 = h3 * h;
        for (int i = 0; i < N; i++) {
            B[4][i] = F[4][0][i] - F[5][0][i] * (10 * t0 + 2 * h);
            B[3][i] = F[3][0][i] - F[4][0][i] * (4 * t0 + 1.2 * h) + F[5][0][i] * (10 * t02 + 8 * t0 * h + 2.48 * h2) + 4 * B[4][i] * t0 - 10 * B[5][i] * t02;
            B[2][i] = F[2][0][i] - F[3][0][i] * (3 * t0 + 0.6 * h) + F[4][0][i] * (6 * t02 + 0.36 * t0 * h + 0.44 * h2) - F[5][0][i] * (10 * t03 + 12 * t02 * h + 4.2 * t0 * h2 + 0.4 * h3) + 3 * B[3][i] * t0 - 6 * B[4][i] * t02 + 10 * B[5][i] * t03;
            B[1][i] = F[1][0][i] - F[2][0][i] * (2 * t0 + 0.2 * h) + F[3][0][i] * (3 * t02 + 1.2 * t0 * h + 0.08 * h2) - F[4][0][i] * (4 * t03 + 3.6 * t02 * h + 0.88 * t0 * h2 + 0.048 * h3) + F[5][0][i] * (5 * t04 + 8 * t03 * h + 4.2 * t02 * h2 + 0.8 * t0 * h3 + 0.0384 * h4) + 2 * B[2][i] * t0 - 3 * B[3][i] * t02 + 4 * B[4][i] * t03 - 5 * B[5][i] * t04;
            B[0][i] = F[0][0][i] - F[1][0][i] * t0 + F[2][0][i] * (t02 + 0.2 * t0 * h) - F[3][0][i] * (t03 + 0.6 * t02 * h + 0.08 * t0 * h2) + F[4][0][i] * (t04 + 1.2 * t03 * h + 0.44 * t02 * h2 + 0.048 * t0 * h3) - F[5][0][i] * (t05 + 2 * t04 * h + 1.4 * t03 * h2 + 0.4 * t02 * h3 + 0.0384 * t0 * h4) + B[1][i] * t0 - B[2][i] * t02 + B[3][i] * t03 - B[4][i] * t04 + B[5][i] * t05;
        }
    }

public:
    constexpr static int N = RHS::N;
    constexpr static int k = 5; //later may be a parameter of the method (doubt)
    double m_epsilon = 0.001;

    TimeStepperEverhart(RHS const * a_rhs, double a_epsilon) : m_rhs(a_rhs), m_epsilon(a_epsilon) {} ;

    std::pair<double, double> operator()(double a_t, double a_y[N], double a_y_dot[N], double h, double a_y_next[N], double a_y_next_dot[N]) {
        std::vector<std::vector<std::vector<double>>> F(k + 1);
        // avoid extra reallocs of arrays
        for (int i = 0; i < F.size(); i++) { 
            F[i].resize(k - i + 1, std::vector<double>(N)); 
        }
        initial_approx(F[0], a_y, a_y_dot, a_t, h);
        compute_differences(F, h);
        std::vector<std::vector<double>> B(k + 1, std::vector<double>(N));
        compute_Bi(F, B, a_t, h);
    }
};

#endif