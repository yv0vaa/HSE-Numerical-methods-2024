#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Observer {
  public:
    bool operator()(double a_curr_t, double const *a_curr_y);
};

#endif
