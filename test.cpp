#include <iostream>

#include "Vector.hpp"

int main() {
    Vector<int> vec;
    vec.pushBack(1);
    vec.pushBack(2);
    vec.pushBack(3);

    std::cout << "Vector elements: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
