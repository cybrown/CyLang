#include "ExprCondition.hpp"

ExprCondition::ExprCondition(Expr *c, Expr *t, Expr *f) {
    this->condition = c;
    this->ontrue = t;
    this->onfalse = f;
}

void ExprCondition::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* ExprCondition::getCondition() {
    return this->condition;
}

Expr* ExprCondition::getOntrue() {
    return this->ontrue;
}

Expr* ExprCondition::getOnfalse() {
    return this->onfalse;
}
