#include "StmFor.hpp"

StmFor::StmFor(Expr* init, Expr *c, Expr* l, Stm *b) {
    this->initial = init;
    this->condition = c;
    this->loop = l;
    this->body = b;
}

void StmFor::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* StmFor::getInitial() {
    return this->initial;
}

Expr* StmFor::getCondition() {
    return this->condition;
}

Expr* StmFor::getLoop() {
    return this->loop;
}

Stm* StmFor::getBody() {
    return this->body;
}
