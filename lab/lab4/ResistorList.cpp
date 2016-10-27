//
// Created by CharlieHu on 2016-10-25.
//

#include "ResistorList.h"
#include "NodeList.h"

ResistorList::ResistorList() {
    head = NULL;
    end = NULL;
    length = 0;
}

ResistorList::~ResistorList() {
    Resistor *currentR = head;
    while (currentR != NULL) {
        Resistor *desR = currentR;
        currentR = currentR->getNext();
        delete desR;
    }
}

Resistor *ResistorList::findRByName(const string &name) const {
    Resistor *currentR = head;
    if (currentR == NULL) {
        r_list_exception re("Error: resistor " + name + " not found");
        throw re;
    }
    while (true) {
        if (currentR->getName() != name) {
            currentR = currentR->getNext();
            if (currentR != NULL) {
                continue;
            } else {
                // not found
                r_list_exception re("Error: resistor " + name + " not found");
                throw re;
            }
        } else {
            return currentR;
        }
    }
}

void ResistorList::deleteRByName(const string &name) {
    //maintain the resistor linked list
    Resistor *currentR = findRByName(name);
    Resistor *prevR = currentR->getPrevious();
    Resistor *nextR = currentR->getNext();
    // handle the head case
    if (prevR != NULL) {
        prevR->setNext(nextR);
    } else {
        head = nextR;
    }
    // handle the end case
    if (nextR != NULL) {
        nextR->setPrevious(prevR);
    } else {
        end = prevR;
    }
    delete currentR;
    // maintain length
    length--;
}

double ResistorList::modifyRByName(const string &name, const double resistance) {
    Resistor *r = findRByName(name);
    double oldResistance = r->getResistance();
    r->setResistance(resistance);
    return oldResistance;
}

void ResistorList::insertR(Resistor *r) {
    try {
        findRByName(r->getName());
    } catch (r_list_exception &re) {
        // if not found
        r->setPrevious(end);
        if (end != NULL)
            end->setNext(r);
        end = r;
        if (head == NULL)
            head = r;
        length++;
        return;
    }
    // if found
    r_list_exception re("Error: resistor " + r->getName() + " already exists");
    throw re;
}

const string ResistorList::listInfo() const {
    stringstream ss;
    Resistor *currentR = head;
    while (currentR != NULL) {
        ss << "\n" << *currentR;
        currentR = currentR->getNext();
    }
    return ss.str();
}

int ResistorList::getLength() const {
    return length;
}

Resistor *ResistorList::getHead() const {
    return head;
}

r_list_exception::r_list_exception(const string &s) {
    msg = s;
}

r_list_exception::r_list_exception(r_list_exception &le) {
    msg = le.msg;
}
