#include "StmInterface.hpp"

StmInterface::StmInterface() {
	this->inter = 0;
}

StmInterface::StmInterface(Interface* i) {
	this->setInterface(i);
}

void StmInterface::setInterface(Interface* i) {
	this->inter = i;
}

Interface* StmInterface::getInterface() {
	return this->inter;
}

void StmInterface::accept(VisitorNode &v) {
    v.visit(this);
}
