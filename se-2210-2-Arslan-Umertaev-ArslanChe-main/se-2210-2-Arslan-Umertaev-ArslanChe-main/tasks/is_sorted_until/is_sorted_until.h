#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    for (auto i = begin + 1; i < end; ++i) {
        if (*i < *(i - 1)) {
            return i;
        }
    }
    return end;
}
