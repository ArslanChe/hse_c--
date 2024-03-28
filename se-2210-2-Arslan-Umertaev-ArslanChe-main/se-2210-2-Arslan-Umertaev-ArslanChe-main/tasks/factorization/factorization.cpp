#include "factorization.h"

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> factorization;
    int64_t d = 2;
    while (d * d <= x) {
        if (x % d == 0) {
            int count = 0;
            while (x % d == 0) {
                x /= d;
                ++count;
            }
            factorization.emplace_back(d, count);
        } else {
            ++d;
        }
    }
    if (x != 1) {
        factorization.emplace_back(x, 1);
    }
    return factorization;
}
