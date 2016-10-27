//
// Created by CharlieHu on 2016-10-08.
//

#ifndef LAB3_1_RPARSER_H
#define LAB3_1_RPARSER_H

#include <sstream>
#include <ostream>
#include <vector>
#include <iomanip>

#include "NodeList.h"
#include "ResistorList.h"

#define MIN_NODE_NUMBER 0

using namespace std;

class Rparser {
private:
    NodeList *nodeList;
    ResistorList *resistorList;

public:
    Rparser();

    ~Rparser();

    string parse(const string &s);

    string insertR(vector<string> &raw_cmd);

    string modifyR(vector<string> &raw_cmd);

    string printNode(vector<string> &raw_cmd);

    string printR(vector<string> &raw_cmd);

    string deleteR(vector<string> &raw_cmd);

    string setV(vector<string> &raw_cmd);

    string unsetV(vector<string> &raw_cmd);

    string solve(vector<string> &raw_cmd);

};

//user input checking functions
void check_resistance(double resistance);

void check_name(string name);

void check_connection(int node1, int node2);

void check_args(vector<string> raw_cmd, int n);

void check_args_few(vector<string> raw_cmd, int n);

void check_args_more(vector<string> raw_cmd, int n);

//exception handling class
class args_exception : exception {
public:
    string msg;

    args_exception(const string &s);

    args_exception(args_exception &ae);

    ~args_exception() throw() {}
};

//reinventing some wheels(not available in C++98)
vector<string> split(const string &s, char sep);

string to_str(int n);

//with decimal places specified
string to_str(double d, int n);

#endif //LAB3_1_RPARSER_H
