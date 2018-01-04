#pragma once
#include<iostream>
#include<stack>
//#include<vector>
//#include<string>
using std::cout;
using std::stack;
//using std::vector;
//using std::string;

// TODO: 
// print left-root-right with stack
// parse expressions like ((8-5)+7)

class BinTree {
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int _data) : data(_data), left(nullptr), right(nullptr) {}

        bool childless() const {
            return left == nullptr && right == nullptr;
        }
    };

    Node* root;

public:
    BinTree() : root(nullptr) {}
    ~BinTree() {
        // ...
    }

    void add(int x, const char* path) {
        add(x, root, path);
    }

    // 3 funtions with stack:

    // Prints the tree root-left-right
    void print_stacky_way() const {
        stack<Node*> st;

        if (root != nullptr) {
            st.push(root);
        }

        while (!st.empty()) {
            Node* crr = st.top();
            st.pop();
            
            cout << crr->data << ' ';
            if (crr->right != nullptr) st.push(crr->right);
            if (crr->left  != nullptr) st.push(crr->left);
        }
    }

    // Returns the number of elements
    int count_stacky_way() const {
        stack<Node*> st;
        int result = 0;

        if (root != nullptr) {
            st.push(root);
        }

        while (!st.empty()) {
            Node* crr = st.top();
            st.pop();

            result += 1;
            if (crr->right != nullptr) st.push(crr->right);
            if (crr->left  != nullptr) st.push(crr->left);
        }
        return result;
    }

    // Returns the number of leaves
    int leaves_stacky_way() const {
        stack<Node*> st;
        int result = 0;

        if (root != nullptr) {
            st.push(root);
        }

        while (!st.empty()) {
            Node* crr = st.top();
            st.pop();

            if (crr->childless()) {
                result += 1;
            }
            if (crr->right != nullptr) st.push(crr->right);
            if (crr->left != nullptr) st.push(crr->left);
        }
        return result;
    }

private:
    void add(int x, Node*& sub_root, const char* path) {    // "LRL" is treated like const char*,
        if (sub_root == nullptr) {                          // not all compilers will accept char* as type here.
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
    
    // Recursive functions
    void print_in_row(Node* sub_root) const {
        if (sub_root == nullptr) {
            return;
        }
        cout << sub_root->data << " ";
        print_in_row(sub_root->left);
        print_in_row(sub_root->right);
    }

    unsigned count_elements(Node* sub_root) const {
        if (sub_root == nullptr) {
            return 0;
        }
        return 1
            + count_elements(sub_root->left)
            + count_elements(sub_root->right);
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