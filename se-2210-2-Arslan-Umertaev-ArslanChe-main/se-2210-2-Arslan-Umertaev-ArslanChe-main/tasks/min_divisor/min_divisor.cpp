#include "min_divisor.h"

int64_t MinDivisor(int64_t number) {
    int64_t d = 2;
    while (d * d <= number) {
        if (number % d == 0) {
            return d;
        }
        d++;
    }
    return number;
}
