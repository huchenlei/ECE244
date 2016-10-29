//
// Created by CharlieHu on 2016-10-08.
//

#include "Rparser.h"

Rparser::Rparser() {
    nodeList = new NodeList();
    resistorList = new ResistorList();
}

Rparser::~Rparser() {
    delete nodeList;
    delete resistorList;
}

string Rparser::parse(const string &s) {
    vector<string> raw_cmd = split(s, ' ');
    string cmd = raw_cmd[0];
    try {
        if (cmd == "insertR") {
            return insertR(raw_cmd);
        } else if (cmd == "modifyR") {
            return modifyR(raw_cmd);
        } else if (cmd == "printR") {
            return printR(raw_cmd);
        } else if (cmd == "printNode") {
            return printNode(raw_cmd);
        } else if (cmd == "deleteR") {
            return deleteR(raw_cmd);
        } else if (cmd == "setV") {
            return setV(raw_cmd);
        } else if (cmd == "unsetV") {
            return unsetV(raw_cmd);
        } else if (cmd == "solve") {
            return solve(raw_cmd);
        } else {
            return "Error: invalid command";
        }
    } catch (args_exception &e) {
        return e.msg;
    } catch (n_list_exception &e) {
        return e.msg;
    } catch (r_list_exception &e) {
        return e.msg;
    } catch (exception &e) {
        // casting error by stoi/stod
        return "Error: invalid argument";
    }
}

string Rparser::insertR(vector<string> &raw_cmd) {
    check_args_few(raw_cmd, 4);

    string name = raw_cmd[1];
    check_name(name);

    double resistance = stod(raw_cmd[2]);
    check_resistance(resistance);

    int nodeid1 = stoi(raw_cmd[3]);
    int nodeid2 = stoi(raw_cmd[4]);
    check_connection(nodeid1, nodeid2);

    check_args_more(raw_cmd, 4);

    int endpoints[2] = {nodeid1, nodeid2};
    Resistor *r = new Resistor(resistance, name, endpoints);
    resistorList->insertR(r);

    Node *node1 = nodeList->findOrInsertNode(nodeid1);
    Node *node2 = nodeList->findOrInsertNode(nodeid2);
    node1->addResistor(*r);
    node2->addResistor(*r);

    return "Inserted: resistor " + name + " " + to_str(resistance, 2) + " Ohms " + raw_cmd[3] + " -> " +
           raw_cmd[4];
}


string Rparser::modifyR(vector<string> &raw_cmd) {
    string name = raw_cmd[1];
    check_name(name);

    double resistance = stod(raw_cmd[2]);
    check_resistance(resistance);
    check_args(raw_cmd, 2);

    double oldResistance = resistorList->modifyRByName(name, resistance);
    Resistor *r = resistorList->findRByName(name);
    const int *endpoints = r->getEndpointNodeIDs();
    Node *node1 = nodeList->findNodeByIndex(endpoints[0]);
    Node *node2 = nodeList->findNodeByIndex(endpoints[1]);
    node1->modifyRByName(name, resistance);
    node2->modifyRByName(name, resistance);

    return "Modified: resistor " + name + " from " + to_str(oldResistance, 2) + " Ohms to " +
           to_str(resistance, 2) +
           " Ohms";
}

string Rparser::printNode(vector<string> &raw_cmd) {
    check_args(raw_cmd, 1);
    if (raw_cmd[1] == "all") {
        stringstream ss;
        ss << "Print:";
        Node *currentNode = nodeList->getHead();
        while (currentNode != NULL) {
            ss << currentNode->nodeInfo();
            currentNode = currentNode->getNext();
        }
        return ss.str();
    } else {
        int nodeid = stoi(raw_cmd[1]);
        return "Print:" + nodeList->findNodeByIndex(nodeid)->nodeInfo();
    }
}

string Rparser::printR(vector<string> &raw_cmd) {
    check_args(raw_cmd, 1);
    string name = raw_cmd[1];
    stringstream ss;
    ss << *resistorList->findRByName(name);
    return "Print:\n" + ss.str();
}

string Rparser::deleteR(vector<string> &raw_cmd) {
    check_args(raw_cmd, 1);
    if (raw_cmd[1] == "all") {
        delete resistorList;
        delete nodeList;
        resistorList = new ResistorList();
        nodeList = new NodeList();
        return "Deleted: all resistors";
    } else {
        string name = raw_cmd[1];
        nodeList->deleteR(*resistorList->findRByName(name));
        resistorList->deleteRByName(name);
        return "Deleted: resistor " + name;
    }
}

string Rparser::setV(vector<string> &raw_cmd) {
    check_args(raw_cmd, 2);
    int nodeIndex = stoi(raw_cmd[1]);
    double voltage = stod(raw_cmd[2]);
    Node *node = nodeList->findOrInsertNode(nodeIndex);
    node->setVoltage(voltage);
    node->setSource(true);
    return "Set: node " + raw_cmd[1] + " to " + to_str(voltage, 2) + " Volts";
}

string Rparser::unsetV(vector<string> &raw_cmd) {
    check_args(raw_cmd, 1);
    int nodeIndex = stoi(raw_cmd[1]);
    nodeList->findOrInsertNode(nodeIndex)->setSource(false);
    return "Unset: the solver will determine the voltage of node " + raw_cmd[1];
}

string Rparser::solve(vector<string> &raw_cmd) {
    check_args(raw_cmd, 0);
    nodeList->solve();
    return "Solve:" + nodeList->voltageInfo();
}

// methods for checking input
void check_resistance(double resistance) {
    if (resistance < 0) {
        args_exception ae("Error: negative resistance");
        throw ae;
    }
}

void check_name(string name) {
    if (name == "all") {
        args_exception ae("Error: resistor name cannot be the keyword \"all\"");
        throw ae;
    }
}

void check_connection(int node1, int node2) {
    if (node1 == node2) {
        args_exception ae("Error: both terminals of resistor connect to node " + to_str(node1));
        throw ae;
    }
}

// n is expected args number
void check_args(vector<string> raw_cmd, int n) {
    check_args_few(raw_cmd, n);
    check_args_more(raw_cmd, n);
}

void check_args_few(vector<string> raw_cmd, int n) {
    if ((int) (raw_cmd.size()) < n + 1) {
        args_exception ae("Error: too few arguments");
        throw ae;
    }
}

void check_args_more(vector<string> raw_cmd, int n) {
    if ((int) (raw_cmd.size()) > n + 1) {
        args_exception ae("Error: too many arguments");
        throw ae;
    }
}

args_exception::args_exception(const string &s) {
    args_exception::msg = s;
}

args_exception::args_exception(args_exception &ae) {
    this->msg = ae.msg;
}

//wheels:
string to_str(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

//with decimal places specified
string to_str(double d, int n) {
    stringstream ss;
    ss << setprecision(n) << fixed << d;
    return ss.str();
}

vector<string> split(const string &s, char sep) {
    vector<string> elems;
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, sep)) {
        if (item != "") {
            elems.push_back(item);
        }
    }
    return elems;
}