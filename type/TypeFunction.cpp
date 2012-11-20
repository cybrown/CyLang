#include "TypeFunction.hpp"

void TypeFunction::initialize() {
    this->signature = new std::vector<Type*>();
    this->type = 0;
    this->is_static = false;
    this->is_virtual = false;
    this->cl = 0;
}

TypeFunction::TypeFunction() {
    this->initialize();
}

TypeFunction::TypeFunction(Type* t) {
    this->initialize();
    this->setType(t);
}

bool TypeFunction::isFunction() {
    return true;
}

bool TypeFunction::equals(Type* t) {
    if (!t->isFunction())
        return false;
    TypeFunction* tf = dynamic_cast<TypeFunction*>(t);
    // Compare return types
    if (!this->type->equals(tf->getType()))
        return false;
    // Compare signature size
    if (this->signature->size() != tf->getSignature()->size())
        return false;
    // Compare signatures
    std::vector<Type*>::iterator it1 = this->signature->begin();
    std::vector<Type*>::iterator it2 = tf->getSignature()->begin();
    while (it1 != this->signature->end())
    {
        if (!(*it1)->equals(*it2))
            return false;
        it1++;
        it2++;
    }
    return true;
}

void TypeFunction::setType(Type* t) {
    this->type = t;
}

Type* TypeFunction::getType() {
    return this->type;
}

void TypeFunction::addSignature(Type* t) {
    this->signature->push_back(t);
}

std::vector<Type*>* TypeFunction::getSignature() {
    return this->signature;
}

void TypeFunction::acceptVisitor(VisitorType &v) {
    v.visit(this);
}

bool TypeFunction::canReceive(Type* t) {
    return this->equals(t);
}

void TypeFunction::setClass(Class* c) {
    this->cl = c;
}

Class* TypeFunction::getClass() {
    return this->cl;
}

void TypeFunction::setName(std::string n) {
    this->name = n;
}

std::string TypeFunction::getName() {
    return this->name;
}

void TypeFunction::setStatic(bool st) {
    this->is_static = st;
    if (st) 
    {
        this->is_virtual = false;
        this->is_overriden = false;
    }
}

bool TypeFunction::isStatic() {
    return this->is_static;
}

void TypeFunction::setVirtual(bool vt) {
    this->is_virtual = vt;
    if (vt)
    {
        this->is_static = false;
        this->is_overriden = false;
    }
}

bool TypeFunction::isVirtual() {
    return this->is_virtual;
}

void TypeFunction::setOverridden(bool _or) {
    this->is_overriden = _or;
    if (_or)
    {
        this->is_static = false;
        this->is_virtual = false;
    }
}

bool TypeFunction::isOverridden() {
    return this->is_overriden;
}
