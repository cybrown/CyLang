#include "StmExpr.hpp"

void StmExpr::accept(VisitorNode &v) {
    v.visit(this);
}

StmExpr::StmExpr(Expr* e) {
    this->expr = e;
}

Expr* StmExpr::getExpr() {
    return this->expr;
}
