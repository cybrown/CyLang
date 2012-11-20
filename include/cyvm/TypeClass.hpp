#ifndef __TYPE_CLASS__
#define __TYPE_CLASS__

#include "Type.hpp"
#include "Class.hpp"
#include <vector>

/**
Class for a type containing a class.
It can handle template classes, with a list of parameters.
*/
class TypeClass: public Type {
protected:
    Class *type_class;
    std::vector<Type*> parameters;
    bool _static;
public:
    TypeClass(Class *c);
    void addParameter(Type *t);
    bool isClass();
    bool equals(Type *t);
    Class* getClass();
    void acceptVisitor(VisitorType &v);
    bool canReceive(Type* t);
    void setStatic(bool s);
    std::string mangle();
    bool isStatic();
};

#endif
