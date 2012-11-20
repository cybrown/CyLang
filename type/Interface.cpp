#include "Interface.hpp"

Interface::Interface() {
	this->id = this->next_id;
	this->next_id++;
	this->methods = new std::vector<cy::Function*>();
}

void Interface::addMethod(std::string original_name, Type* return_type, std::vector<Argument*>* args) {

}

std::vector<cy::Function*>* Interface::getMethods() {
	return this->methods;
}

Type* Interface::getMethodReturnType() {
	return TypePrimary::getVoid();
}

int Interface::getMethodOffset() {
	return 0;
}

int Interface::getId() {
	return this->id;
}

void Interface::setName(std::string n) {
	this->name = n;
}

std::string Interface::getName() {
	return this->name;
}

int Interface::next_id = 1;
