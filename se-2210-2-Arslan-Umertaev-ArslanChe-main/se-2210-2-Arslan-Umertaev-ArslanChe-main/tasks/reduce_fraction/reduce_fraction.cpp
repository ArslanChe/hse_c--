#include "reduce_fraction.h"

int64_t GreatestCommonDivisor(int64_t a, int64_t b) {
    return b ? GreatestCommonDivisor(b, a % b) : a;
}

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t divisor = GreatestCommonDivisor(numerator, denominator);
    int64_t new_numerator = numerator / divisor;
    int64_t new_denominator = denominator / divisor;
    return new_denominator + new_numerator;
}
