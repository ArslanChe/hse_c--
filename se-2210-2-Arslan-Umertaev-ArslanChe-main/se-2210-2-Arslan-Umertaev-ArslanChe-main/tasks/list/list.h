#pragma once
// NOLINTBEGIN
#include <iostream>

template <class T>
class Node {
public:
    Node(const T& value) : value_(value) {
    }
    Node(T&& value) : value_(std::move(value)) {
    }
    ~Node() = default;
    T& GetValue() {
        return value_;
    }
    Node<T>* GetNext() {
        return next_ ? next_ : this;
    }
    void SetNext(Node<T>* value) {
        next_ = value;
    }
    Node<T>* GetPrevious() {
        return previous_ ? previous_ : this;
    }
    void SetPrevious(Node<T>* value) {
        previous_ = value;
    }

private:
    Node<T>* next_;
    Node<T>* previous_;
    T value_;
};

template <typename T>
class List {
public:
    class Iterator {
    public:
        Iterator(Node<T>* current, size_t pos) : current_(current), pos_(pos) {
        }

        Iterator operator++() {
            current_ = current_->GetNext();
            pos_++;
            return Iterator(current_, pos_);
        }

        Iterator operator++(int) {
            Iterator res(current_, pos_);
            current_ = current_->GetNext();
            pos_++;
            return res;
        }

        Iterator operator--() {
            current_ = current_->GetPrevious();
            pos_--;
            return Iterator(current_, pos_);
        }
        Iterator operator--(int) {
            Iterator res(current_, pos_);
            current_ = current_->GetPrevious();
            pos_--;
            return res;
        }
        T& operator*() const {
            return current_->GetValue();
        }
        T* operator->() const {
            return &(current_->GetValue());
        }

        bool operator==(const Iterator& rhs) const {
            return rhs.pos_ == pos_;
        }
        bool operator!=(const Iterator& rhs) const {
            return rhs.pos_ != pos_;
        }

    private:
        Node<T>* current_;
        size_t pos_;
    };

    List() : front_(nullptr), back_(front_), size_(0) {
    }
    List(const List& dop) : List() {
        Node<T>* node = dop.front_;
        while (size_ < dop.size_) {
            PushBack(node->GetValue());
            node = node->GetNext();
        }
    }
    List(List&& dop) : front_(dop.front_), back_(dop.back_), size_(dop.size_) {
        dop.front_ = nullptr;
        dop.back_ = nullptr;
        dop.size_ = 0;
        dop.Clear();
    }
    void Clear() {
        while (!IsEmpty()) {
            PopBack();
        }
        delete front_;
    }
    ~List() {
        Clear();
    }
    List& operator=(const List& dop) {
        Clear();
        Node<T>* node = dop.front_;
        while (size_ < dop.size_) {
            PushBack(node->GetValue());
            node = node->GetNext();
        }
        return *this;
    }

    List& operator=(List&& dop) {
        Clear();
        front_ = dop.front_;
        back_ = dop.back_;
        size_ = dop.size_;
        dop.front_ = nullptr;
        dop.back_ = nullptr;
        dop.size_ = 0;
        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }
    size_t Size() const {
        return size_;
    }

    void PushBack(T&& tmp) {
        if (size_ == 0) {
            Add(std::forward<T>(tmp));
        } else {
            Node<T>* node = new Node<T>(std::forward<T>(tmp));
            node->SetPrevious(back_);
            node->SetNext(front_);
            back_->SetNext(node);
            front_->SetPrevious(node);
            back_ = node;
            size_++;
        }
    }

    void PushBack(const T& tmp) {
        if (size_ == 0) {
            Add(tmp);
        } else {
            Node<T>* node = new Node<T>(tmp);
            node->SetPrevious(back_);
            node->SetNext(front_);
            back_->SetNext(node);
            front_->SetPrevious(node);
            back_ = node;
            size_++;
        }
    }
    void PushFront(T&& tmp) {
        if (size_ == 0) {
            Add(std::forward<T>(tmp));
        } else {
            Node<T>* node = new Node<T>(std::forward<T>(tmp));
            node->SetNext(front_);
            node->SetPrevious(back_);
            front_->SetPrevious(node);
            back_->SetNext(node);
            front_ = node;
            size_++;
        }
    }

    T& Front() {
        return front_->GetValue();
    }
    const T& Front() const {
        return front_->GetValue();
    }
    T& Back() {
        return back_->GetValue();
    }
    const T& Back() const {
        return back_->GetValue();
    }

    void PopBack() {
        if (size_ > 1) {
            Node<T>* new_back = back_->GetPrevious();
            front_->SetPrevious(new_back);
            new_back->SetNext(front_);
            delete back_;
            back_ = new_back;
            size_--;
        } else {
            front_ = nullptr;
            delete back_;
            size_--;
        }
    }
    void PopFront() {
        if (size_ > 1) {
            Node<T>* new_front = front_->GetNext();
            new_front->SetPrevious(back_);
            back_->SetNext(new_front);
            delete front_;
            front_ = new_front;
            size_--;
        } else {
            back_ = nullptr;
            delete front_;
            size_--;
        }
    }

    Iterator Begin() {
        return Iterator(front_, 0);
    }
    Iterator End() {
        return Iterator(back_, size_);
    }

    Iterator begin() {
        return Begin();
    }
    Iterator end() {
        return End();
    }
    void Add(T&& value) {
        front_ = new Node<T>(std::forward<T>(value));
        front_->SetNext(front_);
        front_->SetPrevious(front_);
        back_ = front_;
        size_++;
    }

    void Add(const T& value) {
        front_ = new Node<T>(value);
        front_->SetNext(front_);
        front_->SetPrevious(front_);
        back_ = front_;
        size_++;
    }

private:
    Node<T>* front_;
    Node<T>* back_;
    size_t size_ = 0;
};

template <typename T>
typename List<T>::Iterator begin(const List<T>& list) {
    return list.Begin();
}
template <typename T>
typename List<T>::Iterator end(const List<T>& list) {
    return list.End();
}
// NOLINTEND