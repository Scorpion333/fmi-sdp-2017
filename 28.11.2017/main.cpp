#include<iostream>
#include"KnightConfig.h"
#include"BinTree.h"
using std::cout;

void test_knights() {
    KnightConfig kc({ 1, 0, 0, 1,
                      0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 1, 0, 1 });

    kc.print_current();
    cout << kc.is_valid_config(4);
}

void test_bintree_bfs_iterator() {
    BinTree bt;
    bt.add(1, "");
    bt.add(2, "L");
    bt.add(3, "R");
    bt.add(4, "LL");
    bt.add(5, "LR");
    bt.add(7, "RR");
    bt.add(7, "RRR");

    for (BinTree::BFSIterator it = bt.bfs_begin(); it != bt.bfs_end(); it++) {
        *it += 3;
        cout << *it << " ";
    }
    // Expected output: 4 5 6 7 8 10 10
}

int main() {
    // test_knights();

    test_bintree_bfs_iterator();

    cout << '\n';
    return 0;
}
