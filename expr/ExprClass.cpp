#include "ExprClass.hpp"

ExprClass::ExprClass() {
	this->cl = 0;
}

ExprClass::ExprClass(Class* c) {
	this->setClass(c);
}

void ExprClass::accept(VisitorNode &v) {
	v.visit(this);
}

Class* ExprClass::getClass() {
	return this->cl;
}

void ExprClass::setClass(Class* c) {
	this->cl = c;
}
