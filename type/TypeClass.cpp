#include "TypeClass.hpp"

using namespace std;

TypeClass::TypeClass(Class *c) {
    this->_static = false;
    this->type_class = c;
}

/**
Add a parameter to the template class.
*/
void TypeClass::addParameter(Type *t) {
    // TODO Verify class description for number of parameters.
    this->parameters.push_back(t);
}

bool TypeClass::isClass() {
    return true;
}

bool TypeClass::equals(Type *t) {
    TypeClass *b;
    if (!t->isClass())
        return false;
    b = static_cast<TypeClass*>(t);
    // Compare classe of each types
    //if (!this->type_class->equals(b->type_class))
    //    return false;
    // Compare length of parameter size
    if (this->parameters.size() != b->parameters.size())
        return false;
    // if there are no template parameters, skip parameters comparison and return true
    if (this->parameters.size() == 0)
        return true;
    // Iterate through template parameters and compare types
    vector<Type*>::iterator it1 = this->parameters.begin();
    vector<Type*>::iterator it2 = b->parameters.begin();
    while (it1 != this->parameters.end())
    {
        if (!(*it1)->equals(*it2))
            return false;
        it1++;
        it2++;
    }
    return true;
}

/**
Return the class description of the type.
*/
Class* TypeClass::getClass() {
    return this->type_class;
}

void TypeClass::acceptVisitor(VisitorType &v) {
    v.visit(this);
}

bool TypeClass::canReceive(Type* t) {
    return this->equals(t);
}

void TypeClass::setStatic(bool s) {
    this->_static = s;
}

bool TypeClass::isStatic() {
    return this->_static;
}

std::string TypeClass::mangle() {
    return "c" + this->type_class->getName();
}
