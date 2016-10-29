/*
 * File:   Node.h
 * Author: JC and VB
 * Author: TSA
 *
 * Updated on August 24, 2016, 01:40 PM
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <sstream>
#include <vector>
#include "ResistorList.h"

/*
 * Data Holding Class
 * as part of the design of NodeList(Linked List)
 * similar to Resistor Class
 */

using namespace std;

class Node {
private:
    int nodeIndex;
    Node *next;
    Node *previous;
    ResistorList *resistorList;
    double voltage;
    bool source;

public:
    ~Node();

    Node(int nodeIndex);

    Node *getNext() const;

    Node *getPrevious() const;

    void setPrevious(Node *previous);

    void setNext(Node *next);

    void addResistor(Resistor &r);

    int getNodeIndex() const;

    void setNodeIndex(int nodeIndex);

    string nodeInfo();

    void modifyRByName(const string &name, const double resistance);

    void deleteRByName(const string &name);

    void setResistorList(ResistorList *resistorList);

    ResistorList *getResistorList() const;

    double getVoltage() const;

    void setVoltage(double voltage);

    bool isSource() const;

    void setSource(bool source);
};


#endif	/* NODE_H */