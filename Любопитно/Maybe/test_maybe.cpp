#include"Maybe.h"
#include<iostream>
#include<string>
#include<vector>
using std::cout;
using std::string;
using std::vector;

void expect(const char* output) {
    cout << "\nExpected:\n" << output << "\n\n";
}

void test_maybe() {

    cout << "Maybe<int>:\n\n";

    Maybe<int> def_constr;
    cout << (def_constr == Undefined<int>()) << ' ';       // 1

    Maybe<int> mi = 5;
    mi = 6;
    cout << mi << ' ';                 // 6

    mi = *(new Maybe<int>(7));
    cout << mi << ' ';                 // 7

    int i = mi;
    cout << i + mi << ' ';             // 14
    cout << (mi += 8) << ' ';          // 15

    expect("1 6 7 14 15");

    ///////////////////////////////////////////////////////////

    cout << "Maybe<string>:\n\n";

    Maybe<string> def_constr1;

    cout << (def_constr1 == Undefined<string>()) << ' ';       // 1

    Maybe<string> ms = "5";
    ms = "6";
    cout << ms.value() << ' ';                // 6

    ms = *(new Maybe<string>("7"));
    cout << ms.to_ref() << ' ';               // 7

    string s = ms;
    cout << s + string(ms) << ' ';            // 77
    cout << s + ms.value() << ' ';            // 77
    cout << s + ms.to_ref() << ' ';           // 77
    cout << ((string&)ms += "8") << ' ';      // 78
    cout << (ms.to_ref() += "8") << ' ';      // 788

    expect("1 6 7 77 77 77 78 788");

    ///////////////////////////////////////////////////////////

    cout << "Maybe<vector>:\n\n";
    Maybe<vector<int>> mv({ -1 });
    mv.to_ref().push_back(1);
    mv.to_ref().push_back(3);
    mv.to_ref().push_back(5);

    for (unsigned i = 0; i < mv.to_ref().size(); i++) {
        cout << mv.to_ref()[i] << ' ';
    }
    expect("-1 1 3 5");
}

int main() {
    test_maybe();
    return 0;
}
