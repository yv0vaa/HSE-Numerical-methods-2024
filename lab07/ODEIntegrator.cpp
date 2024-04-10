template <typename Stepper, typename Observer> class ODE_Integrator {
    private:
        Stepper * const m_stepper;
        Observer const * const m_observer;
    public:
        ODE_Integrator(Stpper *a_stepper, Observer const *a_observer) : m_stepper(a_stepper), m_observer(a_observer) {};
        void operator()(double a_t0, double a_y0[Stepper::N], double a_tEnd, double a_yEnd[Stepper::N]) {
            // TODO: invoke stepper in a loop, call m_observer after each step
        }

};