#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    for (auto i = begin; i < end; ++i) {
        for (auto j = begin; j < end - 1; ++j) {
            if (comparator(*(j + 1), *j)) {
                std::swap(*j, *(j + 1));
            }
        }
    }
}
