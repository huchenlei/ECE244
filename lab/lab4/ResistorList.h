//
// Created by CharlieHu on 2016-10-25.
//

#ifndef LAB4_RESISTORLIST_H
#define LAB4_RESISTORLIST_H

#include "Resistor.h"
#include <sstream>

/*
 * The ResistorList class is an implementation of Two-Way linked list, with the length maintained by a private field
 * each time the new resistor coming in, it would be append to the end of the list( why there is a field called end)
 *
 * There is a possible way to get rid of field end:
 * connect the last element's next field to the head element, then the previous field of head element would point
 * to the last element. While that might bring some confusion on looping conditions, the ResistorList is not
 * implemented that way.
 */

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
