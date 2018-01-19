#include<iostream>
using std::cout;

template<typename T>
struct ListNode {
    T data;
    ListNode<T>* next;
    ListNode(const T& _data) : data(_data), next(nullptr) {}
};

// Removes the element once (if it is in the list)                  // Challenge: This function looks great and works fine,
template<typename T>                                                // but can be made better. Add two lines to fix it.
void remove_from_list(ListNode<T>*& first, const T& removed) {
    if (first == nullptr) {
        return;
    }
    if (first->data == removed) {               
        first = first->next;                // This is legal because first is a reference.         
        return;
    }
    remove_from_list(first->next, removed);
}

template<typename T>
void remove_duplicates(ListNode<T>*& first) {
    if (first == nullptr) {
        return;
    }
    remove_duplicates(first->next);                   // After this line, the sublist startting from 'first->next' contains no duplicates.
    remove_from_list(first->next, first->data);       // It contains 'first->data' 0 or 1 times => it is enough to remove 'first->data' once.
}                                                     // Recursion is <3, recursion is life!


// Test time! Here are some useful functions:
template<typename T>
void push_back(ListNode<T>*& first, const T& element) {
    if (first == nullptr) {
        first = new ListNode<T>(element);
        return;
    }
    push_back(first->next, element);
}

template<typename T>
void print_list(const ListNode<T>* first) {
    if (first == nullptr) {
        return;
    }
    cout << first->data << ' ';
    print_list(first->next);
}

void expect(const char* output) {
    cout << "\nExpected:\n" << output << "\n\n";
}

int main() {
    ListNode<int>* lis = nullptr;
    for (int num : { 4, 4, 2, 6, 6, 6, 2, 3, 4 }) {       // Doesn't this look nice? 
        push_back(lis, num);                              // It is absolutely clear what's happenning...
    }
    cout << "Before:\n";
    print_list(lis);
    expect("4 4 2 6 6 6 2 3 4");                          // ...or, if it's not, see this.

    cout << "After:\n";
    remove_duplicates(lis);
    print_list(lis);
    expect("4 2 6 3");
}