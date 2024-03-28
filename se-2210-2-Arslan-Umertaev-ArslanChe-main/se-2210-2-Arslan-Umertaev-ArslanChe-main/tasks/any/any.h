#pragma once
#include <typeinfo>
#include <utility>
class BaseHolder {
public:
    virtual const std::type_info& Type() const = 0;
    virtual BaseHolder* Clone() const {
        return nullptr;
    }
    virtual ~BaseHolder(){};
};

template <class T>
struct Holder : BaseHolder {
    T tmp;
    explicit Holder(const T& value) : tmp(std::move(value)) {
    }

    const std::type_info& Type() const override {
        return typeid(tmp);
    }

    BaseHolder* Clone() const override {
        return new Holder(tmp);
    }
};

class Any {

public:
    Any() : holder_(nullptr) {
    }

    template <class T>
    explicit Any(const T& value) : holder_(new Holder(value)) {
    }

    template <class T>
    Any& operator=(const T& value) {
        delete holder_;
        holder_ = new Holder(value);
        return *this;
    }

    Any(const Any& other) : holder_(other.holder_ ? other.holder_->Clone() : nullptr) {
    }

    Any& operator=(Any other) {
        this->Swap(other);
        return *this;
    }

    ~Any() {
        delete holder_;
    }

    bool Empty() const {
        return holder_ == nullptr;
    }
    void Clear() {
        delete holder_;
        holder_ = nullptr;
    }

    void Swap(Any& rhs) {
        std::swap(holder_, rhs.holder_);
    }

    template <class T>
    const T& GetValue() const {
        if (!holder_ || holder_->Type() == typeid(T)) {
            return dynamic_cast<Holder<T>*>(holder_)->tmp;
        }
        throw std::bad_cast();
    }

private:
    BaseHolder* holder_;
};