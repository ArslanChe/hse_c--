
#pragma once
#include <iostream>
#include <iterator>
// NOLINTBEGIN
template <class T>
class Vector {
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T, std::size_t, T*, T&> {
    public:
        Iterator() : ptr_(nullptr) {
        }
        explicit Iterator(T* ptr) : ptr_(ptr) {
        }
        Iterator(const Iterator& other) : ptr_(other.ptr_) {
        }
        T& operator*() const {
            return *ptr_;
        }
        T* operator->() const {
            return ptr_;
        }
        ~Iterator() {
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }
        Iterator& operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator++(int) {
            ++(*this);
            Iterator tmp = *this - 1;
            return tmp;
        }
        Iterator operator--(int) {
            --(*this);
            Iterator tmp = *this + 1;
            return tmp;
        }

        Iterator& operator+=(int n) {
            ptr_ += n;
            return *this;
        }
        Iterator& operator-=(int n) {
            ptr_ -= n;
            return *this;
        }

        std::size_t operator-(const Iterator& other) const {
            return ptr_ - other.ptr_;
        }

        Iterator operator+(int n) const {
            Iterator tmp = *this;
            tmp += n;
            return tmp;
        }
        Iterator operator-(int n) const {
            Iterator tmp = *this;
            tmp -= n;
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }

    private:
        T* ptr_;
    };

    Vector() : Vector(0) {
    }

    explicit Vector(std::size_t size) : data_(new T[size]), size_(size), capacity_(size) {
        std::fill(data_, data_ + size_, 0);
    }

    Vector(std::initializer_list<T> init_list)
        : data_(new T[init_list.size()]), size_(init_list.size()), capacity_(init_list.size()) {
        std::copy(init_list.begin(), init_list.end(), data_);
    }

    Vector(const Vector& other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.size_) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    Vector(Vector&& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
        delete[] other.data_;
        other.data_ = nullptr;
    }

    Vector& operator=(const Vector& other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
        delete[] other.data_;
        other.data_ = nullptr;
        return *this;
    }

    void Swap(Vector& other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }

    T operator[](std::size_t index) const {
        return data_[index];
    }

    T& operator[](std::size_t index) {
        return data_[index];
    }

    std::size_t Size() const {
        return size_;
    }

    std::size_t Capacity() const {
        return capacity_;
    }

    void PushBack(int value) {
        if (size_ == capacity_) {
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            T* new_data = new int[capacity_];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
        }

        data_[size_++] = value;
    }

    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = new int[new_capacity];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }
    ~Vector() {
        delete[] data_;
    }

    Iterator Begin() {
        return Iterator(data_);
    }

    Iterator End() {
        return Iterator(data_) + size_;
    }

    Iterator begin() {  // NOLINT
        return Begin();
    }
    Iterator end() {  // NOLINT
        return End();
    }

private:
    T* data_;
    size_t size_;
    size_t capacity_;
};
// NOLINTEND