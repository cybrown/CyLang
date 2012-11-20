#include "TypeArray.hpp"

TypeArray::TypeArray(Type *t, int length) {
    this->type = t;
    this->length = length;
}

TypeArray::TypeArray(Type *t) {
    this->type = t;
}

/**
Get the type of what the array is containing.
*/
Type* TypeArray::getType() {
    return this->type;
}

bool TypeArray::isArray() {
    return true;
}

bool TypeArray::equals(Type *t) {
    // TODO Verify if both arrays are the same !
    //TypeArray *b;
    // Verify type is an array
    if (!t->isArray())
        return false;
    //b = static_cast<TypeArray*>(t);
    // Verify types are the same
    /*
    if (!this->type->equals(t))
        return false;*/
    return true;
}

void TypeArray::acceptVisitor(class VisitorType &v) {
    v.visit(this);
}

bool TypeArray::canReceive(Type* t) {
    return this->equals(t);
}

int TypeArray::getLength() {
    return this->length;
}

std::string TypeArray::mangle() {
    return "a" + this->type->mangle();
}
