#pragma once
#include<iostream>
#include<vector>
using std::cout;
using std::vector;

class List {
    struct Node {
        int data;
        Node* next;
        Node(int _data) {
            data = _data;
            next = nullptr;
        }
    };

    Node* first;
    Node* last;
public:
    class Iterator {
        Node* crr;
    public:
        Iterator(Node* node) {
            crr = node;
        }
        bool operator != (const Iterator& other) const {
            return crr != other.crr;
        }
        int operator*() const {
            return crr->data;
        }
        void operator++ () {
            crr = crr->next;
        }

        // Optional non-const (*) for maniacs
        int& operator* () {
            return crr->data;
        }
    };

    Iterator begin() const {
        return Iterator(first);
    }
    Iterator end() const {
        return Iterator(nullptr);
    }

    List() {
        first = last = nullptr;
    }
    ~List() {
        // ...
    }

    void push_back(int x) {
        if (last == nullptr) {
            first = last = new Node(x);
            return;
        }
        last->next = new Node(x);
        last = last->next;
    }

    bool has_duplicates() {
        Node* iter = first;
        while (iter != nullptr) {
            if (find(iter->data, iter->next)) {
                return true;
            }
            iter = iter->next;
        }
        return false;
    }

    // Checks if 'x' is in the sublist which starting from 'ptr'.
    bool find(int x, Node* ptr) {
        if (ptr == nullptr) {
            return false;
        }
        if (ptr->data == x) {
            return true;
        }
        return find(x, ptr->next);
    }
};