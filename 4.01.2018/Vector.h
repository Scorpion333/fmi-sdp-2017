#pragma once
const int MIN_CAPACITY = 2;

class Vector {
    int* arr;
    int size; 
    int capacity;

public:
    class Iterator {
        int* ptr;
    public:
        Iterator(int* _ptr) {
            ptr = _ptr;
        }
        bool operator != (const Iterator& other) {
            return ptr != other.ptr;
        }
        int operator*() const {
            return *ptr;
        }
        void operator++() {                 // Prefix operator
            ++ptr;
        }

        // Optional non-const (*) for maniacs
        int& operator*() {
            return *ptr;
        }
    };
    
    Iterator begin() const {
        return Iterator(arr);
    }
    Iterator end() const {
        return Iterator(arr + size);
    }

    Vector() {
        size = 0;
        capacity = MIN_CAPACITY;
        arr = new int[capacity];
    }
    Vector(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        arr = new int[capacity];
        for (int i = 0; i < other.size; i++) {
            arr[i] = other.arr[i];
        }
    }
    Vector& operator= (const Vector& other) {
        if (this != &other) {
            size = other.size;
            capacity = other.capacity;
            arr = new int[capacity];
            for (int i = 0; i < other.size; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    ~Vector() {
        delete[] arr;
    }

    void push_back(int x) {
        if (size == capacity) {
            resize();
        }
        arr[size] = x;
        size++;
    }

private:
    void resize() {
        capacity *= 2;
        int* temp = new int[capacity];
        for (int i = 0; i < size; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
};