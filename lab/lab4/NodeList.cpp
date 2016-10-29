//
// Created by CharlieHu on 2016-10-25.
//

#include "NodeList.h"

Node *NodeList::findNodeByIndex(const int index) const {
    Node *currentNode = head;
    if (head == NULL) {
        n_list_exception nl("Error: node " + to_string(index) + " not found");
        throw nl;
    }
    while (true) {
        if (currentNode->getNodeIndex() != index) {
            currentNode = currentNode->getNext();
            if (currentNode != NULL) {
                continue;
            } else {
                // not found
                n_list_exception nl("Error: node " + to_string(index) + " not found");
                throw nl;
            }
        } else {
            return currentNode;
        }
    }
}

Node *NodeList::findOrInsertNode(const int index) {
    Node *node;
    try {
        node = findNodeByIndex(index);
    } catch (n_list_exception &ne) {
        // if not found
        node = new Node(index);
        if (head == NULL) {
            head = node;
            return node;
        }
        Node *currentNode = head;
        while (currentNode != NULL) {
            // head case
            if (currentNode->getNodeIndex() > node->getNodeIndex()) {
                node->setNext(currentNode);
                currentNode->setPrevious(node);
                head = node;
                break;
            }
            // end case
            if (currentNode->getNext() == NULL) {
                node->setPrevious(currentNode);
                currentNode->setNext(node);
                break;
            }
            // middle case
            Node *next = currentNode->getNext();
            if (node->getNodeIndex() > currentNode->getNodeIndex() &&
                node->getNodeIndex() < next->getNodeIndex()) {
                currentNode->setNext(node);
                next->setPrevious(node);
                node->setNext(next);
                node->setPrevious(currentNode);
                break;
            }
            currentNode = currentNode->getNext();
        }
    }
    return node;
}

void NodeList::deleteR(const Resistor &r) {
    Node *nodes[2];
    for (int i = 0; i < 2; ++i) {
        nodes[i] = findNodeByIndex(r.getEndpointNodeIDs()[i]);
        nodes[i]->deleteRByName(r.getName());
        if(nodes[i]->getResistorList()->getHead() == NULL){
            // maintain the linked list
            Node *previous = nodes[i]->getPrevious();
            Node *next = nodes[i]->getNext();
            if(previous != NULL) {
                previous->setNext(next);
            }else{
                head = next;
            }
            if(next != NULL)
                next->setPrevious(previous);
            delete nodes[i];
        }
    }
}

void NodeList::solve() {
    double minIterationChange = INITIAL_CHANGE;
    // empty list case
    if (head == NULL)
        return;
    // pre set
    setUp();
    while (minIterationChange > MIN_ITERATION_CHANGE) {
        // walk through all nodes
        Node *currentNode = head;
        while (currentNode != NULL) {
            double iterationChange = solveNode(currentNode);
            if (iterationChange < minIterationChange)
                minIterationChange = iterationChange;
            currentNode = currentNode->getNext();
        }
    }
}

double NodeList::solveNode(Node *node) {
    if (node->isSource())
        return INITIAL_CHANGE;

    double oldVoltage = node->getVoltage();
    double *voltageList = getVoltages(node);
    double *resistanceList = getResistances(node);
    double R_1 = 0, V = 0;
    for (int i = 0; i < node->getResistorList()->getLength(); ++i) {
        R_1 += 1 / resistanceList[i];
        V += voltageList[i] / resistanceList[i];
    }
    delete voltageList;
    delete resistanceList;
    double newVoltage = (1 / R_1) * V;
    node->setVoltage(newVoltage);

    if (oldVoltage == 0 && newVoltage == 0) {
        return INITIAL_CHANGE;
    } else {
        return newVoltage > oldVoltage ? (newVoltage - oldVoltage) : (oldVoltage - newVoltage);
    }
}

double *NodeList::getResistances(Node *node) {
    const ResistorList *resistorList = node->getResistorList();
    double *resistanceList = new double[resistorList->getLength()];
    Resistor *currentR = resistorList->getHead();
    for (int i = 0; i < resistorList->getLength(); ++i) {
        resistanceList[i] = currentR->getResistance();
        currentR = currentR->getNext();
    }
    return resistanceList;
}

double *NodeList::getVoltages(Node *node) {
    const ResistorList *resistorList = node->getResistorList();
    const int nodeIndex = node->getNodeIndex();
    double *voltageList = new double[resistorList->getLength()];
    Resistor *currentR = resistorList->getHead();
    for (int i = 0; i < resistorList->getLength(); ++i) {
        const int *endpoints = currentR->getEndpointNodeIDs();
        if (endpoints[0] == nodeIndex) {
            voltageList[i] = findNodeByIndex(endpoints[1])->getVoltage();
        } else {
            voltageList[i] = findNodeByIndex(endpoints[0])->getVoltage();
        }
        currentR = currentR->getNext();
    }
    return voltageList;
}

void NodeList::setUp() {
    bool hasSource = false;
    Node *currentNode = head;
    while (currentNode != NULL) {
        if (!currentNode->isSource()) {
            currentNode->setVoltage(0);
        } else {
            hasSource = true;
        }
        currentNode = currentNode->getNext();
    }
    if (!hasSource) {
        n_list_exception ne("Error: no nodes have their voltage set");
        throw ne;
    }
}

string NodeList::voltageInfo() {
    stringstream ss;
    Node *currentNode = head;
    while (currentNode != NULL) {
        ss << "\n" << setprecision(2) << fixed << "Node " << currentNode->getNodeIndex() << ": "
           << currentNode->getVoltage() << " V";
        currentNode = currentNode->getNext();
    }
    return ss.str();
}

Node *NodeList::getHead() const {
    return head;
}

void NodeList::setHead(Node *head) {
    NodeList::head = head;
}

NodeList::~NodeList() {
    Node *currentNode = head;
    while (currentNode != NULL) {
        Node *desN = currentNode;
        currentNode = currentNode->getNext();
        delete desN;
    }
}

n_list_exception::n_list_exception(const string &s) {
    msg = s;
}

n_list_exception::n_list_exception(r_list_exception &ne) {
    msg = ne.msg;
}
