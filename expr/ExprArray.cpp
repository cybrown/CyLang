#include "ExprArray.hpp"

void ExprArray::initialize() {
    this->values = new std::vector<Expr*>();
    this->size = 0;
    this->expr_size = 0;
}

ExprArray::ExprArray() {
    this->initialize();
}

ExprArray::ExprArray(Type* t, int num) {
    this->initialize();
    this->size = num;
    this->setContentType(t);
    this->setType(new TypeArray(t, num));
}

ExprArray::ExprArray(Type* t, Expr* num) {
    this->initialize();
    this->expr_size = num;
    this->setContentType(t);
    this->setType(new TypeArray(t));
}

ExprArray::ExprArray(char* str) {
    this->initialize();
    int i;
    char c = '@';   // Dummy character, not equal to \0
    for (i = 0; c != '\0'; i++)
    {
    	c = str[i];
    	this->addExpr(new ExprLiteral(c));
    }
}

void ExprArray::addExpr(Expr* e) {
    this->values->push_back(e);
}

void ExprArray::accept(VisitorNode &v) {
    v.visit(this);
}

Type* ExprArray::getType() {
    return this->type;
}

void ExprArray::setType(Type* t) {
    this->type = t;
}

void ExprArray::setContentType(Type* t) {
    this->contentType = t;
}

Type* ExprArray::getContentType() {
    return this->contentType;
}

std::vector<Expr*>* ExprArray::getValues() {
    return this->values;
}

int ExprArray::getSize() {
    return this->size;
}

Expr* ExprArray::getExprSize() {
    return this->expr_size;
}
