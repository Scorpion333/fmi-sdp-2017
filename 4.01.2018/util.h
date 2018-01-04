#pragma once
#include<iostream>
using std::cout;

void expect(const char* output) {                   // Useful for short tests
    cout << "\nExpected:\n" << output << "\n\n";
}