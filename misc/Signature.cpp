#include "Signature.hpp"

using namespace std;

Signature::Signature() {
	this->types = new vector<Type*>();
}

std::string Signature::getMangledName() {
	return this->mangled_name;
}

void Signature::setMangledName(std::string n) {
	this->mangled_name = n;
}

std::vector<Type*>* Signature::getTypes() {
	return this->types;
}

void Signature::addType(Type* t) {
	this->types->push_back(t);
}
