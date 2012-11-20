#include "Symtab.hpp"

// DEBUG
#include <iostream>
using namespace std;

Symtab::Symtab() {
    this->scopes.push_back(new std::map<std::string, Variable*>());
    this->addresses.push_back(0);
}

void Symtab::add(std::string name, Type* t) {
    Variable* v = new Variable();
    //cout << "Symtab::add " << name << " : " << v << endl;
    int tmp_size = this->addresses.back() + t->stackSize();
    v->setName(name);
    v->setType(t);
    v->setScope(this->scopes.size() - 1);
    v->setAddress(this->addresses.back());
    this->addresses.pop_back();
    this->addresses.push_back(tmp_size);
    this->scopes.back()->insert(std::make_pair(name, v));
}

void Symtab::addInParent(std::string name, Type* t) {
    // Memorize last scope
    std::map<std::string, Variable*>* tmp = this->scopes.back();
    // Memorize last address
    int tmpi = this->addresses.back();
    // Remove last scope, current scope is the parent
    this->popScope();
    
    // Normal process
    this->add(name, t);
    
    // Restore last scope
    this->pushScope(tmp);
    // Pop address 0
    this->addresses.pop_back();
    // Put old last address
    this->addresses.push_back(tmpi);
}

Variable* Symtab::get(std::string name) {
    Variable* res = 0;
    std::vector<std::map<std::string, Variable*>* >::reverse_iterator it;

    for (it = this->scopes.rbegin(); !res && it != this->scopes.rend(); it++)
    {
        res = (*(*it))[name];
    }
    return res;
}

void Symtab::pushScope() {
    this->scopes.push_back(new std::map<std::string, Variable*>());
    this->addresses.push_back(0);
}

void Symtab::pushScope(std::map<std::string, Variable*>* s) {
    this->scopes.push_back(s);
    this->addresses.push_back(0);
}

void Symtab::popScope() {
    this->scopes.pop_back();
    this->addresses.pop_back();
}

int Symtab::stackSize() {
    return this->addresses.back();
}

std::map<std::string, Variable*>* Symtab::getScope() {
    return this->scopes.back();
}

void Symtab::dump() {
    int idx = 0;
    std::vector<std::map<std::string, Variable*>* >::iterator it;
    std::map<std::string, Variable*>::iterator it2;

    for (it = this->scopes.begin(); it != this->scopes.end(); it++)
    {
        cout << "Depth: " << idx << endl;
        for (it2 = (*it)->begin(); it2 != (*it)->end(); it2++)
        {
            cout << "    " << (*it2).first << " : " << (*it2).second << endl;
        }
        idx++;
    }
}
