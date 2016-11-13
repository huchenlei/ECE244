//
// Created by CharlieHu on 2016-11-12.
//

#include "DBentry.h"

DBentry::DBentry() {

}

DBentry::DBentry(const string &name, unsigned int IPaddress, bool active) :
        name(name), IPaddress(IPaddress), active(active) {

}

DBentry::~DBentry() {

}

// getter setters
void DBentry::setName(string _name) {
    name = _name;
}

void DBentry::setIPaddress(unsigned int _IPaddress) {
    IPaddress = _IPaddress;
}

void DBentry::setActive(bool _active) {
    active = _active;
}

string DBentry::getName() const {
    return name;
}

unsigned int DBentry::getIPaddress() const {
    return IPaddress;
}

bool DBentry::getActive() const {
    return active;
}

ostream &operator<<(ostream &out, const DBentry &rhs) {
    out << rhs.getName() <<  " : " << rhs.getIPaddress() << " : ";
    if(rhs.getActive()){
        out << "active";
    }else{
        out << "inactive";
    }
    return out;
}

void DBentry::printInfo() const {
    cout << name <<  " : " << IPaddress << " : ";
    if(active){
        cout << "active\n";
    }else{
        cout << "inactive\n";
    }
}
