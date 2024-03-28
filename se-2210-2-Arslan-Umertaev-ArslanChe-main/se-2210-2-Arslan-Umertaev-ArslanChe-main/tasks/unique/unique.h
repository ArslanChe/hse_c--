template <typename T>
T Unique(T begin, T end) {
    if (begin == end) {
        return end;
    }
    T ans = begin;
    ++begin;
    while (begin != end) {
        if (*begin != *ans) {
            ++ans;
            *ans = *begin;
        }
        ++begin;
    }
    return ++ans;
}
