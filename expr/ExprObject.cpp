#include "ExprObject.hpp"
#include "TypePrimary.hpp"

using namespace cy;

void ExprObject::initialize() {
	this->function = 0;
}

ExprObject::ExprObject() {
    this->initialize();
}

ExprObject::ExprObject(Type* t) {
    this->initialize();
    this->setType(t);
}

void ExprObject::accept(VisitorNode &v) {
    v.visit(this);
}

void ExprObject::setType(Type* t) {
    this->type = t;
}

Type* ExprObject::getType() {
    return this->type;
}

Function* ExprObject::getFunction() {
	return this->function;
}

void ExprObject::setFunction(Function* f) {
	this->function = f;
}

bool ExprObject::isMethod() {
	return this->function != 0;
}

std::string ExprObject::getName() {
	return this->name;
}

void ExprObject::setName(std::string s) {
	this->name = s;
}
