#include <iostream>
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

//#include <fstream>
//
//int main() {
//    string str;
//    string raw_str;
//    fstream f;
//    f.open("testcase.txt");
//
//    cout << "Exec: \n";
//    getline(f, raw_str);
//    str = raw_str.substr(2);
//
//    Rparser rp;
//    while (!f.eof()) {
//        cout << str << endl;
//        cout << rp.parse(str) << endl;
//        cout << "------------------" << endl;
//        while(true) {
//            getline(f, raw_str);
//            if (raw_str[0] == '>') {
//                str = raw_str.substr(2);
//                break;
//            } else {
//                cout << raw_str << endl;
//            }
//        }
//        cout << "\n\n";
//        cout << "Exec: \n";
//    }
//    return 0;
//}
//