#ifndef OBSERVER_HPP
#define OBSERVER_HPP

enum class ObserveMethod {
    ReturnCoordinates,
    CheckMaxRange
};

class Observer {
  private:
    ObserveMethod observe_method;
  public:
    Observer(ObserveMethod method) : observe_method(method){};

    bool operator()(double a_curr_t, int a_n,
                    double const *a_curr_y);
};

#endif