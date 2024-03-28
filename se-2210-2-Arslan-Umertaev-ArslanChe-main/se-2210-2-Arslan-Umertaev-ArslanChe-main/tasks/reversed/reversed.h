#pragma once

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

template <class Container>
class Reversed {
public:
    explicit Reversed(Container& container) : container_(container) {
    }

    auto begin() const {  // NOLINT
        return container_.rbegin();
    }

    auto end() const {  // NOLINT
        return container_.rend();
    }

private:
    Container& container_;
};
