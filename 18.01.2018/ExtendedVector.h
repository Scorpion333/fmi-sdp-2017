#pragma once
#include<vector>
using std::vector;

template<typename T>
int index_of(const T& x, const vector<T>& vec) {
    for (unsigned i = 0; i < vec.size(); i++) {
        if (vec[i] == x)
            return i;
    }
    return -1;
}

template<typename T>
bool has_element(const T& x, const vector<T>& vec) {
    return index_of(x, vec) != -1;
}

// Removes X, if it is there. Nothing happens if there's no X in the vector
template<typename T>
void remove_from_vector(const T& x, vector<T>& vec) {
    int ix = index_of(x, vec);
    if (ix == -1)
        return;
    vec.erase(vec.begin() + ix);
}
