#pragma once
#include<fstream>
using std::istream;
using std::ostream;

template<typename T>
T* copy_of(T* pointer) {
    return pointer ? new T(*pointer) : nullptr;
}

template<typename T>
class Maybe {
    T* ptr;

public:
    Maybe()                      : ptr(nullptr) {}
    Maybe(const T& t)            : ptr(new T(t)) {}
    Maybe(const Maybe<T>& other) : ptr(copy_of(other.ptr)) {}

    Maybe& operator = (const T& t) {
        delete ptr;
        ptr = new T(t);
        return *this;
    }
    Maybe& operator = (const Maybe<T>& other) {
        if (this != &other) {
            delete ptr;
            ptr = copy_of(other.ptr);
        }
        return *this;
    }
    ~Maybe() {
        delete ptr;
    }
    
    bool operator == (const T& t) const {
        return ptr != nullptr && *ptr == t;
    }
    bool operator == (const Maybe<T>& other) const {
        return (ptr == nullptr && other.ptr == nullptr)
            || (ptr != nullptr && other.ptr != nullptr && *ptr == *other.ptr);
    }
    
    bool operator != (const T& t) const {
        return ptr == nullptr || *ptr != t;
    }
    bool operator != (const Maybe<T>& other) const {
        return !(*this == other);
    }  

    operator T() const {
        return *ptr;
    }
    operator T&() {
        return *ptr;
    }
    operator bool() const {
        return ptr != nullptr;
    }

    // For readability - sometimes the explicit cast looks ugly, for instance, when T is a class
    T value() const {
        return *ptr;
    }
    T& to_ref() {
        return *ptr;
    }
};

template<typename T>
Maybe<T> Undefined() {
    return Maybe<T>();
}

template<typename T>
bool operator == (const T& t, const Maybe<T>& m) {
    return m == t;
}
template<typename T>
bool operator != (const T& t, const Maybe<T>& m) {
    return m != t;
}

template<typename T>
ostream& operator << (ostream& out, const Maybe<T>& m) {
    return out << m.value();
}
template<typename T>
istream& operator >> (istream& in, Maybe<T>& m) {
    T temp;
    in >> temp;
    m = temp;
    return in;
}