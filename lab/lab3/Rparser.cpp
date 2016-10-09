//
// Created by CharlieHu on 2016-10-08.
//

#include "Rparser.h"

Rparser::Rparser() {}

Rparser::~Rparser() {
    cout << "Rparser des called!" << endl;
    for (vector<Resistor *>::iterator it = resistorArray.begin(); it != resistorArray.end(); it++) {
        delete *it;
    }
    for (vector<Node *>::iterator it = nodeArray.begin(); it != nodeArray.end(); it++) {
        delete *it;
    }
//    delete &resistorArray;
//    delete &nodeArray;
}

string Rparser::parse(const string &s) {
    vector<string> raw_cmd = split(s, ' ');
    string cmd = raw_cmd[0];

    try {
        if (cmd == "maxVal") {
            check_args_few(raw_cmd, 2);

            int maxN = stoint(raw_cmd[1]);
            check_max_val(maxN);
            int maxR = stoint(raw_cmd[2]);
            check_max_val(maxR);

            Node::maxNodeNumber = maxN;
            Resistor::maxResistors = maxR;

            if (maxN < nodeArray.size())
                for (int j = maxN; j < nodeArray.size(); ++j) {
                    delete nodeArray[j];
                    nodeArray.erase(nodeArray.begin() + j);
                }
            for (int i = 0; i < (maxN < nodeArray.size() ? (unsigned long) maxN : nodeArray.size()); ++i) {
                nodeArray[i]->reset();
            }
            for (vector<Resistor *>::iterator it = resistorArray.begin(); it != resistorArray.end(); it++)
                delete *it;
            resistorArray.clear();

            nodeArray.reserve((unsigned long) maxN);
            resistorArray.reserve((unsigned long) maxR);

            return "New network: max node number is " + to_str(maxN) + "; max resistors is " + to_str(maxR);

        } else if (cmd == "insertR") {
            check_args_few(raw_cmd, 4);

            string name = raw_cmd[1];
            check_name(name);

            double resistance = stodouble(raw_cmd[2]);
            check_resistance(resistance);

            int nodeid1 = stoint(raw_cmd[3]);
            int nodeid2 = stoint(raw_cmd[4]);

            check_node(nodeid1);
            check_node(nodeid2);
            check_connection(nodeid1, nodeid2);

            check_args_more(raw_cmd, 4);

            insert_resistor(name, resistance, nodeid1, nodeid2);
            return "Inserted: resistor " + name + " " + to_str(resistance, 2) + " Ohms " + raw_cmd[3] + " -> " +
                   raw_cmd[4];

        } else if (cmd == "modifyR") {

            string name = raw_cmd[1];
            check_name(name);

            double resistance = stodouble(raw_cmd[2]);
            check_resistance(resistance);
            check_args(raw_cmd, 2);

            double oldResistance = modify_resistor(name, resistance);
            return "Modified: resistor " + name + " from " + to_str(oldResistance, 2) + " Ohms to " +
                   to_str(resistance, 2) +
                   " Ohms";
        } else if (cmd == "printR") {
            check_args_few(raw_cmd, 1);
            if (raw_cmd[1] == "all") {
                check_args_more(raw_cmd, 1);
                stringstream ss;
                ss << "Print:";
                for (int i = 0; i < resistorArray.size(); i++) {
                    ss << endl << *resistorArray[i];
                }
                return ss.str();
            } else {
                string name = raw_cmd[1];
                check_args_more(raw_cmd, 1);
                return "Print:\n" + resistor_info(name);
            }
        } else if (cmd == "printNode") {
            check_args_few(raw_cmd, 1);
            if (raw_cmd[1] == "all") {
                check_args_more(raw_cmd, 1);
                stringstream ss;
                ss << "Print:";
                for (int i = 0; i < nodeArray.size(); i++) {
                    ss << node_info(nodeArray[i]->getNodeIndex());
                }
                return ss.str();
            } else {
                int nodeid = stoint(raw_cmd[1]);
                check_node(nodeid);
                check_args(raw_cmd, 1);
                return "Print:" + node_info(nodeid);
            }
        } else if (cmd == "deleteR") {
            check_args_few(raw_cmd, 1);
            if (raw_cmd[1] == "all") {
                check_args_more(raw_cmd, 1);
                resistorArray.clear();
                nodeArray.clear();
                return "Deleted: all resistors";
            } else {
                string name = raw_cmd[1];
                check_args_more(raw_cmd, 1);
                delete_resistor(name);
                return "Deleted: resistor " + name;
            }
        } else {
            return "Error: invalid command";
        }
    } catch (args_exception &e) {
        return e.msg;
    }
}

void check_resistance(double resistance) {
    if (resistance < 0) {
        args_exception ae("Error: negative resistance");
        throw ae;
    }
}

void Rparser::insert_resistor(string &name, double resistance, int node1, int node2) {
    if (resistorArray.size() >= Resistor::maxResistors) {
        args_exception ae("Error: resistor array is full");
        throw ae;
    }
    try {
        find_resistor_by_name(name);
    } catch (args_exception &e) {
        // if not found
        Node *node_1 = find_node_by_index(node1);
        Node *node_2 = find_node_by_index(node2);
        if (node_1->canAddResistor() && node_2->canAddResistor()) {
            int endpoints[2] = {node1, node2};
            Resistor *resistor = new Resistor(name, resistance, endpoints);
            node_1->addResistor(resistor->getRIndex());
            node_2->addResistor(resistor->getRIndex());
            resistorArray.push_back(resistor);
            if (!node_array_contains(node_1->getNodeIndex()))
                nodeArray.push_back(node_1);
            if (!node_array_contains(node_2->getNodeIndex()))
                nodeArray.push_back(node_2);
            return; // exit early
        } else {
            if (node_1->isEmpty())
                delete node_1;
            if (node_2->isEmpty())
                delete node_2;
            args_exception ae("Error: node is full");
            throw ae;
        }
    }
    //if found
    args_exception ae("Error: Resistor " + name + " already exists");
    throw ae;
}

