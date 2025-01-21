#include "Vector.hpp"

#include <algorithm>

namespace {
const size_t kDefaultSize{8};
}

// constructors

template<typename T>
Vector<T>::Vector() : data_(nullptr), capacity_(kDefaultSize), size_(0) {
}

template<typename T>
Vector<T>::Vector(const size_t capacity) : size_(0), capacity_(capacity), data_(new T[capacity]) {
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> list) : capacity_(list.size()), size_(list.size()), data_(new T[list.size()]) {
    std::copy(list.begin(), list.begin() + list.size(), data_);
}

template<typename T>
Vector<T>::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), data_(nullptr) {
    if (other.data_ == nullptr) {
        throw std::invalid_argument("error when calling copy constructor");
    }

    data_ = new T[other.size_];
    std::copy(other.data_, other.data_ + other.size_, data_);
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
    other.data_ = nullptr;
    other.capacity_ = 0;
    other.size_ = 0;
}

// destructor

template<typename T>
Vector<T>::~Vector() {
    delete[] data_;
    data_ = nullptr;
}

// access to the elements

template<typename T>
T& Vector<T>::operator[](size_t index) {
    return data_[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data_[index];
}

template<typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("invalid index");
    }

    return data_[index];
}

template<typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("invalid index");
    }

    return data_[index];
}

template<typename T>
T& Vector<T>::front() {
    if (empty()) {
        throw std::out_of_range("vector is empty");
    }

    return data_[0];
}

template<typename T>
T& Vector<T>::back() {
    if (empty()) {
        throw std::out_of_range("vector is empty");
    }

    return data_[size_ - 1];
}

// operators

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (other.data_ == nullptr) {
        throw std::invalid_argument("invalid vector");
    }

    if (data_ != nullptr) {
        delete[] data_;
    }

    data_ = new T[other.capacity_];
    std::copy(other.data_, other.data_ + other.size_, data_);
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data;
        capacity_ = other.capacity_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }
    return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector& other) const {
    if (data_ == nullptr || other.data_ == nullptr || size_ != other.size_) {
        return false;
    }

    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }

    return true;
}

// working with vector size

template<typename T>
bool Vector<T>::empty() const {
    return size_ == 0;
}

template<typename T>
size_t Vector<T>::size() const {
    return size_;
}

template<typename T>
size_t Vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
void Vector<T>::reserve(size_t newCapacity) {
    if (newCapacity > capacity_) {
        T* newData = new T[newCapacity];
        std::copy(data_, data_ + size_, newData);

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }
}

template<typename T>
void Vector<T>::resize() {
    if (data_ == nullptr) {
        throw std::invalid_argument("invalid argument to resize");
    }

    capacity_ *= 2;

    T* newData = new T[capacity_];
    std::copy(data_, data_ + size_, newData);

    delete[] data_;
    data_ = newData;
}

// modificators

template<typename T>
void Vector<T>::clear() {
    if (data_ == nullptr) {
        throw std::invalid_argument("error when calling clearing");
    }

    size_ = 0;
}

template<typename T>
void Vector<T>::pushBack(const T& element) {
    if (data_ == nullptr) {
        throw std::invalid_argument("invalid data to pushback");
    }

    if (size_ >= capacity_) {
        resize();
    }

    data_[size_++] = element;
}

template<typename T>
void Vector<T>::popBack() {
    if (data_ == nullptr) {
        throw std::invalid_argument("invalid data to popback");
    }

    if (size_ > 0) {
        --size_;
    }
}

template<typename T>
void Vector<T>::insert(size_t index, const T& element) {
    if (index > size_) {
        throw std::out_of_range("invalid index");
    }

    if (size_ >= capacity_) {
        resize();
    }

    for (size_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }

    data_[index] = element;
    ++size_;
}

template<typename T>
void Vector<T>::erase(size_t index) {
    if (index > size_) {
        throw std::out_of_range("invalid index");
    }

    for (size_t i = index; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
}

template<typename T>
void Vector<T>::swap(Vector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

// iterators

template<typename T>
T* Vector<T>::begin() {
    return data_;
}

template<typename T>
T* Vector<T>::end() {
    return data_ + size_;
}

template<typename T>
T* Vector<T>::rbegin() {
    return data_ + size_ - 1;
}

template<typename T>
T* Vector<T>::rend() {
    return data_ - 1;
}
