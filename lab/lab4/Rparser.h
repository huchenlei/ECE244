//
// Created by CharlieHu on 2016-10-08.
//

#ifndef LAB3_1_RPARSER_H
#define LAB3_1_RPARSER_H

#define DEFAULT_VECTOR_SIZE 5

#include <sstream>
#include <ostream>
#include <iomanip>

#include "NodeList.h"
#include "ResistorList.h"

using namespace std;

// reinventing Vector since the use of Vector from std lib is not allowed in lab4
// this myVector is used to hold string
class myVector {
private:
    int size = DEFAULT_VECTOR_SIZE;
    int currentCoursor = 0;
    string *capsule;
public:
    virtual ~myVector();

    myVector();

    int getSize() const;

    myVector(int size);

    string &operator[](const int index);

    void push_back(const string &s);
};

/*
 * The Rparser class handles the command input from keyboard(or possibly any other source)
 * and return the result as string to be output to any given destination(terminal or text file)
 *
 * parse: detect command name and forward request to corresponding handling methods
 * handling methods: take myVector command as input, return the string processed
 *
 * the Rparser class has a field nodeList for saving node information
 * each node has its own resistorList, while Rparser still maintain a global copy of resistorList
 * as a field in order to facilitate the searching of resistors by their names, i.e. when inserting
 * a resistor, the resistor it self is added to the global resistorList, and two copies(on heap) are
 * add to the resistorList of Nodes the resistor is connected to.
 */
class Rparser {
private:
    NodeList *nodeList;
    ResistorList *resistorList;

public:
    Rparser();

    ~Rparser();

    string parse(const string &s);

    //handling methods
    string insertR(myVector &raw_cmd);

    string modifyR(myVector &raw_cmd);

    string printNode(myVector &raw_cmd);

    string printR(myVector &raw_cmd);

    string deleteR(myVector &raw_cmd);

    string setV(myVector &raw_cmd);

    string unsetV(myVector &raw_cmd);

    string solve(myVector &raw_cmd);

};

//user input checking functions
void check_resistance(double resistance);

//@deprecated
// since the printR all branch no longer exists
void check_name(string name);

void check_connection(int node1, int node2);

void check_args(myVector &raw_cmd, int n);

void check_args_few(myVector &raw_cmd, int n);

void check_args_more(myVector &raw_cmd, int n);

//exception handling class
class args_exception : exception {
public:
    string msg;

    args_exception(const string &s);

    args_exception(args_exception &ae);

    ~args_exception() throw() {}
};

//reinventing some wheels(not available in C++98)
myVector split(const string &s, char sep);

string to_str(int n);

//with decimal places specified
string to_str(double d, int n);

#endif //LAB3_1_RPARSER_H
