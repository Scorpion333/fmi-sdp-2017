#include<iostream>
#include<vector>
#include<stack>
using std::cout;
using std::vector;
using std::stack;

template<typename T>
struct Node {
    T data;
    vector<Node*> children;

    Node(const T& _data) : data(_data), children() {}

    void add_child(const T& child_data) {               // Two useful methods for creating a tree.
        children.push_back(new Node<T>(child_data));
    }
    void add_children(const vector<T>& _children) {
        for (int i = 0; i < _children.size(); i++) {
            add_child(_children[i]);
        }
    }
};

template<typename T>
void print_leaves_rec(const Node<T>* root) {
    if (root == nullptr) {                    // This is not the bottom of recursion. (No subtree can be empty.)
        return;                               // It is just a special case
    }
    if (root->children.size() == 0) {         // This is the recursion's bottom - when
        cout << root->data << ' ';            // root->children.size() is 0.
        return;
    }
    for (int i = 0; i < root->children.size(); i++) {       
        print_leaves_rec(root->children[i]);                
    }
}

template<typename T>
void print_leaves_with_stack(const Node<T>* root) {
    if (root == nullptr) {                    // This was not the bottom of recursion, just a special
        return;                               // case => it remains special even in the stacky solution.
    }
    stack<const Node<T>*> st;
    st.push(root);

    while (!st.empty()) {
        const Node<T>* crr = st.top();
        st.pop();

        if (crr->children.size() == 0) {      // If crr is a leaf,
            cout << crr->data << ' ';         // print it.
        }
        else {                                                      // Else print its children's leaves.
            for (int i = crr->children.size() - 1; i >= 0; i--)     // We push them in reversed order, because
                st.push(crr->children[i]);                          // the last pushed child will be popped
        }                                                           // first. Here i must NOT be unsigned.
    }
}

// Test time!
void expect(const char* output) {
    cout << "\nExpected:\n" << output << "\n\n";
}

int main() {
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

    cout << "Recursion:\n";
    print_leaves_rec(tree);

    cout << "\nStack:\n";
    print_leaves_with_stack(tree);
    expect("2 200 300 500 5");

    return 0;
}