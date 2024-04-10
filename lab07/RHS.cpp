// should be modified for our task
class RHS {
    private:
        double const m_omega2;
    public:
        constexpr static int N = 2;

        RHS(double a_omega) : m_omega2(a_omega * a_omega) {} ;
        
        void operator()(double a_t, double a_y[N], double a_rhs[N]) const {
            a_rhs[0] = a_y[1];
            a_rhs[1] = - m_omega2 * a_y[0]; 
        }
};