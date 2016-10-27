//
// Created by CharlieHu on 2016-10-25.
//

#ifndef LAB4_NODELIST_H
#define LAB4_NODELIST_H
#define MIN_ITERATION_CHANGE 0.0001
#define INITIAL_CHANGE 1.0

#include "Node.h"
#include <iomanip>


class NodeList {
private:
    Node *head;

    Node *end;

    //returns the Iteration change
    double solveNode(Node *node);

    // pre-set for the solve method
    void setUp();

    // get voltages of other nodes(in default order)
    double *getVoltages(Node *node);

    // get resistance of all resistors
    double *getResistances(Node *node);

public:
    ~NodeList();

    Node *findNodeByIndex(const int index) const;

    Node *findOrInsertNode(const int index);

    void deleteR(const Resistor &r);

    Node *getHead() const;

    void setHead(Node *head);

    void solve();

    string voltageInfo();

};

class n_list_exception : exception {
public:
    string msg;

    n_list_exception(const string &s);

    n_list_exception(r_list_exception &ne);

    ~n_list_exception() throw() {}
};

#endif //LAB4_NODELIST_H
