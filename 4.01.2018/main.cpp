#include<iostream>
#include"util.h"        // For expect()
#include"List.h"
#include"Vector.h"
#include"Matrix.h"
#include"BinTree.h"
using namespace std;

void test_list() {
    cout << "Testing List.\n";
    List lis;
    for (int i = 1; i <= 17; i++) {
        lis.push_back(2 * i);
    }
    for (List::Iterator it = lis.begin(); it != lis.end(); ++it) {
        cout << *it << ' ';
    }
    expect("2 4 6 ... 34");
}

void test_has_duplicates() {
    cout << "Testing has_duplicates.\n";

    List a, b;
    a.push_back(4);
    a.push_back(4);
    a.push_back(2);

    b.push_back(11);
    b.push_back(12);
    b.push_back(13);

    cout << a.has_duplicates() << ' ' << b.has_duplicates();
    expect("1 0");
}

void test_vector() {
    cout << "Testing Vector.\n";
    Vector vec;
    for (int i = 1; i <= 17; i++) {
        vec.push_back(2 * i);
    }
    for (Vector::Iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << ' ';
    }
    expect("2 4 6 ... 34");
}

void test_matrix() {
    cout << "Testing Matrix.\n";
    Matrix m({                  // Yeah, this is valid C++11 syntax
        { 1, 2, 3 },
        { 4, 5, 6, 7 },
        {},
        { 8, 9 }
    });

    for (Matrix::Iterator it = m.begin(); it != m.end(); ++it) {
        cout << *it << ' ';
    }
    expect("1 2 ... 9");
}

void test_bintree() {
    cout << "Testing BinTree.\n";
    BinTree bt;
    bt.add(5, "");
    bt.add(1, "L");
    bt.add(4, "LL");
    bt.add(100, "R");
    bt.add(200, "RL");
    bt.add(300, "RR");

    bt.print_stacky_way();
    expect("5 1 4 100 200 300");

    cout << bt.count_stacky_way();
    expect("6");
}

int main() {
    test_list();
    test_has_duplicates();
    test_vector();
    test_matrix();
    test_bintree();
    return 0;
}