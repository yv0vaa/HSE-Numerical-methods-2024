#ifndef EVERHART_STEPPER_HPP
#define EVERHART_STEPPER_HPP
#include <vector>

template <typename RHS> class TimeStepperEverhart {
    RHS const * m_rhs;
    void initial_approx(std::vector<std::vector<std::vector<double>>> &F, 
        double a_y[N], double a_y_dot[N], double a_t, double h) {
        m_rhs(a_t, a_y, a_y_dot, f[0][0]);
        for (int i = 1; i < k; i++) {
            std::vector<double> tmp_y_dot(N), tmp_y(N);
            for (int j = 0; j < N; j++) {
                tmp_y_dot[i] = a_y_dot[i] + (h / i) * f[0][0][i];
                tmp_y[i] = a_y[i] + (h / i) * a_y_dot[i] + (h / i) * (h / i) * f[0][0][i] / 2;
            }
            m_rhs(a_t + h / i, tmp_y, tmp_y_dot, F[0][i]);
        }
    }
    // MUST be checked
    void compute_differences(std::vector<std::vector<<std::vector<double>>> &F, double h) {
        double step = h / k;
        for (int i = 1; i < k; i++) {
            for (int j = 0; j < F[i - 1].size(); j++) {
                for (int l = 0; l < N; l++) {
                    F[i][j][l] = (F[i - 1][j + 1][l] - F[i - 1][j][l]) / (i * step);
                }
            }
        }
    }
public:
    constexpr static int N = RHS::N;
    constexpr static int k = 5; //later may be a parametr of the method
    double m_epsilon = 0.001;
    TimeStepperEverhart(RHS const * a_rhs, double a_epsilon) : m_rhs(a_rhs), m_epsilon(a_epsilon){}
    std::pair<double, double> operator()(double a_t, double a_y[N], double a_y_dot[N],
     double h, double a_y_next[N], double a_y_next_dot[N]) {
        std::vector<std::vector<std::vector<double>>> F(k);
        // avoid extra reallocs of arrays
        for (int i = 0; i < F.size(); i++) {
            F[i].resize(i + 1);
            for (auto &elem : F[i]) {
                elem.resize(N);
            }
        }
        initial_approx(F, a_y, a_y_dot, a_t, h);
    }
};
#endif