#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

#define MAX_NODE_NUMBER 5000
#define MIN_NODE_NUMBER 0

using namespace std;

vector<string> split(const string &s, char sep);

string parse(const string &s);

void check_resistance(double resistance);

void check_node(int node);

void check_name(string name);

void check_connection(int node1, int node2);

// there shall be only one check with good design
void check_args(vector<string> raw_cmd, int n);
//but the requirement is to check few before everything
void check_args_few(vector<string> raw_cmd, int n);
//and check more after. How absurd!
void check_args_more(vector<string> raw_cmd, int n);

string to_str(int n);

string to_str(double d);

//with decimal places specified
string to_str(double d, int n);

int stoint(string& s);

double stodouble(string &s);

class args_exception : exception {
public:
    string msg;

    args_exception(const string &s);

    args_exception(args_exception &ae);

    ~args_exception() throw() {}
};

int main() {
    string str;

    cout << "> ";
    getline(cin, str);

    while (!cin.eof()) {
        cout << parse(str) << endl;
        cout << "> ";
        getline(cin, str);
    }
    return 0;
}

string parse(const string &s) {
    vector<string> raw_cmd = split(s, ' ');
    string cmd = raw_cmd[0];

    try {
        if (cmd == "insertR") {
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

            return "Inserted: resistor " + name + " " + to_str(resistance, 2) + " Ohms " + raw_cmd[3] + " -> " +
                   raw_cmd[4];

        } else if (cmd == "modifyR") {

            string name = raw_cmd[1];
            check_name(name);

            double resistance = stodouble(raw_cmd[2]);
            check_resistance(resistance);
            check_args(raw_cmd, 2);

            return "Modified: resistor " + name + " to " + to_str(resistance, 2) + " Ohms";
        } else if (cmd == "printR") {
            check_args_few(raw_cmd, 1);
            if (raw_cmd[1] == "all") {
                return "Print: all resistors";
            } else {
                string name = raw_cmd[1];
                check_args_more(raw_cmd, 1);
                return "Print: resistor " + name;
            }
        } else if (cmd == "printNode") {
            check_args_few(raw_cmd, 1);
            if (raw_cmd[1] == "all") {
                return "Print: all nodes";
            } else {
                int nodeid = stoint(raw_cmd[1]);
                check_node(nodeid);
                check_args(raw_cmd, 1);
                return "Print: node " + to_str(nodeid);
            }
        } else if (cmd == "deleteR") {
            check_args_few(raw_cmd, 1);
            if (raw_cmd[1] == "all") {
                return "Deleted: all resistors";
            } else {
                string name = raw_cmd[1];
                check_args_more(raw_cmd, 1);
                return "Deleted: resistor " + name;
            }
        } else {
            return "Error: invalid command";
        }
    } catch (args_exception &e) {
        return e.msg;
    }
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

void check_resistance(double resistance) {
    if (resistance < 0) {
        args_exception ae("Error: negative resistance");
        throw ae;
    }
}

void check_node(int node) {
    if (node > MAX_NODE_NUMBER || node < MIN_NODE_NUMBER) {
        args_exception ae(
                "Error: " + to_str(node) + " is out of permitted range " + to_str(MIN_NODE_NUMBER) + "-" +
                to_str(MAX_NODE_NUMBER));
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

args_exception::args_exception(const string &s) {
    args_exception::msg = s;
}

args_exception::args_exception(args_exception &ae) {
    this->msg = ae.msg;
}

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

int stoint(string &s) {
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

double stodouble(string &s) {
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



