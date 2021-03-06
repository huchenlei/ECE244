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
//    cout << raw_str << endl;
//    str = raw_str.substr(2);
//
//    Rparser rp;
//    while (!f.eof()) {
//        cout << str << endl;
//        string output = rp.parse(str);
//        string std_output;
//        cout << output << endl;
//        cout << "------------------" << endl;
//        while(true) {
//            getline(f, raw_str);
//            if (raw_str.length() == 1){
//                return 0;
//            }
//            if (raw_str[0] == '>') {
//                str = raw_str.substr(2);
//                break;
//            } else {
//                cout << raw_str << endl;
//                std_output+=raw_str;
//            }
//        }
//        if(std_output == output){
//            cout << "PASS!" << endl;
//        }else{
//            cout << "FAIL!" << endl;
//        }
//        cout << "\n\n";
//        cout << "Exec: \n";
//    }
//
//    return 0;
//}
