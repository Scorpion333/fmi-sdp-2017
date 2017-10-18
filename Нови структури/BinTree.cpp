#include<iostream>
using std::cout;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int _data) : data(_data), left(nullptr), right(nullptr) {}
};

class BinTree {
    Node* root;

public:
    BinTree() : root(nullptr) {}

    ~BinTree() {
        del(root);
    }

    void add(int x, char* path) {
        add(x, root, path);
    }

    unsigned count_elements() const {
        return count_elements(root);
    }

    void print() const {
        print(root);
    }

    unsigned height() const {
        return height(root);
    }

    unsigned leaves() const {
        return leaves(root);
    }
private:

    void add(int x, Node*& sub_root, char* path) {
        if (sub_root == nullptr) {
            sub_root = new Node(x);
            return;
        }
        if (path[0] == 'L') {
            add(x, sub_root->left, path + 1);
            return;
        }
        // Now path[0] is 'R'
        add(x, sub_root->right, path + 1);
        return;
    }

    unsigned count_elements(Node* sub_root) const {
        if (sub_root == nullptr) {
            return 0;
        }
        return 1
            + count_elements(sub_root->left)
            + count_elements(sub_root->right);
    }

    void del(Node*& sub_root) {
        if (sub_root == nullptr) {
            return;
        }
        del(sub_root->left);
        del(sub_root->right);
        delete sub_root;
    }

    void print(Node* sub_root) const {
        if (sub_root == nullptr) {
            return;
        }
        cout << sub_root->data << " ";
        print(sub_root->left);
        print(sub_root->right);
    }

    unsigned height(Node* sub_root) const {
        if (sub_root == nullptr) {
            return 0;
        }
        unsigned left = height(sub_root->left);
        unsigned right = height(sub_root->right);
        return 1 + (left > right ? left : right);
    }

    unsigned leaves(Node* sub_root) const {
        if (sub_root == nullptr) {
            return 0;
        }
        if (sub_root->left == nullptr && sub_root->right == nullptr) {
            return 1;
        }
        return leaves(sub_root->left) + leaves(sub_root->right);
    }
};

void test_bin_tree() {
    BinTree bt;
    bt.add(2, "");
    bt.add(4, "L");
    bt.add(6, "R");
    bt.add(8, "RL");
    bt.add(10, "RR");
    bt.add(12, "RLR");
    cout << "Size:   " << bt.count_elements() << '\n';    // Expected: 6
    cout << "Height: " << bt.height() << '\n';            // Expected: 4
    cout << "Leaves: " << bt.leaves() << '\n';            // Expected: 3
    cout << "Elems:  ";
    bt.print();         // Expected: 2 4 6 8 12 10
    cout << '\n';
}

int main() {
    test_bin_tree();
    return 0;
}