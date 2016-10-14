//
// Created by CharlieHu on 2016-10-08.
//

#include "Node.h"

int Node::maxNodeNumber = 100;

Node::Node() {
    numRes = 0;
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++) {
        resIDArray[i] = -1;
    }
}

Node::~Node() {
}

Node::Node(int nodeIndex_) {
    numRes = 0;
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++) {
        resIDArray[i] = -1;
    }
    nodeIndex = nodeIndex_;
}

bool Node::canAddResistor(int rIndex) {
    return canAddResistor();
}

bool Node::canAddResistor() {
    if (numRes >= MAX_RESISTORS_PER_NODE) {
        return false;
    } else {
        return true;
    }
}


void Node::addResistor(int rIndex) {
    if (canAddResistor(rIndex)) {
        for (int i = 0; i < MAX_RESISTORS_PER_NODE; ++i) {
            if (resIDArray[i] == -1) {
                resIDArray[i] = rIndex;
                break;
            }
        }
        numRes++;
    } else {
        throw exception();
    }
}

int Node::getNodeIndex() const {
    return nodeIndex;
}

void Node::setNodeIndex(int nodeIndex) {
    Node::nodeIndex = nodeIndex;
}

int Node::getNumRes() const {
    return numRes;
}

void Node::setNumRes(int numRes) {
    Node::numRes = numRes;
}

int *Node::getResIDArray() {
    return resIDArray;
}

bool Node::isEmpty() {
    if(numRes == 0){
        return true;
    }else{
        return false;
    }
}

void Node::reset() {
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++) {
        resIDArray[i] = -1;
    }
    numRes = 0;
}
