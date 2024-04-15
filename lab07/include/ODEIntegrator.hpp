#ifndef ODE_INTEGRATOR_HPP
#define ODE_INTEGRATOR_HPP
#include "Observer.hpp"

template <typename Stepper, typename Observer> class ODE_Integrator {
  private:
    Stepper *const m_stepper;
    Observer *const m_observer;
    double integration_step;

  public:
    ODE_Integrator(Stepper *a_stepper, Observer *a_observer, double a_step)
        : m_stepper(a_stepper), m_observer(a_observer), integration_step(a_step){};

    void operator()(double a_t0, double a_y0[Stepper::N], double a_tEnd,
                    double a_yEnd[Stepper::N]) {
        double current_t = a_t0;
        while (current_t < a_tEnd) {
            std::pair<double, double> step_result = m_stepper->operator()(current_t, a_y0, integration_step, a_y0);
            bool should_continue = m_observer->operator()(current_t, Stepper::N, a_y0);
            if (!(should_continue)) {
                break;
            }
            current_t = step_result.first;
            integration_step = step_result.second;
        }
        for (int i = 0; i < Stepper::N; i++) {
            a_yEnd[i] = a_y0[i];
        }
    }
};

#endif

