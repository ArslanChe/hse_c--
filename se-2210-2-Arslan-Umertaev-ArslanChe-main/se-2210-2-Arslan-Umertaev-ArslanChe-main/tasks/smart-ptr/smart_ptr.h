
#pragma once
// NOLINTBEGIN
#include <set>
#include <string>

struct Counter {
    size_t shared;
    size_t weak;
    bool weak_exp = false;
    Counter(size_t s, size_t w) {
        shared = s;
        weak = w;
    }
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
    friend class WeakPtr<T>;
    T* ptr_ = nullptr;
    Counter* counter_ = nullptr;

public:
    SharedPtr() : ptr_(nullptr), counter_(new Counter(1, 0)) {
    }

    ~SharedPtr() {
        --counter_->shared;

        if (counter_->shared == 0) {
            delete ptr_;
            ptr_ = nullptr;
            counter_->weak_exp = true;
            if (counter_->weak == 0) {
                delete counter_;
            }
        }
    }

    SharedPtr(const SharedPtr<T>& other) : ptr_(other.ptr_) {
        if (other.ptr_ != nullptr) {
            counter_ = other.counter_;
            ++counter_->shared;
        } else {
            counter_ = new Counter(1, 0);
        }
    }

    SharedPtr(SharedPtr<T>&& other) : ptr_(other.ptr_), counter_(other.counter_) {
        other.counter_ = new Counter(1, 0);
        other.ptr_ = nullptr;
    }

    void operator=(const SharedPtr<T>& other) {
        --counter_->shared;
        if (counter_->shared == 0) {
            delete ptr_;
            ptr_ = nullptr;
        }
        if (counter_->shared + counter_->weak == 0) {
            delete counter_;
        }
        if (other.ptr_ != nullptr) {
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            ++counter_->shared;
        } else {
            counter_ = new Counter(1, 0);
            ptr_ = nullptr;
        }
    }

    void operator=(SharedPtr<T>&& other) {
        --counter_->shared;
        if (counter_->shared == 0) {
            delete ptr_;
            ptr_ = nullptr;
        }
        if (counter_->shared + counter_->weak == 0) {
            delete counter_;
        }
        if (other.ptr_ != nullptr) {
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            other.counter_ = new Counter(1, 0);
            other.ptr_ = nullptr;
        } else {
            counter_ = new Counter(1, 0);
        }
    }

    explicit SharedPtr(T* value) {
        ptr_ = value;
        counter_ = new Counter(1, 0);
    }

    T operator*() {
        return *ptr_;
    }

    void Reset(T* dop) {
        --counter_->shared;
        if (counter_->shared == 0) {
            delete ptr_;
            ptr_ = nullptr;
        }
        if (counter_->shared + counter_->weak == 0) {
            delete counter_;
        }
        ptr_ = dop;
        counter_ = new Counter(1, 0);
    }

    T* Get() {
        return ptr_;
    }

    explicit SharedPtr(const WeakPtr<T>& rhs);
};

template <class T>
class WeakPtr {
    friend class SharedPtr<T>;
    T* ptr_ = nullptr;
    Counter* counter_ = nullptr;

public:
    WeakPtr() {
        ptr_ = nullptr;
        counter_ = new Counter(0, 1);
        counter_->weak_exp = true;
    }

    ~WeakPtr() {
        --counter_->weak;

        if (counter_->shared == 0) {
            if (!counter_->weak_exp) {
                delete ptr_;
                ptr_ = nullptr;
                counter_->weak_exp = true;
            }
            if (counter_->weak == 0) {
                delete counter_;
            }
        }
    }

    WeakPtr(const WeakPtr<T>& other) {
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        ++counter_->weak;
    }

    explicit WeakPtr(const SharedPtr<T>& other) {
        ptr_ = other.ptr_;
        if (ptr_) {
            counter_ = other.counter_;
            ++counter_->weak;
        } else {
            counter_ = new Counter(0, 1);
            counter_->weak_exp = true;
        }
    }

    WeakPtr(WeakPtr<T>&& other) {
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        other.counter_ = new Counter(0, 1);
        other.ptr_ = nullptr;
        ++counter_->weak;
    }

    bool IsExpired() const {
        return counter_ == nullptr || counter_->shared == 0;
    }

    void operator=(const WeakPtr<T>& other) {
        --counter_->weak;
        if (counter_->shared == 0 && counter_->weak == 0) {
            delete ptr_;
            ptr_ = nullptr;
            delete counter_;
            counter_ = nullptr;
        }
        if (other.ptr_ != nullptr) {
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            ++counter_->weak;
        } else {
            ptr_ = nullptr;
            counter_ = new Counter(0, 1);
            counter_->weak_exp = true;
        }
    }

    void operator=(WeakPtr<T>&& other) {
        --counter_->weak;
        if (counter_->shared == 0 && counter_->weak == 0) {
            delete ptr_;
            ptr_ = nullptr;
            delete counter_;
            counter_ = nullptr;
        }
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        other.counter_ = new Counter(0, 1);
        other.ptr_ = nullptr;
    }

    T operator*() {
        return *ptr_;
    }

    void Reset(T* object) {
        --counter_->weak;
        if (counter_->shared == 0 && counter_->weak == 0) {
            delete ptr_;
            ptr_ = nullptr;
            delete counter_;
            counter_ = nullptr;
        }
        ptr_ = object;
        counter_ = new Counter(0, 1);
    }

    SharedPtr<T> Lock() {
        return SharedPtr<T>(*this);
    }
};

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& rhs) {
    if (!rhs.counter_->weak_exp && rhs.ptr_ != nullptr) {
        ptr_ = rhs.ptr_;
        counter_ = rhs.counter_;
        ++counter_->shared;
    } else {
        ptr_ = nullptr;
        counter_ = new Counter(1, 0);
    }
}
// NOLINTEND