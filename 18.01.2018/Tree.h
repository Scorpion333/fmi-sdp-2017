#pragma once
#include<iostream>
#include<vector>
#include<queue>
using std::cout;
using std::vector;
using std::queue;

template<typename T>
struct Node {
    T data;
    vector<Node*> children;
    
    Node(const T& _data) : data(_data), children() {}
    
    // Useful methods when it comes to creating a tree. Sorry I forgot to write them earlier.
    void add_child(const T& child_data) {
        children.push_back(new Node<T>(child_data));
    }
    void add_children(const vector<T>& _children) {
        for (int i = 0; i < _children.size(); i++) {
            add_child(_children[i]);
        }
    }
};

// I showed these two functions in a class MTree, but I decided to rewrite them for bare Nodes.
template<typename T>
void print_bfs(const Node<T>* root) {
    if (root == nullptr)
        return;

    queue<const Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        const Node<T>* crr = q.front();
        q.pop();
        cout << crr->data << ' ';
        for (unsigned i = 0; i < crr->children.size(); i++) {
            q.push(crr->children[i]);
        }
    }
}

template<typename T>
void print_dfs(const Node<T>* root) {
    if (root == nullptr)
        return;

    cout << root->data << ' ';
    for (unsigned i = 0; i < root->children.size(); i++) {
        print_dfs(root->children[i]);
    }
}

template<typename T>
int evens(const Node<T>* root) {
    if (root == nullptr)
        return 0;

    int sum = 0;
    if (root->data % 2 == 0)
        sum++;

    for (int i = 0; i < root->children.size(); i++) {
        sum += evens(root->children[i]);
    }
    return sum;
}

template<typename T>
int height(const Node<T>* root) {
    if (root == nullptr)
        return 0;

    int max = 0;
    for (int i = 0; i < root->children.size(); i++) {
        int h = height(root->children[i]);
        if (h > max) {
            max = h;
        }
    }
    return 1 + max;
}

template<typename T>
int count_leaves(const Node<T>* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->children.size() == 0) {
        return 1;
    }
    int sum = 0;
    for (int i = 0; i < root->children.size(); i++) {
        sum += count_leaves(root->children[i]);
    }
    return sum;
}

// One of you asked me to write this function, so I wrote it...
template<typename T>
int search_count(const Node<T>* root, bool(*pred)(const T&)) {
    if (root == nullptr)
        return 0;

    int sum = 0;
    if (pred(root->data))
        sum++;

    for (int i = 0; i < root->children.size(); i++) {
        sum += search_count(root->children[i], pred);
    }
    return sum;
}

// ...and a predicate to test with.
bool larger_than_90(const int& x) {
    return x > 90;
}


// Test time!
#include"expect.h"

void test_tree() {
    cout << "--- --- TESTING THE TREE --- ---\n\n";

    Node<int>* tree = new Node<int>(1);                                     
                                                                            
    tree->add_children({ 2, 3, 4 });         //   1 -> 2, 3, 4               // 
                                                                             // The whole tree:
    tree->children[1]->add_child(100);       //   3 -> 100                   // 
                                                                             //       1                                                         
    tree->children[1]                                                        //     / | \      
        ->children[0]                                                        //    2  3  4                                
        ->add_children({ 200, 300, 400 });   // 100 -> 200 300 400           //       |    \   
                                                                             //      100    5
    tree->children[1]                        // children[1] of 1 is 3        //    /  |  \ 
        ->children[0]                        // children[0] of 3 is 100      // 200  300  400
        ->children[2]                        // children[2] of 100 is 400    //            |
        ->add_child(500);                    // 400 -> 500                   //           500 
                                                                             //
    tree->children[2]->add_child(5);         // 4 -> 5                       //

    cout << "BFS:\n";
    print_bfs(tree);
    expect("1 2 3 4 100 5 200 300 400 500");

    cout << "DFS:\n";
    print_dfs(tree);
    expect("1 2 3 100 200 300 400 500 4 5");
    
    cout << "Evens:  " << evens(tree) << '\n'
         << "Height: " << height(tree) << '\n'
         << "Leaves: " << count_leaves(tree);
    expect("7 5 5");

    cout << "Larger than 90: " << search_count<int>(tree, larger_than_90);
    expect("5");
}