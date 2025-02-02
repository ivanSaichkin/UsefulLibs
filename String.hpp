#pragma once

#include <iostream>
#include <stdexcept>

class String {
 private:
    char* data_;
    size_t length_;
    static size_t numStrings_;

 public:
    // Constructors
    String();
    String(const char* _s);
    String(const String& str);
    String(const char* _s, size_t n);
    String(String&& str) noexcept;

    // Destructor
    ~String();

    // Assignment operators
    String& operator=(const String& other);
    String& operator=(const char* _s);
    String& operator=(char _c);
    String& operator=(String&& str) noexcept;

    // Operators
    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    friend bool operator<(const String& str_1, const String& str_2);
    friend bool operator>(const String& str_1, const String& str_2);
    friend bool operator==(const String& str_1, const String& str_2);

    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);

    friend String operator+(const String& str_1, const String& str_2);

    String& operator+=(const String& other);
    String& operator+=(const char* str);
    String& operator+=(char c);

    // Iterators
    char* begin();
    char* end();

    // Static methods
    static size_t numStrigs();
    static void resetNumStrings();
};
