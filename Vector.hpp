#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class Vector {
 private:
    T* data_;
    size_t capacity_;
    size_t size_;

    void resize();

 public:
    // constructors
    Vector();
    explicit Vector(const size_t capacity);
    Vector(std::initializer_list<T> list);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;

    // destructor
    ~Vector();

    // access to elements
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& front();
    T& back();

    // operators
    Vector<T>& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    bool operator==(const Vector& other) const;

    // working with vector size
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] size_t capacity() const;
    void reserve(size_t newCapacity);

    // modificators
    void clear();
    void pushBack(const T& element);
    void popBack();
    void insert(size_t index, const T& element);
    void erase(size_t index);
    void swap(Vector& other) noexcept;

    // iterators
    T* begin();
    T* end();
    T* rbegin();
    T* rend();
};
