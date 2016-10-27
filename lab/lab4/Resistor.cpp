//
// Created by CharlieHu on 2016-10-08.
//

#include "Resistor.h"

int Resistor::rIndexCount = 0;

Resistor::Resistor() : next(NULL), previous(NULL) {}

Resistor::Resistor(double resistance, const string &name, int *endpointNodeIDs_)
        : resistance(resistance), name(name), next(NULL), previous(NULL) {
    endpointNodeIDs[0] = endpointNodeIDs_[0];
    endpointNodeIDs[1] = endpointNodeIDs_[1];
    rIndex = rIndexCount++;
}

Resistor::Resistor(const Resistor &other) : resistance(other.resistance), name(other.name), rIndex(other.rIndex),
                                            next(NULL), previous(NULL) {
    endpointNodeIDs[0] = other.endpointNodeIDs[0];
    endpointNodeIDs[1] = other.endpointNodeIDs[1];
}

Resistor::~Resistor() {
    if (previous != NULL)
        previous->next = next;
    if (next != NULL)
        next->previous = previous;
}

Resistor *Resistor::deepCopy() {
    Resistor *new_res = new Resistor(resistance, name, endpointNodeIDs);
    new_res->setRIndex(rIndex);
    rIndexCount--;
    return new_res;
}

//getters and setters
string Resistor::getName() const {
    return name;
}

double Resistor::getResistance() const {
    return resistance;
}

void Resistor::setResistance(double resistance) {
    Resistor::resistance = resistance;
}

int Resistor::getRIndex() const {
    return rIndex;
}

void Resistor::setRIndex(int rIndex) {
    Resistor::rIndex = rIndex;
}

void Resistor::setName(const string &name) {
    Resistor::name = name;
}

const int *Resistor::getEndpointNodeIDs() const {
    return endpointNodeIDs;
}

ostream &operator<<(ostream &os, const Resistor &resistor) {
    int resistance = (int) (resistor.resistance);
    os << resistor.getName() << "                  ";
    //format output
    while (resistance < 10000) {
        os << " ";
        resistance *= 10;
    }
    os << setprecision(2) << fixed << resistor.resistance << " Ohms " << resistor.getEndpointNodeIDs()[0] << " -> "
       << resistor.getEndpointNodeIDs()[1];
    return os;
}

Resistor *Resistor::getNext() const {
    return next;
}

void Resistor::setNext(Resistor *next) {
    Resistor::next = next;
}

Resistor *Resistor::getPrevious() const {
    return previous;
}

void Resistor::setPrevious(Resistor *previous) {
    Resistor::previous = previous;
}
