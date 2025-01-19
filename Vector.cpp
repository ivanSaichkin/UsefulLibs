#include "Vector.hpp"

#include <algorithm>

namespace{
size_t kDefaultSize{8};
}

template <typename T>
Vector<T>::Vector() : data(nullptr), capacity(kDefaultSize), size(0){
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list) : capacity(list.size()), size(list.size()), data(new T [list.size()]){
    std::copy(list.begin(), list.begin() + list.size(), data);
}

template <typename T>
Vector<T>::Vector(const size_t cap) : size(0), capacity(cap), data(new T [cap]){
}

template <typename T>
Vector<T>::Vector(const Vector& other) : size(other.size), capacity(other.capacity), data(nullptr){
    if(other.data == nullptr){
        throw std::invalid_argument("error when calling copy constructor");
    }

    data = new T [other.size];
    std::copy(other.data, other.data + other.size, data);
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
    data = nullptr;
}

template <typename T>
bool Vector<T>::Empty() const{
    return size == 0;
}

template <typename T>
void Vector<T>::Clear(){
    if (data == nullptr){
        throw std::invalid_argument("error when calling clearing");
    }

    size = 0;
}

template <typename T>
size_t Vector<T>::Size(){
    return size;
}

template <typename T>
void Vector<T>::Resize(){
    if(data == nullptr){
        throw std::invalid_argument("invalid argument to resize");
    }

    capacity *= 2;

    T* newData = new T [capacity];
    std::copy (data, data + size, newData);

    delete[] data;
    data = newData;
}

template <typename T>
void Vector<T>::PushBack(const T& element){
    if (data == nullptr){
        throw std::invalid_argument("invalid data to pushback");
    }

    if(size >= capacity){
        Resize();
    }

    data[size++] = element;
}

template <typename T>
void Vector<T>::PopBack(){
    if(data == nullptr){
        throw std::invalid_argument("invalid data to popback");
    }

    if(size > 0){
        --size;
    }
}

int main(){
    Vector<int> vector = {1, 2, 3, 4, 5};
    vector.PopBack();
    vector.Size();
    vector.PushBack(8);


    return 0;
}
