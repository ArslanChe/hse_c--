#include "cppstring.h"

#include <cstring>

String::String() : size_(0), capacity_(0), data_(new char[0]) {
}

String::String(size_t size, char symbol) : size_(size), capacity_(size), data_(new char[size]) {
    std::fill(data_, data_ + size_, symbol);
}
String::String(const char *src) : size_(strlen(src)), capacity_(strlen(src)), data_(new char[size_]) {
    std::copy(src, src + size_, data_);
}

String::String(const char *src, size_t size) : size_(size), capacity_(size), data_(new char[size]) {
    std::copy(src, src + size_, data_);
}
String::String(const String &other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new char[capacity_];
    std::copy(other.data_, other.data_ + size_, data_);
}
String::~String() {
    delete[] data_;
}

const char &String::operator[](size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return data_[idx];
}
char &String::operator[](size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return data_[idx];
}

const char &String::At(size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return data_[idx];
}

char &String::At(size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return data_[idx];
}

const char &String::Front() const {
    if (size_ == 0) {
        throw StringOutOfRange();
    }
    return data_[0];
}
char &String::Front() {
    if (size_ == 0) {
        throw StringOutOfRange();
    }
    return data_[0];
}

const char &String::Back() const {
    if (size_ == 0) {
        throw StringOutOfRange();
    }
    return data_[size_ - 1];
}
char &String::Back() {
    if (size_ == 0) {
        throw StringOutOfRange();
    }
    return data_[size_ - 1];
}

const char *String::Data() const {
    return capacity_ == 0 ? nullptr : data_;
}

char *String::Data() {
    return capacity_ == 0 ? nullptr : data_;
}

bool String::Empty() const {
    return size_ == 0;
}
size_t String::Size() const {
    return size_;
}
size_t String::Length() const {
    return size_;
}
size_t String::Capacity() const {
    return capacity_;
}

void String::Clear() {
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

void String::Swap(String &other) {
    std::swap(other.data_, data_);
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
}

void String::PopBack() {
    if (size_ == 0) {
        throw StringOutOfRange();
    }
    --size_;
}
void String::PushBack(char c) {
    if (size_ >= capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_] = c;
    ++size_;
}

void String::Resize(size_t new_size, char symbol) {
    if (new_size > size_) {
        if (new_size > capacity_) {
            Reserve(new_size);
        }
        std::fill(data_ + size_, data_ + new_size, symbol);
    }
    size_ = new_size;
}
void String::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    char *new_data = new char[new_capacity];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}
void String::ShrinkToFit() {
    if (size_ == capacity_) {
        return;
    }
    char *new_data = new char[size_];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
}

int String::Compare(const String &other) const {
    int cmp_result = std::strncmp(data_, other.data_, std::min(size_, other.size_));

    return cmp_result == 0 ? size_ - other.size_ : cmp_result;  // NOLINT
}

String &String::operator+=(const String &other) {
    if (capacity_ < Size() + other.Size()) {
        Reserve(std::max(Size() + other.Size(), capacity_ * 2));
    }
    std::copy(other.data_, other.data_ + other.size_, data_ + size_);
    size_ = size_ + other.size_;
    return *this;
}
char *String::CStr() {
    return data_;
}

String operator+(const String &first, const String &second) {
    String result(first);
    result += second;
    return result;
}

bool operator==(const String &first, const String &second) {
    return first.Compare(second) == 0;
}

bool operator!=(const String &first, const String &second) {
    return !(first == second);
}
bool operator>(const String &first, const String &second) {
    return first.Compare(second) > 0;
}
bool operator<(const String &first, const String &second) {
    return first.Compare(second) < 0;
}
bool operator>=(const String &first, const String &second) {
    return first.Compare(second) >= 0;
}
bool operator<=(const String &first, const String &second) {
    return first.Compare(second) <= 0;
}

std::ostream &operator<<(std::ostream &stream, const String &string) {
    for (size_t i = 0; i < string.Size(); i++) {
        stream << string[i];
    }
    return stream;
}
const char *String::CStr() const {
    return data_;
}

String &String::operator=(const String &other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new char[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    return *this;
}
void SafeCpy(char *dest, const char *src, size_t len) {
    for (size_t i = 0; i < len; i++) {
        *(dest + i) = *(src + i);
    }
}