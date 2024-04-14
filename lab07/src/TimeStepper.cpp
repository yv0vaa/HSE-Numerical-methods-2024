template <typename RHS> class TimeStepper_RKF45 {
    private:
        RHS const * const m_rhs;
        // K1, ... buffers
    public:
        constexpr static int N = RHS::N; // ?

        TimeStepper_RKF45(RHS const * a_rhs) : m_rhs(a_rhs) {};

        std::pair<double, double> operator()(double a_t, double a_y[N], double h, double a_y_next[N]) {
            // TODO: RKF45 method
        }
};
