#ifndef __TYPE_ARRAY__
#define __TYPE_ARRAY__

#include "Type.hpp"

/**
Type representing an array.
Arrays can have multiple dimensions.
*/
class TypeArray: public Type {
protected:
    Type *type;
    int length;
public:
    TypeArray(Type *t);
    TypeArray(Type *t, int length);
    int getLength();
    Type* getType();
    bool isArray();
    bool equals(Type *t);
    void acceptVisitor(VisitorType &v);
    bool canReceive(Type* t);
    std::string mangle();
};

#endif
