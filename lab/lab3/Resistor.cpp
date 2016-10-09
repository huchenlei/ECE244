//
// Created by CharlieHu on 2016-10-08.
//

#include "Resistor.h"

int Resistor::rIndexCount = 0;
int Resistor::maxResistors = 100;

Resistor::Resistor() {}

Resistor::Resistor(string &name ) {
    name = name ;
}

Resistor::Resistor(string &name , double resistance , int *endpoints ) {
    Resistor::rIndex = Resistor::rIndexCount;
    Resistor::rIndexCount++;
    Resistor::name = name ;
    Resistor::resistance = resistance ;
    Resistor::endpointNodeIDs[0] = endpoints [0];
    Resistor::endpointNodeIDs[1] = endpoints [1];
}

Resistor::~Resistor() {
//    cout << "Resistor des called!" << endl;
}

//getters and setters
string Resistor::getName() const {
    return name;
}

double Resistor::getResistance() const {
    return resistance;
}

void Resistor::setResistance(double resistance ) {
    Resistor::resistance = resistance ;
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
//    os << resistor.getName() << "_________________ ";
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