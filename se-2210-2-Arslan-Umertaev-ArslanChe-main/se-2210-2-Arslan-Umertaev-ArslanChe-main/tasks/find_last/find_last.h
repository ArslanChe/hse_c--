#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    Iterator ans;
    for (auto i = first; i < last; ++i) {
        if (*i == val) {
            ans = i;
        }
    }
    return ans != Iterator() ? ans : last;
}
