#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include<utility>   // For std::pair
#include"expect.h"
using std::cout;
using std::ostream;
using std::string;
using std::set;
using std::map;
using std::pair;

void use_set() {        // Examples with std::set

    cout << "--- --- USING STD::SET --- ---\n\n";

    set<int> s;

    s.insert(11);           // 11
    s.insert(12);           // 11 12
    s.insert(12);           // 11 12
    s.insert(13);           // 11 12 13
    
    s.erase(12);            // 11 13

    cout << s.count(11);    // 1
    cout << s.count(12);    // 0
    expect("10");

    for (set<int>::iterator it = s.begin(); it != s.end(); ++it) {
        int elem = *it;
        cout << elem << ' ';
    }
    // Short version of the same
    for (int elem : s) {
        cout << elem << ' ';
    }
    expect("11 13 11 13");
}

void use_map() {        // Examples with std::map

    cout << "--- --- USING STD::MAP --- ---\n\n";

    map<string, int> m;
                            // Pairs in m:
    m["edno"] = 1;          // { "edno" => 1 }                  
    m["dve"] = 2;           // { "edno" => 1, "dve" => 2 }
    m["dve"]++;             // { "edno" => 1, "dve" => 3 }
    m["dve"] = 4;           // { "edno" => 1, "dve" => 4 }      

    for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it) {
        cout << (*it).first << ": " << (*it).second << '\n';
    }
    expect(
        "edno: 1\n"
        "dve: 4  (Or the same lines in different order)"
    );

    cout << m.count("edno");    // 1
    cout << m.count("tri");     // 0
    expect("10");
}

// K - Key type, V - Value type
template<typename K, typename V>
ostream& operator << (ostream& out, map<K, V> m) {
    for (map<K, V>::iterator it = m.begin(); it != m.end(); ++it) {
        out << (*it).first << ": " << (*it).second << '\n';
    }
    return out;
}

template<typename K, typename V1, typename V2>
map<K, pair<V1, V2>> product(map<K, V1> m1, map<K, V2> m2) {

    map<K, pair<V1, V2>>& result = *(new map<K, pair<V1, V2>>);
                                                        // Long version:
    for (pair<K, V1> pair1 : m1) {                      // for (map<K, V1>::iterator it = m1.begin(); it != m1.end(); ++it) {
        K key = pair1.first;                            //     pair<K, V1> pair1 = *it;
        if (m2.count(key) == 1) {                       //     K key = pair1.first;
            result[key] = { m1[key], m2[key] };         //     if (m2.count(key) == 1) {
        }                                               //         result[key] = pair<V1, V2>(m1[key], m2[key]);
    }                                                   //     }
    return result;                                      // }
}

// Useful operator, not defined in the library
template<typename X, typename Y>
ostream& operator << (ostream& out, const pair<X, Y>& _pair) {
    out << "{" << _pair.first << ", " << _pair.second << "}";
    return out;
}

void test_product() {
    cout << "--- --- TESTING PRODUCT OF MAPS --- ---\n\n";

    map<string, int>  m1, m2;

    m1["aa"] = 1;       m2["aa"] = 11;
    m1["bb"] = 2;
    m1["cc"] = 3;       m2["cc"] = 13;

    map<string, pair<int, int>> pr = product(m1, m2);
    cout << pr;

    expect(
        "aa: {1, 11}\n"
        "cc: {3, 13}\n"
    );
}
