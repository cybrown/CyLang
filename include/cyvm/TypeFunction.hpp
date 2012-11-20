#ifndef __TYPE_FUNCTION__
#define __TYPE_FUNCTION__

#include <vector>
#include "Type.hpp"

/**
Class for function types.
These are functions or methods, not callable objects (which are class with operator overload.).


*/
class TypeFunction: public Type {
protected:
    Type* type;
    class Class* cl;
    std::vector<Type*>* signature;
    void initialize();
    std::string name;
    bool is_static;
    bool is_virtual;
    bool is_overriden;
public:
    TypeFunction();
    TypeFunction(Type* t);
    bool isFunction();
    bool equals(Type *t);

    void setType(Type* t);
    Type* getType();

    void addSignature(Type* t);
    std::vector<Type*>* getSignature();
    void acceptVisitor(VisitorType &v);
    bool canReceive(Type* t);
    
    void setClass(Class* c);
    class Class* getClass();

    void setName(std::string n);
    std::string getName();

    void setStatic(bool st);
    bool isStatic();
    void setVirtual(bool vt);
    bool isVirtual();
    void setOverridden(bool _or);
    bool isOverridden();
};

#endif
