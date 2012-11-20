#include "StmClass.hpp"

StmClass::StmClass() {
	this->cl = 0;
}

StmClass::StmClass(Class* c) {
	this->setClass(c);
}

void StmClass::setClass(Class* c) {
	this->cl = c;
}

Class* StmClass::getClass() {
	return this->cl;
}

void StmClass::accept(VisitorNode &v) {
    v.visit(this);
}
