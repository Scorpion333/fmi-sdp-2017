#pragma once
#include<iostream>
#include<cmath>
#include<vector>
using std::cout;
using std::vector;

unsigned ones_in(const vector<bool>& vec) {
    unsigned ones = 0;
    for (unsigned i = 0; i < vec.size(); i++) {
        if (vec[i])
            ones++;
    }
    return ones;
}

class KnightConfig {
    vector<bool> vec;
    size_t size;
    unsigned k;
public:
    KnightConfig(const vector<bool>& _vec) : vec(_vec) {
        size = sqrt(vec.size());
        k = ones_in(vec);
    }

    KnightConfig(size_t _size, unsigned k)
        : size(_size)
    {
        for (int i = 0; i < size*size - k; i++) {
            vec[i] = 0;
        }
        for (int i = size*size - k; i < size*size; i++) {
            vec[i] = 1;
        }
    }

    bool get_position(unsigned row, unsigned col) {
        return vec[row*size + col];
    }
    
    // TODO
    void to_next_table() {
    }
    
    // Slow but working
    bool is_valid_config(unsigned k) {
        if (k == 1) {
            return true;
        }
        unsigned knights_i[8];
        unsigned found_knights = 0;

        unsigned i = 0;
        while (found_knights < k) {
            if (vec[i]) {
                knights_i[found_knights] = i;
                found_knights++;
            }
            i++;
        }
        for (i = 1; i < found_knights; i++) {
            if (beats(knights_i[0], knights_i[i])) {
                return false;
            }
        }
        vec[knights_i[0]] = 0;
        bool is_valid = is_valid_config(k - 1);
        vec[knights_i[0]] = 1;
        return is_valid;
    }

    bool beats(unsigned a, unsigned b) {
        unsigned row_a = a / size;
        unsigned col_a = a % size;
        unsigned row_b = b / size;
        unsigned col_b = b % size;

        return (row_a - row_b)*(row_a - row_b)
            + (col_a - col_b)*(col_a - col_b) == 5;
    }

    void print_current() {
        for (unsigned i = 0; i < size; i++) {
            for (unsigned j = 0; j < size; j++) {
                if (vec[i* size + j])
                    cout << "H ";
                else
                    cout << "_ ";
            }
            cout << '\n';
        }
    }
};