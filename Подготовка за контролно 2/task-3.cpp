#include<iostream>
using std::cout;

const int N = 6;                // TODO: explain why this is OK.

bool a[N][N] = {                
    1, 1, 0, 0, 1, 1,           // Hint: {
    0, 1, 0, 1, 0, 1,           //     "If", "you", "write", "multi-line",
    1, 1, 0, 0, 1, 1,           //     "things", "like", "matrixes", "this",
    1, 1, 0, 0, 1, 0,           //     "way", "the", "editor", "will", "have",  
    1, 0, 1, 0, 1, 1,           //     "no", "problems", "with", "indentation",
    0, 0, 0, 0, 0, 0,           // }
};                              

bool has_ladder(int start, int k) {
    if (start < 0 || start >= N || k < 0 || k >= N) {     // Incorrect arguments
        return false;
    } 
    if (k == 0) {                                         // Trivial case
        return true;
    }
    for (int i = start + 1; i < N; i++) {                 // For each vertex, larger than start, if there
        if (a[start][i] && has_ladder(i, k - 1))          // is edge start->i and (k-1)-sized ladder from i,
            return true;                                  // this means that vsichko e tochno.
    }
    return false;
}


// Test time!
void expect(const char* output) {
    cout << "\nExpected:\n" << output << "\n\n";
}

int main() {
    for (int i = 0; i < N; i++)
        cout << has_ladder(0, i) << ' ';
    expect("1 1 1 1 1 0");                // The longest ladder is:  { 0, 1, 3, 4, 5 }  (k == 4)

    a[3][4] = a[4][5] = 0;              

    for (int i = 0; i < N; i++)
        cout << has_ladder(0, i) << ' ';
    expect("1 1 1 0 0 0");                // Now the new longest is:  { 0, 1, 3 }  (k = 2)

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = 0;
   
    for (int i = 0; i < N; i++)
        cout << has_ladder(0, i) << ' ';
    expect("1 0 0 0 0 0");                // The '1' is for the trivial ladder:  { 0 }  (k = 0)

    return 0;
}