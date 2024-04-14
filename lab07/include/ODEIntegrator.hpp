#ifndef ODE_INTEGRATOR_HPP
#define ODE_INTEGRATOR_HPP
#include "Observer.hpp"

template <typename Stepper, typename Observer> class ODE_Integrator {
  private:
    Stepper *const m_stepper;
    Observer const *const m_observer;

  public:
    ODE_Integrator(Stpper *a_stepper, Observer const *a_observer)
        : m_stepper(a_stepper), m_observer(a_observer){};

    void operator()(double a_t0, double a_y0[Stepper::N], double a_tEnd,
                    double a_yEnd[Stepper::N]) {
        double t_h = 0.0001;
        double current_t = a_t0;
        while (current_t < a_tEnd) {
            // call stepper m_stepper
            bool should_continue = m_observer(current_t, Stepper::N, a_y0);
            if (not should_continue) {
                break;
            }
            current_t += t_h;
        }
        for (int i = 0; i < Stepper::N; i++) {
            a_yEnd[i] = a_y0[i];
        }
    }
};

#endif