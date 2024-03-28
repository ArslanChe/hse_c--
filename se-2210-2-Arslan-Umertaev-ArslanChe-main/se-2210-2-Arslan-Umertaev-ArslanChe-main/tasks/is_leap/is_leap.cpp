#include "is_leap.h"

bool IsLeap(int year) {
    const int four_hundred = 400;
    const int one_hundred = 100;
    return (year % four_hundred == 0) || (year % 4 == 0 && year % one_hundred != 0);
}
