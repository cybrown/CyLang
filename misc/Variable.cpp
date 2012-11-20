#include "Variable.hpp"

//DEBUG
#include <iostream>
using namespace std;

Variable::Variable() {
    this->scope = 0;
    this->type = 0;
    //cout << "Variable::Variable " << this << endl;
}

void Variable::setName(std::string n) {
    this->name = n;
}

std::string Variable::getName() {
    return this->name;
}

void Variable::setType(Type* t) {
	//cout << "Variable::setType " << this << ":" << t << endl;
    this->type = t;
}

Type* Variable::getType() {
    return this->type;
}

void Variable::setScope(int s) {
        this->scope = s;
}

int Variable::getScope() {
    return this->scope;
}

void Variable::setAddress(int a) {
    this->address = a;
}

int Variable::getAddress() {
    return this->address;
}
