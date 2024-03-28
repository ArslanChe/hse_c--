#pragma once
#include <istream>
template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

class RangeIterator : public std::iterator<std::input_iterator_tag, int64_t> {
private:
    int64_t current_;
    [[maybe_unused]] int64_t begin_;
    [[maybe_unused]] int64_t end_;
    int64_t step_ = 1;

public:
    RangeIterator(int64_t begin, int64_t end, int64_t step) : current_(begin), begin_(begin), end_(end), step_(step) {
    }

    RangeIterator(int64_t begin, int64_t end, int64_t step, int64_t current)
        : current_(current), begin_(begin), end_(end), step_(step) {
    }
    RangeIterator& operator++() {
        current_ += step_;
        return *this;
    }

    int64_t operator*() const {
        return current_;
    }
    bool operator!=(const RangeIterator rhs) const {
        return current_ < rhs.current_;
    }
};

class Range : public IteratorRange<RangeIterator> {
public:
    Range(int64_t begin, int64_t end, int64_t step = 1)
        : IteratorRange<RangeIterator>(RangeIterator{begin, end, step}, RangeIterator{begin, end, step, end}) {
    }

    explicit Range(int64_t end) : Range(0, end, 1) {
    }
};

template <typename T, typename U>
class ZipIterator {

private:
    T first_;
    U second_;

public:
    ZipIterator(T first, U second) : first_(first), second_(second) {
    }

    auto operator*() const {
        return std::make_pair(*first_, *second_);
    }

    ZipIterator& operator++() {
        ++first_;
        ++second_;
        return *this;
    }
    bool operator!=(const ZipIterator& rhs) const {
        return first_ != rhs.first_ && second_ != rhs.second_;
    }
};

template <typename T>
class GroupIterator {
private:
    T current_;
    T end_;

public:
    GroupIterator(T begin, T end) : current_(begin), end_(end) {
    }
    IteratorRange<T> operator*() {
        T tmp = current_;
        while (tmp != end_ && *tmp == *current_) {
            ++tmp;
        }
        return IteratorRange(current_, tmp);
    }

    GroupIterator& operator++() {
        auto tmp = current_;
        while (true) {
            ++current_;
            if (current_ == end_ || *current_ != *tmp) {
                break;
            }
        }
        return *this;
    }

    bool operator!=(const GroupIterator rhs) const {
        return current_ != rhs.current_;
    }
};

template <typename T, typename U>
auto Zip(const T& first, const U& second) {
    return IteratorRange(ZipIterator(first.begin(), second.begin()), ZipIterator(first.end(), second.end()));
}

template <typename T>
auto Group(const T& ans) {
    return IteratorRange(GroupIterator(ans.begin(), ans.end()), GroupIterator(ans.end(), ans.end()));
}