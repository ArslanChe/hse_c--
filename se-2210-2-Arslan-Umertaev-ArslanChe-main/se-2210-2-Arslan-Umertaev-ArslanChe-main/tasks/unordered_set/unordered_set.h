#pragma once
// NOLINTBEGIN
#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : n_elements_(0), data_(std::vector<std::list<KeyT>>(0)) {
    }
    explicit UnorderedSet(size_t count) : n_elements_(0) {
        data_.resize(count);
        std::fill(data_.begin(), data_.end(), std::list<KeyT>());
    }
    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : n_elements_(std::distance(first, last)) {
        for (IteratorType i = first; i != last; ++i) {
            data_.emplace_back(1, *i);
        }
    }
    UnorderedSet(const UnorderedSet& other) : n_elements_(other.n_elements_) {
        data_.resize(n_elements_);
        std::copy(other.data_.begin(), other.data_.end(), data_.begin());
    }
    UnorderedSet(UnorderedSet&& other) : n_elements_(other.n_elements_), data_(std::move(other.data_)) {
        other.n_elements_ = 0;
        other.data_.clear();
    }
    ~UnorderedSet() = default;
    UnorderedSet& operator=(const UnorderedSet& other) {
        Clear();
        data_.resize(other.n_elements_);
        n_elements_ = other.n_elements_;
        std::copy(other.data_.begin(), other.data_.end(), data_.begin());
        return *this;
    }
    UnorderedSet& operator=(UnorderedSet&& other) {
        Clear();
        data_ = std::move(other.data_);
        n_elements_ = other.n_elements_;
        other.n_elements_ = 0;
        other.data_.clear();
        return *this;
    }

    size_t Size() const {
        return n_elements_;
    }

    bool Empty() const {
        return n_elements_ == 0;
    }

    void Clear() {
        n_elements_ = 0;
        data_.clear();
    }
    void Insert(const KeyT& key) {
        if (data_.empty()) {
            data_.resize(1);
        } else if (n_elements_ == data_.size()) {
            data_.resize(n_elements_ * 2);
        }
        data_[n_elements_++].push_back(key);
    }
    void Insert(KeyT&& key) {
        if (data_.empty()) {
            data_.resize(1);
        } else if (n_elements_ == data_.size()) {
            data_.resize(n_elements_ * 2);
        }
        data_[n_elements_++].push_back(std::move(key));
    }
    void Erase(const KeyT& key) {
        for (auto& list : data_) {
            auto it = std::find(list.begin(), list.end(), key);
            if (it != list.end()) {
                list.erase(it);
                --n_elements_;
                break;
            }
        }
    }
    bool Find(const KeyT& key) const {
        for (const auto& list : data_) {
            if (std::find(list.begin(), list.end(), key) != list.end()) {
                return true;
            }
        }
        return false;
    }
    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count >= n_elements_) {
            data_.resize(new_bucket_count);
        }
    }

    void Reserve(size_t new_bucket_count) {
        if (new_bucket_count > n_elements_) {
            data_.resize(new_bucket_count);
        }
    }
    size_t BucketCount() const {
        return data_.size();
    }

    size_t BucketSize(size_t id) const {
        if (id >= data_.size() || n_elements_ == 0) {
            return 0;
        }
        return data_[id].size();
    }
    size_t Bucket(const KeyT& key) const {
        return std::hash<KeyT>{}(key) % data_.size();
    }
    double LoadFactor() const {
        return n_elements_ == 0 ? 0 : static_cast<double>(n_elements_) / data_.size();
    }

private:
    size_t n_elements_;
    std::vector<std::list<KeyT>> data_;
};
// NOLINTEND