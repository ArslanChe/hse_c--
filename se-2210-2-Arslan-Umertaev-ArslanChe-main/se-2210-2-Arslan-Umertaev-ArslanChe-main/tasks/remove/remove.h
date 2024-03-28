#pragma once

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    auto tmp = begin;
    for (auto i = begin; i != end; ++i) {
        if (*i != value) {
            *tmp = *i;
            ++tmp;
        }
    }
    return tmp;
}
