#pragma once

template <class T>
class UniquePtr {
public:
    UniquePtr() : ptr_(nullptr) {
    }
    explicit UniquePtr(T* ptr) : ptr_(ptr) {
    }

    UniquePtr(UniquePtr&& other) : ptr_(other.Release()) {
    }

    ~UniquePtr() {
        delete ptr_;
    }
    UniquePtr& operator=(UniquePtr&& other) {
        Reset(other.Release());
        return *this;
    }

    T& operator*() const {
        return *ptr_;
    }
    T* operator->() const {
        return ptr_;
    }
    T* Get() const noexcept {
        return ptr_;
    }

    void Reset(T* ptr = nullptr) {
        delete ptr_;
        ptr_ = ptr;
    }
    T* Release() {
        T* released_ptr = ptr_;
        ptr_ = nullptr;
        return released_ptr;
    }

private:
    T* ptr_;
};
