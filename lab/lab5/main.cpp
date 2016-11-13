#include <iostream>
#include "TreeDB.h"

using namespace std;

int main() {

    TreeDB treeDB;

    treeDB.insert(new DBentry("a" , 11 , true));
    treeDB.insert(new DBentry("b" , 11 , true));
    treeDB.insert(new DBentry("c" , 11 , true));

    treeDB.printall();

    while (!cin.eof()) {
        cout << "> ";
        string raw_cmd;
        getline(cin, raw_cmd);

        stringstream raw_stream;
        raw_stream << raw_cmd;

        string cmd;
        raw_stream >> cmd;

        if (cmd == "insert") {
            string domain;
            unsigned int IP;
            bool active;
            string _active;
            raw_stream >> domain >> IP >> _active;
            active = (_active == "active");
            DBentry *dBentry = new DBentry(domain, IP, active);
            if(treeDB.insert(dBentry))
                cout << "Success" << endl;
        } else if (cmd == "find"){
            string domain;
            raw_stream >> domain;
            DBentry *result = treeDB.find(domain);
            if(result != NULL)
                cout << *result << endl;
        } else if( cmd == "remove"){
            string domain;
            raw_stream >> domain;
            if(treeDB.remove(domain))
                cout << "Success" << endl;
        } else if (cmd == "printall"){
            treeDB.printall();
        } else if (cmd == "printprobes"){
            string domain;
            raw_stream >> domain;
            treeDB.printProbes(domain);
        } else if(cmd == "removeall"){
            treeDB.clear();
            cout << "Success" << endl;
        } else if(cmd == "countactive"){
            treeDB.countActive();
        } else if(cmd == "updatestatus"){
            string domain;
            string _active;
            bool active;
            raw_stream >> domain;
            raw_stream >> _active;
            active = (_active == "active");
            DBentry *dBentry = treeDB.find(domain);
            if(dBentry != NULL) {
                dBentry->setActive(active);
                cout << "Success" << endl;
            }
        }
    }
    treeDB.clear();
    return 0;
}