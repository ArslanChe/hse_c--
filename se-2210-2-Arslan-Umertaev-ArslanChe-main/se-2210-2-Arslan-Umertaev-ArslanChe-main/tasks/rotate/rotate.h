#pragma once
#include <iostream>
template <typename Iterator>
void Reverse(Iterator begin, Iterator end) {
    if (begin == end) {
        return;
    }
    --end;
    while (begin < end) {
        std::iter_swap(begin, end);
        ++begin;
        --end;
    }
}

template <typename Iterator>
void Rotate(Iterator begin, Iterator mid, Iterator end) {
    if (begin == mid || mid == end) {
        return;
    }
    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}
