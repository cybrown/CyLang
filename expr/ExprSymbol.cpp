#include "ExprSymbol.hpp"
#include "TypePrimary.hpp"

using namespace std;

ExprSymbol::ExprSymbol(std::string n) {
    this->name = n;
}

void ExprSymbol::accept(VisitorNode &v) {
    v.visit(this);
}

string ExprSymbol::getName() {
    return this->name;
}

void ExprSymbol::setName(std::string n) {
	this->name = n;
}

bool ExprSymbol::assignable() {
    return true;
}
