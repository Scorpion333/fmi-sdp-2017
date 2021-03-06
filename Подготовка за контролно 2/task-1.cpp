#include<iostream>
using std::cout;

template<typename T>
struct ListNode {
    T data;
    ListNode<T>* next;
    ListNode(const T& _data) : data(_data), next(nullptr) {}
};

template<typename T>
bool has_element(const ListNode<T>* first, const T& x) {
    if (first == nullptr) {
        return false;
    }
    if (first->data == x) {
        return true;
    }
    return has_element(first->next, x);
}

// Removes all occurrences of the element                       // Challenge: This function looks great and works fine,
template<typename T>                                            // but can be made better. Add two lines to fix it.
void remove_all_occs(ListNode<T>*& first, const T& removed) {
    if (first == nullptr) {
        return;
    }
    remove_all_occs(first->next, removed);      // First we remove it from the 'tail' (the sublist from first->next)
    if (first->data == removed) {               // and then from the 'head' (the first position).
        first = first->next;                    // This line is legal because first is a reference.
    }
}

template<typename T>
void remove_duplicates(ListNode<T>*& first) {
    if (first == nullptr) {
        return;
    }
    if (has_element(first->next, first->data)) {        // If first->data needs to be removed,
        remove_all_occs(first, first->data);            // we remove it.
        remove_duplicates(first);                       // Then we remove all duplicates from the remainder.
        return;
    }
    remove_duplicates(first->next);                     // If first->data can stay alive, we just go on.
}


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
    expect("3");

    return 0;
}