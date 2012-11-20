#include "TypePrimary.hpp"
#include <string>

TypePrimary::TypePrimary(TypePrimary::Basetype t) {
    this->setType(t);
}

/**
Return base type.
*/
TypePrimary::Basetype TypePrimary::getType() {
    return this->base_type;
}

bool TypePrimary::isPrimary() {
    return true;
}

bool TypePrimary::equals(Type *t) {
    TypePrimary *b;
    if (!t->isPrimary())
        return false;
    b = static_cast<TypePrimary*>(t);
    if (this->getType() == b->getType())
        return true;
    return false;
}

/**
Set basetype.
*/
void TypePrimary::setType(TypePrimary::Basetype t) {
    this->base_type = t;
}

/**
Return true if is a Bool.
*/
bool TypePrimary::isBool() {
    return this->base_type == TypePrimary::Bool;
}

/**
Return true if is a Byte.
*/
bool TypePrimary::isByte() {
    return this->base_type == TypePrimary::Byte;
}

/**
Return true if is a Short.
*/
bool TypePrimary::isShort() {
    return this->base_type == TypePrimary::Short;
}

/**
Return true if is a Int.
*/
bool TypePrimary::isInt() {
    return this->base_type == TypePrimary::Int;
}

/**
Return true if is a Long.
*/
bool TypePrimary::isLong() {
    return this->base_type == TypePrimary::Long;
}

/**
Return true if is a Float.
*/
bool TypePrimary::isFloat() {
    return this->base_type == TypePrimary::Float;
}

/**
Return true if is a Double.
*/
bool TypePrimary::isDouble() {
    return this->base_type == TypePrimary::Double;
}

/**
Return true if is void.
*/
bool TypePrimary::isVoid() {
    return this->base_type == TypePrimary::Void;
}

void TypePrimary::acceptVisitor(VisitorType &v) {
    v.visit(this);
}

TypePrimary* TypePrimary::getBool() {
    return _bool;
}

TypePrimary* TypePrimary::getByte() {
    return _byte;
}

TypePrimary* TypePrimary::getShort() {
    return _short;
}

TypePrimary* TypePrimary::getInt() {
    return _int;
}

TypePrimary* TypePrimary::getLong() {
    return _long;
}

TypePrimary* TypePrimary::getFloat() {
    return _float;
}

TypePrimary* TypePrimary::getDouble() {
    return _double;
}

TypePrimary* TypePrimary::getVoid() {
    return _void;
}

int TypePrimary::stackSize() {
    return heapSize();
}

int TypePrimary::heapSize() {
    switch (this->base_type)
    {
        case TypePrimary::Bool:
            return 1;
        case TypePrimary::Byte:
            return 1;
        case TypePrimary::Short:
            return 2;
        case TypePrimary::Int:
            return 4;
        case TypePrimary::Long:
            return 8;
        case TypePrimary::Float:
            return 4;
        case TypePrimary::Double:
            return 8;
        case TypePrimary::Void:
            return 0;
        default:
            throw "Not a base type.";
    }
}

bool TypePrimary::canReceive(Type* t) {
    return this->equals(t);
}

std::string TypePrimary::mangle() {
    switch (this->base_type)
    {
        case TypePrimary::Bool:
            return "b";
            break;
        case TypePrimary::Byte:
            return "y";
            break;
        case TypePrimary::Short:
            return "s";
            break;
        case TypePrimary::Int:
            return "i";
            break;
        case TypePrimary::Long:
            return "l";
            break;
        case TypePrimary::Float:
            return "f";
            break;
        case TypePrimary::Double:
            return "d";
            break;
        case TypePrimary::Void:
            return "v";
            break;
        default:
            return "P";
            break;
    }
}

TypePrimary* TypePrimary::_bool(new TypePrimary(TypePrimary::Bool));
TypePrimary* TypePrimary::_byte(new TypePrimary(TypePrimary::Byte));
TypePrimary* TypePrimary::_short(new TypePrimary(TypePrimary::Short));
TypePrimary* TypePrimary::_int(new TypePrimary(TypePrimary::Int));
TypePrimary* TypePrimary::_long(new TypePrimary(TypePrimary::Long));
TypePrimary* TypePrimary::_float(new TypePrimary(TypePrimary::Float));
TypePrimary* TypePrimary::_double(new TypePrimary(TypePrimary::Double));
TypePrimary* TypePrimary::_void(new TypePrimary(TypePrimary::Void));
