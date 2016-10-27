#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

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

