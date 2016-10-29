#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/*
 * The Resistor class is responsible for holding data, and is part of the design of ResistorList(Linked List)
 * Since the Node class already includes Resistor.h, to avoid compiler link error, nodes the resistor
 * is connected to is not specified by Pointers to Node, instead, array of nodeIndex.
 */

class Resistor {
private:
    int rIndex;
    double resistance; // resistance (in Ohms)
    string name; // C++ string holding the label
    int endpointNodeIDs[2]; // IDs of nodes it attaches to
    Resistor *next;
    Resistor *previous;

public:
    static int rIndexCount;

    Resistor();

    Resistor(double resistance, const string &name, int *endpointNodeIDs);
    //copy constructor
    Resistor(const Resistor &other);

    ~Resistor();

    // creates a copy on heap(with "new" statement)
    Resistor* deepCopy();

    string getName() const; // returns the name

    double getResistance() const; // returns the resistance

    void setResistance(double resistance_);

    int getRIndex() const;

    Resistor *getNext() const;

    void setNext(Resistor *next);

    void setRIndex(int rIndex);

    void setName(const string &name);

    const int *getEndpointNodeIDs() const;

    Resistor *getPrevious() const;

    void setPrevious(Resistor *previous);

    friend ostream &operator<<(ostream &, const Resistor &);
};

ostream &operator<<(ostream &, const Resistor &);

#endif	/* RESISTOR_H */

