#include "String.hpp"

#include <cstring>

namespace {
const size_t kMaxCinSymbols{80};
}

size_t String::numStrings_ = 0;

// Constructors

String::String() : data_(new char[1]{}), length_(0) {
    data_[0] = '\0';
    ++numStrings_;
}

String::String(const char* str) : length_(std::strlen(str)), data_(new char[std::strlen(str) + 1]{}) {
    std::strncpy(data_, str, std::strlen(str));
    ++numStrings_;
}

String::String(const String& str) : length_(std::strlen(str.data_)), data_(new char[std::strlen(str.data_) + 1]{}) {
    std::strncpy(this->data_, str.data_, std::strlen(str.data_));
    ++numStrings_;
}

String::String(const char* str, size_t n) : length_(std::min(n, std::strlen(str))) {
    data_ = new char[length_ + 1];
    std::strncpy(data_, str, n);
    ++numStrings_;
}

String::String(String&& str) noexcept : length_(str.length_), data_(str.data_) {
    str.data_ = nullptr;
    str.length_ = 0;
}

// Destructor

String::~String() {
    delete[] data_;
    data_ = nullptr;
    length_ = 0;
    --numStrings_;
}

// Assignment operators

String& String::operator=(const String& str) {
    if (this == &str) {
        return *this;
    }

    if (data_ != nullptr) {
        delete[] data_;
    }

    if (str.length_ != 0) {
        data_ = new char[str.length_ + 1];
        std::strncpy(data_, str.data_, std::strlen(str.data_));
        length_ = str.length_;
    } else {
        data_ = nullptr;
        length_ = 0;
    }

    return *this;
}

String& String::operator=(const char* str) {
    delete[] data_;

    length_ = std::strlen(str);
    data_ = new char[length_ + 1];
    std::strncpy(data_, str, std::strlen(str));

    return *this;
}

String& String::operator=(char _c) {
    delete[] data_;

    length_ = 1;
    data_ = new char[length_ + 1];
    data_[0] = _c;
    data_[1] = '\0';

    return *this;
}

String& String::operator=(String&& str) noexcept {
    if (this != &str) {
        delete[] data_;

        data_ = str.data_;
        length_ = str.length_;

        str.data_ = nullptr;
        str.length_ = 0;
    }

    return *this;
}

// Operators

char& String::operator[](size_t index) {
    return data_[index];
}

const char& String::operator[](size_t index) const {
    return data_[index];
}

bool operator<(const String& str_1, const String& str_2) {
    return std::strcmp(str_1.data_, str_2.data_) < 0;
}

bool operator>(const String& str_1, const String& str_2) {
    return std::strcmp(str_1.data_, str_2.data_) > 0;
}

bool operator==(const String& str_1, const String& str_2) {
    return std::strcmp(str_1.data_, str_2.data_) == 0;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.data_;
    return os;
}

std::istream& operator>>(std::istream& is, String& str) {
    char buffer[kMaxCinSymbols]{};
    is >> buffer;
    str = String(buffer);
    return is;
}

String operator+(const String& str_1, const String& str_2) {
    String temp;
    delete[] temp.data_;
    temp.length_ = str_1.length_ + str_2.length_;
    temp.data_ = new char[temp.length_];
    char* merge = std::strncat(str_1.data_, str_2.data_, std::strlen(str_2.data_));
    std::strncpy(temp.data_, merge, std::strlen(merge));

    return temp;
}

String& String::operator+=(const String& other) {
    length_ = std::strlen(data_) + std::strlen(other.data_);

    char* newStr = new char[length_ + 1];
    std::strncpy(newStr, data_, std::strlen(data_));
    std::strncat(newStr, other.data_, std::strlen(other.data_));

    delete[] data_;
    data_ = newStr;

    return *this;
}

String& String::operator+=(const char* str) {
    length_ = std::strlen(data_) + std::strlen(str);

    char* newStr = new char[length_ + 1];
    std::strncpy(newStr, data_, std::strlen(data_));
    std::strncat(newStr, str, std::strlen(str));

    delete[] data_;
    data_ = newStr;

    return *this;
}

String& String::operator+=(char c) {
    ++length_;

    char* newStr = new char[length_ + 1];
    std::strncpy(newStr, data_, std::strlen(data_));
    newStr[length_ - 1] = c;

    delete[] data_;
    data_ = newStr;

    return *this;
}

// Iterators

char* String::begin() {
    if (data_ == nullptr) {
        throw std::invalid_argument("str is empty");
    }

    return data_;
}

char* String::end() {
    if (data_ == nullptr) {
        throw std::invalid_argument("str is empty");
    }

    return data_ + length_;
}

// Static methods
size_t String::numStrigs() {
    return numStrings_;
}

void String::resetNumStrings() {
    numStrings_ = 0;
}
