#ifndef __TYPE_PRIMARY__
#define __TYPE_PRIMARY__

#include "Type.hpp"

/**
Class for primary types like byte, int, double etc...
*/
class TypePrimary: public Type {
protected:
public:
    enum Basetype {
        Bool,
        Byte,
        Short,
        Int,
        Long,
        Float,
        Double,
        Void
    };
    TypePrimary(TypePrimary::Basetype t);
    TypePrimary::Basetype getType();
    bool isPrimary();
    bool equals(Type *t);
    void setType(TypePrimary::Basetype t);
    bool isBool();
    bool isByte();
    bool isShort();
    bool isInt();
    bool isLong();
    bool isFloat();
    bool isDouble();
    bool isVoid();
    void acceptVisitor(VisitorType &v);
    static TypePrimary* getBool();
    static TypePrimary* getByte();
    static TypePrimary* getShort();
    static TypePrimary* getInt();
    static TypePrimary* getLong();
    static TypePrimary* getFloat();
    static TypePrimary* getDouble();
    static TypePrimary* getVoid();
    int stackSize();
    int heapSize();
    bool canReceive(Type* t);
    std::string mangle();
protected:
    TypePrimary::Basetype base_type;
    static TypePrimary* _bool;
    static TypePrimary* _byte;
    static TypePrimary* _short;
    static TypePrimary* _int;
    static TypePrimary* _long;
    static TypePrimary* _float;
    static TypePrimary* _double;
    static TypePrimary* _void;
};

#endif
