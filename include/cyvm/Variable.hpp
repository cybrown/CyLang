#ifndef __VARIABLE__
#define __VARIABLE__

#include "Type.hpp"
#include <string>

class Variable {
protected:
    std::string name;
    Type* type;
    int scope;
    int address;
public:
    Variable();
    void setName(std::string n);
    std::string getName();
    void setType(Type* t);
    Type* getType();
    void setScope(int s);
    int getScope();
    void setAddress(int a);
    int getAddress();
};

#endif
