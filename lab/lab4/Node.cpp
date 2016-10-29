//
// Created by CharlieHu on 2016-10-08.
//

#include "Node.h"

Node::~Node() {
    delete resistorList;
    if(previous != NULL)
        previous->next = next;
    if(next != NULL)
        next->previous = previous;
}

Node::Node(int nodeIndex) : nodeIndex(nodeIndex), voltage(0), source(false), next(NULL), previous(NULL) {
    resistorList = new ResistorList();
}

void Node::addResistor(Resistor &r) {
    Resistor *new_res = r.deepCopy();
    resistorList->insertR(new_res);
}

int Node::getNodeIndex() const {
    return nodeIndex;
}

void Node::setNodeIndex(int nodeIndex) {
    Node::nodeIndex = nodeIndex;
}

Node *Node::getNext() const {
    return next;
}

void Node::setNext(Node *next) {
    Node::next = next;
}

ResistorList *Node::getResistorList() const {
    return resistorList;
}

void Node::setResistorList(ResistorList *resistorList) {
    Node::resistorList = resistorList;
}

string Node::nodeInfo() {
    stringstream ss;
    ss << "\nConnections at node " << nodeIndex << ": " << resistorList->getLength() << " resistor(s)";
    ss << resistorList->listInfo();
    return ss.str();
}

void Node::modifyRByName(const string &name, const double resistance) {
    resistorList->modifyRByName(name, resistance);
}

Node *Node::getPrevious() const {
    return previous;
}

void Node::setPrevious(Node *previous) {
    Node::previous = previous;
}

double Node::getVoltage() const {
    return voltage;
}

void Node::setVoltage(double voltage) {
    Node::voltage = voltage;
}

void Node::deleteRByName(const string &name) {
    resistorList->deleteRByName(name);
}

bool Node::isSource() const {
    return source;
}

void Node::setSource(bool source) {
    Node::source = source;
}
