#ifndef EVERHART_STEPPER_HPP
#define EVERHART_STEPPER_HPP
#include <cmath>
#include <vector>
#include <iostream>

template <typename RHS> class TimeStepperEverhart {
  private:
    RHS const *m_rhs;

  public:
    constexpr static int N = RHS::N;
    constexpr static int k = 5;
    double m_epsilon = 1e-12;

    TimeStepperEverhart(RHS const *a_rhs, double a_epsilon)
        : m_rhs(a_rhs), m_epsilon(a_epsilon) {
    }

  private:
    void initial_approx(std::vector<std::vector<double>> &F, double a_y[N],
                        double a_y_dot[N], double h) {
        m_rhs->operator()(a_y, a_y_dot, F[0]);
        for (int i = 1; i <= k; i++) {
            double tmp_y_dot[N], tmp_y[N];
            double t_diff = h * i / k;
            for (int j = 0; j < N; j++) {
                tmp_y_dot[j] = a_y_dot[j] + F[0][j] * t_diff;
                tmp_y[j] = a_y[j] + a_y_dot[j] * t_diff +
                           F[0][j] * t_diff * t_diff * 0.5;
            }
            m_rhs->operator()(tmp_y, tmp_y_dot, F[i]);
        }
    }

    void compute_differences(std::vector<std::vector<std::vector<double>>> &F,
                             double h) {
        double step = h / k;
        for (int order = 1; order <= k; order++) {
            for (int i = 0; i < F[order - 1].size() - 1; i++) {
                for (int j = 0; j < N; j++) {
                    F[order][i][j] =
                        (F[order - 1][i + 1][j] - F[order - 1][i][j]) /
                        (order * step);
                }
            }
        }
    }
     void compute_Bi(std::vector<std::vector<std::vector<double>>> &F, std::vector<std::vector<double>> &B, double t0, double h) {
        B[5] = F[5][0];
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
    void compute_Bi(const std::vector<std::vector<std::vector<double>>> &F,
                    std::vector<std::vector<double>> &B, double h) {
        B[5] = F[5][0];
        B[0] = F[0][0];
        double delta[] = {h / 5, 2 * h / 5, 3 * h / 5, 4 * h / 5};
        for (int i = 0; i < N; i++) {
            B[1][i] = F[1][0][i] - delta[0] + F[2][0][i] +
                      delta[0] * delta[1] * F[3][0][i] -
                      delta[0] * delta[1] * delta[2] * F[4][0][i] +
                      delta[0] * delta[1] * delta[2] * delta[3] * F[5][0][i];
            B[2][i] = F[2][0][i] - F[3][0][i] * (delta[0] + delta[1]) +
                      F[4][0][i] * (delta[0] * delta[1] + delta[0] * delta[2] +
                                    delta[1] * delta[2]) -
                      F[5][0][i] * (delta[0] * delta[1] * delta[2] + delta[0] +
                                    delta[1] * delta[3] + delta[0] * delta[2] +
                                    delta[3] + delta[1] * delta[2] * delta[3]);
            B[3][i] = F[3][0][i] -
                      F[4][0][i] * (delta[0] + delta[1] + delta[2]) +
                      F[5][0][i] * (delta[0] * delta[1] + delta[0] * delta[2] +
                                    delta[0] * delta[3] + delta[1] * delta[2] +
                                    delta[1] * delta[3] + delta[2] * delta[3]);
            B[4][i] = F[4][0][i] -
                      F[5][0][i] * (delta[0] + delta[1] + delta[2] + delta[3]);
        }
    }

    void compute_y(double a_y[N], double a_y_dot[N], double a_y_next[N],
                   double tau, const std::vector<std::vector<double>> &B) {
        for (int i = 0; i < N; i++) {
            a_y_next[i] = a_y[i] + a_y_dot[i] * tau;
            for (int j = 0; j <= k; j++) {
                a_y_next[i] +=
                    (B[j][i] * std::pow(tau, j + 2)) / ((j + 1) * (j + 2));
            }
        }
    }

    void compute_y_dot(double a_y_dot[N], double a_y_dot_next[N], double tau,
                       const std::vector<std::vector<double>> &B) {
        for (int i = 0; i < N; i++) {
            a_y_dot_next[i] = a_y_dot[i];
            for (int j = 0; j <= k; j++) {
                a_y_dot_next[i] += (B[j][i] * std::pow(tau, j + 1)) / (j + 1);
            }
        }
    }
  public:
    std::pair<double, double> operator()(double a_t, double a_y[N],
                                         double a_y_dot[N], double h,
                                         double a_y_next[N],
                                         double a_y_next_dot[N]) {
        std::vector<std::vector<std::vector<double>>> F(k + 1);
        for (int i = 0; i < F.size(); i++) {
            F[i].resize(k - i + 1, std::vector<double>(N));
        }
        initial_approx(F[0], a_y, a_y_dot, h);
        std::vector<std::vector<double>> B(k + 1, std::vector<double>(N));
        double diff = 1;
        while (diff > m_epsilon) {
            compute_differences(F, h);
            compute_Bi(F, B, h, a_t);
            std::vector<std::vector<double>> new_f(k + 1,
                                                   std::vector<double>(N));
            for (int j = 0; j <= k; j++) {
                double step = (h * j) / k;
                double y_next_tmp[N], y_dot_next_tmp[N];
                compute_y(a_y, a_y_dot, y_next_tmp, step, B);
                compute_y_dot(a_y_dot, y_dot_next_tmp, step, B);
                m_rhs->operator()(y_next_tmp, y_dot_next_tmp, new_f[j]);
            }
            diff = 0;
            double tmp = 0;
            for (int j = 0; j < N; j++) {
                diff = std::max(diff, std::abs(new_f[5][j] - F[0][5][j]));
                tmp = std::max(tmp, std::abs(F[0][5][j]));
            }
            diff /= tmp;
            F[0] = new_f;
        }
        compute_y(a_y, a_y_dot, a_y_next, h, B);
        compute_y_dot(a_y_dot, a_y_next_dot, h, B);
        return {a_t + h, h};
    }
};

#endif