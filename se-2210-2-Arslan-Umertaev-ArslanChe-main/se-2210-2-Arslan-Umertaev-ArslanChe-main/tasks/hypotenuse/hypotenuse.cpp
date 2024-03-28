#include "hypotenuse.h"

double CalculateHypotenuse(int64_t a, int64_t b) {
    double d_a = static_cast<double>(a);
    double d_b = static_cast<double>(b);
    return sqrt(d_a * d_a + d_b * d_b);
};
