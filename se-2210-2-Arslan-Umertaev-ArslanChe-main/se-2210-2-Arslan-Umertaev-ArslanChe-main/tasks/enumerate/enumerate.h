#pragma once
#include <iostream>
#include <memory>
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

template <class Iterator>
class PairIterator {
public:
    explicit PairIterator(Iterator iterator, size_t index = 0) : iterator_(iterator), index_(index) {
    }
    ~PairIterator() = default;

    bool operator!=(const PairIterator &other) const {
        return iterator_ != other.iterator_;
    }

    PairIterator &operator++() {
        ++iterator_;
        ++index_;
        return *this;
    }
    auto operator*() const {
        return std::tie(index_, *iterator_);
    }

private:
    Iterator iterator_;
    size_t index_;
};

template <class Iterator>
IteratorRange<Iterator> MakeIteratorRange(const Iterator &begin, const Iterator &end) {
    return IteratorRange<Iterator>(begin, end);
}
template <class Iterator>
auto Enumerate(Iterator &it) {
    return MakeIteratorRange(PairIterator(it.begin()), PairIterator(it.end()));
}
