#pragma once

#include <cstddef>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t size;

    void Resize();

public:
    Vector();
    explicit Vector(const size_t cap);
    Vector(std::initializer_list<T> list);
    Vector(const Vector& other);

    ~Vector();

    bool Empty() const;
    void Clear();

    size_t Size();

    void PushBack(const T& element);
    void PopBack();
};
