#include <iostream>
#include <string>
#include "Rparser.h"

int main() {
    string str;

    cout << "> ";
    getline(cin, str);

    Rparser rp;
    while (!cin.eof()) {
        cout << rp.parse(str) << endl;
        cout << "> ";
        getline(cin, str);
    }
    return 0;
}

