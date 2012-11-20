#include "StmWhile.hpp"

StmWhile::StmWhile(Expr *c, Stm *b) {
    this->condition = c;
    this->body = b;
}

void StmWhile::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* StmWhile::getCondition() {
    return this->condition;
}

Stm* StmWhile::getBody() {
    return this->body;
}
