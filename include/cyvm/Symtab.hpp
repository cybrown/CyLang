#ifndef __SYMTAB__
#define __SYMTAB__

#include <string>
#include <map>
#include <vector>
#include "Type.hpp"
#include "Variable.hpp"

/**
add (name, type)
find(name)


?? scopes push/pop

*/

class Symtab {
protected:
    std::vector<std::map<std::string, Variable*>* > scopes;
    std::vector<int> addresses;
public:
    Symtab();
    void add(std::string name, Type* t);
    void addInParent(std::string name, Type* t);
    Variable* get(std::string name);
    void pushScope();
    void pushScope(std::map<std::string, Variable*>* s);
    void popScope();
    std::map<std::string, Variable*>* getScope();
    int stackSize();
    void dump();
};

#endif
