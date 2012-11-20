#include "StmDo.hpp"

StmDo::StmDo(Expr *c, Stm *b) {
    this->condition = c;
    this->body = b;
}

void StmDo::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* StmDo::getCondition() {
    return this->condition;
}

Stm* StmDo::getBody() {
    return this->body;
}
