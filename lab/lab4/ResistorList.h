//
// Created by CharlieHu on 2016-10-25.
//

#ifndef LAB4_RESISTORLIST_H
#define LAB4_RESISTORLIST_H

#include "Resistor.h"
#include <sstream>

class ResistorList {
private:
    Resistor *head;
    Resistor *end;
    int length;

public:
    ResistorList();

    int getLength() const;

    Resistor *findRByName(const string &name) const;

    void deleteRByName(const string &name);

    // return the old resistance
    double modifyRByName(const string &name, const double resistance);

    const string listInfo() const;

    void insertR(Resistor *r);

    Resistor *getHead() const;

    ~ResistorList();
};

//exception handling class
class r_list_exception : exception {
public:
    string msg;

    r_list_exception(const string &s);

    r_list_exception(r_list_exception &ae);

    ~r_list_exception() throw() {}
};


#endif //LAB4_RESISTORLIST_H
