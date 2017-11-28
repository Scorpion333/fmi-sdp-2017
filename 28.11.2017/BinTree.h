#pragma once
#include<iostream>
#include<queue>
using std::cout;
using std::queue;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int _data) : data(_data), left(nullptr), right(nullptr) {}
};

class BinTree {
    Node* root;

public:
    class BFSIterator {
        queue<Node*> q;

        Node* current() const {
            return q.front();
        }
    public:
        BFSIterator(Node* node) : q() {
            q.push(node);
        }

        BFSIterator& operator++ () {
            Node* crr = current();
            q.pop();
            if (crr->left != nullptr) q.push(crr->left);
            if (crr->right != nullptr) q.push(crr->right);
            if (q.empty()) {
                q.push(nullptr);
            }
            return *this;
        }
        BFSIterator operator++ (int) {
            BFSIterator old = *this;
            ++*this;
            return old;
        }

        bool operator != (const BFSIterator& other) const {
            return current() != other.current();
        }
       
        int operator * () const {
            return current()->data;
        }
        int& operator * () {
            return current()->data;
        }
    };

    BFSIterator bfs_begin() const {
        return BFSIterator(root);
    }
    BFSIterator bfs_end() const {
        return BFSIterator(nullptr);
    }

    BinTree() : root(nullptr) {}

    ~BinTree() {
       del(root);
    }

    void add(int x, char* path) {
        add(x, root, path);
    }
  
    // Prints root-left-right
    void print_in_row() const {
        print_in_row(root);
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
    
    void del(Node*& sub_root) {
        if (sub_root == nullptr) {
            return;
        }
        del(sub_root->left);
        del(sub_root->right);
        delete sub_root;
    }
   
    // Prints root-left-right
    void print_in_row(Node* sub_root) const {
        if (sub_root == nullptr) {
            return;
        }
        cout << sub_root->data << " ";
        print_in_row(sub_root->left);
        print_in_row(sub_root->right);
    }
};
