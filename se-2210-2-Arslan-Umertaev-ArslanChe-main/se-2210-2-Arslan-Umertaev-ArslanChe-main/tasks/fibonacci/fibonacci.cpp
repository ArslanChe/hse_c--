#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {

    int64_t first = 0;
    int64_t second = 1;
    int64_t temp = 0;
    for (int i = 0; i < n; ++i) {
        temp = first;
        first = second;
        second = temp + first;
    }
    return first;
}
