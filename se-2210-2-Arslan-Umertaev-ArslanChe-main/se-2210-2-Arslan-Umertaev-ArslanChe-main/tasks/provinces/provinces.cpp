#include "provinces.h"

#include <queue>
int64_t CountPassports(const std::vector<int>& provinces) {
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> dop{provinces.begin(), provinces.end()};
    int64_t ans = 0;
    while (dop.size() > 1) {
        int64_t smallest1 = dop.top();
        dop.pop();
        int64_t smallest2 = dop.top();
        dop.pop();
        int64_t tmp = smallest1 + smallest2;
        dop.push(tmp);
        ans += tmp;
    }
    return ans;
}
