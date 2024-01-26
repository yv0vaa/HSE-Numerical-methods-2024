#include "exp.hpp"
#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

const int FORMAT1 = 18;
const int FORMAT2 = 15;
const int FORMAT3 = 16;
const int FORMAT4 = 12;
const int PRECISION = 10;

template <typename F> void test_value(F x) {
    F expected = std::exp(x);
    F actual = ADAAI::Exp(x);
    F delta = (expected > actual) ? expected - actual : actual - expected;
    std::cout << " ";
    if (x > 0) {
        std::cout << " " << std::setw(FORMAT2 - 1) << std::left
                  << std::setprecision(PRECISION) << x;
    } else {
        std::cout << std::setw(FORMAT2) << std::left 
                  << std::setprecision(PRECISION) << x;
    }
    std::cout << "| " 
        << std::setw(FORMAT3) << std::left << std::setprecision(PRECISION) 
        << expected << "| "
        << std::setw(FORMAT4) << std::left << std::setprecision(PRECISION)
        << actual << "| " 
        << std::setw(FORMAT4) << std::left << std::setprecision(PRECISION)
        << delta << "\n";
}

// Program can be called without args, then 5 tests will be conducted, 
// otherwise, specified number of tests will be conducted.
int main(int argc, char **argv) {
    int tests_count = 5;
    if (argc > 1) {
        tests_count = strtol(argv[1], NULL, 10);
    }

    long double lower_bound = -100;
    long double upper_bound = 100;
    std::uniform_real_distribution<long double> unif(lower_bound, upper_bound);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> gen(0, 2);

    // Random value is calculated as a random double 
    // divided by another random double.
    long double random_double1 = 0.0;
    long double random_double2 = 0.0;

    // Value will be randomly casted from long double to 
    // float (0), double (1) or long double (2).
    int arg_type = 0;

    std::cout << std::setw(FORMAT1) << std::left << "    VALUE TYPE" << "|"
              << std::setw(FORMAT2 + 1) << "     VALUE"
              << "|"
              << std::setw(FORMAT3 + 1) << " EXPECTED RESULT"
              << "|" << std::setw(FORMAT4 + 1) << " OUR RESULT"
              << "|" << std::setw(FORMAT4) <<  "    DELTA" << std::endl;
    for (int i = 0; i < FORMAT1 + FORMAT2 + FORMAT3 + 3 * FORMAT4; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (;tests_count >= 0; tests_count--) {
        random_double1 = unif(rng);
        random_double2 = unif(rng);
        // Calculate value for testing
        long double random_double = random_double1 / random_double2;
        // Determine value type
        arg_type = gen(rng);
        switch (arg_type) { 
            case 0: 
                std::cout << std::setw(FORMAT1) << std::left << "FLOAT VALUE"
                          << "|";
                test_value(static_cast<float>(random_double));
                break;
            case 1: 
                std::cout << std::setw(FORMAT1) << std::left 
                          << "DOUBLE VALUE"
                          << "|";
                test_value(static_cast<double>(random_double));
                break;
            case 2: 
                std::cout << std::setw(FORMAT1  ) << std::left
                          << "LONG DOUBLE VALUE" 
                          << "|";
                test_value(static_cast<long double>(random_double));
        }
    }
}