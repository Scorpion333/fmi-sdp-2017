#pragma once
#include<vector>;
using std::vector;

class Matrix {
    vector<vector<int>> matr;
public:
    Matrix(const vector<vector<int>>& _matr) {
        matr = _matr;
    }

    class Iterator {
        int row, col;
        const Matrix* matrix;
    public:
        Iterator (const Matrix* _matrix, int _row, int _col) {
            matrix = _matrix;
            row = _row;
            col = _col;
        }
        bool operator != (const Iterator& other) {
            return matrix != other.matrix || row != other.row || col != other.col;
        }
        int operator* () {
            return (*matrix)[row][col];
        }
        void operator++() {
            col++;
            if (col == (*matrix)[row].size()) {
                col = 0;
                do {
                    row++;
                } while (row < matrix->size() && (*matrix)[row].empty());
            }
        }
    };
    Iterator begin() {
        int the_row = 0;
        while (the_row < matr.size() && matr[the_row].empty()) {
            the_row++;
        }
        return Iterator(this, the_row, 0);
    }
    Iterator end() {
        return Iterator(this, matr.size(), 0);
    }

    // Returns a row
    vector<int> operator [](int i) const {
        return matr[i];
    }

    // Returns the number of rows
    int size() const {
        return matr.size();
    }
};