#include "StmReturn.hpp"

void StmReturn::accept(VisitorNode &v) {
    v.visit(this);
}

void StmReturn::setValue(Expr* v) {
    this->value = v;
}

Expr* StmReturn::getValue() {
    return this->value;
}

StmReturn::StmReturn(Expr* v) {
    this->setValue(v);
}
