#include "StmIf.hpp"

StmIf::StmIf(Expr *c, Stm *t, Stm *f) {
    this->condition = c;
    this->ontrue = t;
    this->onfalse = f;
}

void StmIf::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* StmIf::getCondition() {
    return this->condition;
}

Stm* StmIf::getOntrue() {
    return this->ontrue;
}

Stm* StmIf::getOnfalse() {
    return this->onfalse;
}