double Rparser::modify_resistor(string &name, double resistance) {
    Resistor *r = find_resistor_by_name(name);
    double oldResistance = r->getResistance();
    r->setResistance(resistance);
    return oldResistance;
}

void Rparser::delete_resistor(string &name) {
    const int *endpoints;
    // delete Resistor in resistorArray
    for (int i = 0; i < resistorArray.size(); i++) {
        if (resistorArray[i]->getName() == name) {
            endpoints = resistorArray[i]->getEndpointNodeIDs();
            const int rIndex = resistorArray[i]->getRIndex();
            resistorArray.erase(resistorArray.begin() + i);
            delete_attached_resistor(rIndex, endpoints[0]);
            delete_attached_resistor(rIndex, endpoints[1]);
            break;
        }
    }

}

void Rparser::delete_attached_resistor(int rIndex, int nodeIndex) {
    Node *node = find_node_by_index(nodeIndex);
    for (int i = 0; i < node->getNumRes(); i++) {
        if (node->getResIDArray()[i] == rIndex) {
            node->getResIDArray()[i] = -1;// -1 means null
            node->setNumRes(node->getNumRes() - 1);
            if (node->getNumRes() == 0)
                delete node;
        }
    }
}

string Rparser::resistor_info(string &name) {
    Resistor *resistor = find_resistor_by_name(name);
    stringstream ss;
    ss << *resistor;
    return ss.str();
}

string Rparser::node_info(int nodeIndex) {
    Node *node = find_node_by_index(nodeIndex);
    stringstream ss;
    ss << "\nConnections at node " << node->getNodeIndex() << ": " << node->getNumRes() << " resistor(s)";
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++) {
        try {
            Resistor r = *find_resistor_by_index(node->getResIDArray()[i]);
            ss << "\n" << r;
        } catch (args_exception) {
            if (node->getResIDArray()[i] != -1)
                cout << "Something unexpected happened!";
        }
    }
    return ss.str();
}

Resistor *Rparser::find_resistor_by_index(int rIndex) {
    for (int i = 0; i < resistorArray.size(); i++)
        if (resistorArray[i]->getRIndex() == rIndex)
            return resistorArray[i];
    args_exception ae("Error: Resistor #" + to_str(rIndex) + " not found");
    throw ae;
}

bool Rparser::node_array_contains(int nodeIndex) {
    for (int i = 0; i < nodeArray.size(); i++)
        if (nodeArray[i]->getNodeIndex() == nodeIndex)
            return true;
    return false;
}

Node *Rparser::find_node_by_index(int nodeIndex) {
    for (int i = 0; i < nodeArray.size(); i++)
        if (nodeArray[i]->getNodeIndex() == nodeIndex)
            return nodeArray[i];
    return new Node(nodeIndex);
}

Resistor *Rparser::find_resistor_by_name(string &name) {
    for (int i = 0; i < resistorArray.size(); i++) {
        if (resistorArray[i]->getName() == name) {
            return resistorArray[i];
        }
    }
    args_exception ae("Error: Resistor " + name + " not found");
    throw ae;
}

void check_node(int node) {
    if (node > Node::maxNodeNumber || node < MIN_NODE_NUMBER) {
        args_exception ae(
                "Error: node " + to_str(node) + " is out of permitted range " + to_str(MIN_NODE_NUMBER) + "-" +
                to_str(Node::maxNodeNumber));
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
    if (raw_cmd.size() < n + 1) {
        args_exception ae("Error: too few arguments");
        throw ae;
    }
}

void check_args_more(vector<string> raw_cmd, int n) {
    if (raw_cmd.size() > n + 1) {
        args_exception ae("Error: too many arguments");
        throw ae;
    }
}

void check_max_val(int maxVal) {
    if (maxVal <= 0) {
        args_exception ae("Error: maxVal arguments must be greater than 0");
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

string to_str(double d) {
    stringstream ss;
    ss << d;
    return ss.str();
}

//with decimal places specified
string to_str(double d, int n) {
    stringstream ss;
    ss << setprecision(n) << fixed << d;
    return ss.str();
}

int ctoint(char c) {
    return c - 48;
}

int stoint(const string &s) {
    string int_val = "1234567890";
    int result = 0;
    for (int i = 0; i < s.length(); i++) {
        if (int_val.find(s[i]) == string::npos) {
            args_exception ae("Error: invalid argument");
            throw ae;
        } else {
            result *= 10;
            result += ctoint(s[i]);
        }
    }
    return result;
}

double stodouble(const string &s) {
    string double_val = "1234567890";
    double result = 0;
    double deci = 10;
    bool is_deci = false;
    args_exception ae("Error: invalid argument");
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.') {
            // there should be at most one '.'
            if (is_deci) {
                throw ae;
            } else {
                is_deci = true;
            }
        } else if (double_val.find(s[i]) == string::npos) {
            throw ae;
        } else {
            if (is_deci) {
                result += ctoint(s[i]) / deci;
                deci *= 10;
            } else {
                result *= 10;
                result += ctoint(s[i]);
            }
        }
    }
    return result;
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


