#include "Argument.hpp"

Argument::Argument() {

}

Argument::Argument(Type* t, std::string n) {
	this->setType(t);
	this->setName(n);
}

std::string Argument::getName() {
	return this->name;
}

void Argument::setName(std::string n) {
	this->name = n;
}

Type* Argument::getType() {
	return this->type;
}

void Argument::setType(Type* t) {
	this->type = t;
}

