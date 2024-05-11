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
                        double a_y_dot[N], double a_t, double h) {
        m_rhs->operator()(a_y, a_y_dot, F[0]);
        for (int i = 1; i <= k; i++) {
            std::vector<double> tmp_y_dot(N), tmp_y(N);
            double t_diff = h * i / k;
            for (int j = 0; j < N; j++) {
                tmp_y_dot[j] = a_y_dot[j] + F[0][j] * t_diff;
                tmp_y[j] = a_y[j] + a_y_dot[j] * t_diff +
                           F[0][j] * (t_diff * t_diff / 2);
            }
            m_rhs->operator()(&tmp_y[0], &tmp_y_dot[0], F[i]);
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

    void compute_Bi(const std::vector<std::vector<std::vector<double>>> &F,
                    std::vector<std::vector<double>> &B, double t0, double h) {
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
        initial_approx(F[0], a_y, a_y_dot, a_t, h);
        double err = 0;
        do {
            err = 0;
            compute_differences(F, h);
            std::vector<std::vector<double>> B(k + 1, std::vector<double>(N));
            compute_Bi(F, B, a_t, h);
            std::vector<std::vector<double>> new_f(k + 1,
                                                   std::vector<double>(N));
            for (int j = 0; j <= k; j++) {
                double step = (h * j) / k;
                double y_next_tmp[N], y_dot_next_tmp[N];
                compute_y(a_y, a_y_dot, y_next_tmp, step, B);
                compute_y_dot(a_y_dot, y_dot_next_tmp, step, B);
                m_rhs->operator()(y_next_tmp, y_dot_next_tmp, new_f[j]);
            }
            compute_y(a_y, a_y_dot, a_y_next, h, B);
            compute_y_dot(a_y_dot, a_y_next_dot, h, B);
            for (int j = 0; j < N; j++) {
                for (int l = 0; l <= k; l++) {
                    err = std::max(err, std::abs(new_f[l][j] - F[0][l][j]));
                }
            }
            F[0] = new_f;
        } while (err > m_epsilon);
        return {a_t + h, h};
    }
};

#endif