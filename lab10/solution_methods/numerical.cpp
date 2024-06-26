#include "../include/RiskFreeInterestRate.hpp"
#include "../include/Volatility.hpp"
#include <cmath>
#include <iostream>



class C_calculator {
  private: 
    static const int K = 100;
    static const int n = 500;
    static const int S_tau_max = 0.9 * K;
    static const int tau_max = 1;
    constexpr static double time_step = 0.001;
    static const int C_time_discretation_size =
        1000;  // tau_max / time_step
    Volatility sigma;
    RiskFreeInterestRate r;
    double h = S_tau_max / n;
    double C_i[n + 1][C_time_discretation_size]; 



   public:
    double S(int i) {
         return i * h;
    }
    // call option
    double f(double S) {
        if (S - K > 0) {
            return (S - K);
        }
        return 0.0;
    }

    void compute_initial_conditions() {
        // solving for call option
        for (int t = 0; t < C_time_discretation_size; t++) {
            C_i[0][t] = 0;
        }
        for (int t = 0; t < C_time_discretation_size; t++) {
            C_i[n][t] = 0; // Phi_L in lecture

            double r_integral = r.integral_from_zero_to(t); //Phi_U in lecture
            C_i[n][t] = S_tau_max - K * std::exp(-r_integral);
        }

        for (int i = 0; i < n + 1; i++) {
            double f_value = 0.0;
            if (i != 0 && i != n) {
                f_value = f(S(i));
            }
            C_i[i][0] = f_value;
            
        }
    }
    
};


int main() {
    C_calculator calc;
    calc.compute_initial_conditions();
    return 0;
}