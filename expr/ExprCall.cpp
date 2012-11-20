#include "ExprCall.hpp"

ExprCall::ExprCall() {
    this->args = new std::vector<Expr*>;
}

void ExprCall::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* ExprCall::getCallee() {
    return this->callee;
}

void ExprCall::setCallee(Expr* e) {
    this->callee = e;
}

std::vector<Expr*>* ExprCall::getArgs() {
    return this->args;
}

void ExprCall::setArgs(std::vector<Expr*>* a) {
    this->args = a == 0 ? new std::vector<Expr*> : a;
}

void ExprCall::addArg(Expr* e) {
    if (this->args == 0)
    {
        this->args = new std::vector<Expr*>();
    }
    this->args->push_back(e);
}
