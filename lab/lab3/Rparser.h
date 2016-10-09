//
// Created by CharlieHu on 2016-10-08.
//

#ifndef LAB3_1_RPARSER_H
#define LAB3_1_RPARSER_H

#include <sstream>
#include <ostream>
#include <vector>
#include <iomanip>

#include "Node.h"
#include "Resistor.h"

#define MIN_NODE_NUMBER 0

using namespace std;

class Rparser {
private:
    vector<Resistor*> resistorArray;
    vector<Node*> nodeArray;

public:
    Rparser();

    ~Rparser();

    string parse(const string &s);

    void insert_resistor(string &name, double resistance, int node1, int node2);

    double modify_resistor(string &name, double resistance);

    void delete_resistor(string &name);

    void delete_attached_resistor(int rIndex, int nodeIndex);

    bool node_array_contains(int nodeIndex);

    Node* find_node_by_index(int nodeIndex);

    Resistor* find_resistor_by_name (string &name);

    Resistor* find_resistor_by_index(int rIndex);

    string resistor_info(string &name);

    string node_info(int nodeIndex);


};

//user input checking functions
void check_resistance(double resistance);

void check_node(int node);

void check_name(string name);

void check_connection(int node1, int node2);

void check_args(vector<string> raw_cmd, int n);

void check_args_few(vector<string> raw_cmd, int n);

void check_args_more(vector<string> raw_cmd, int n);

void check_max_val(int maxVal);

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

string to_str(double d);

//with decimal places specified
string to_str(double d, int n);

int stoint(const string &s);

double stodouble(const string &s);

#endif //LAB3_1_RPARSER_H
