#include "ExprOP1.hpp"

ExprOP1::ExprOP1(ExprOP1::op t, Expr* opd) {
    this->operand = opd;
    this->opt = t;
}

void ExprOP1::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* ExprOP1::getOperand() {
    return this->operand;
}

ExprOP1::op ExprOP1::getOperator() {
    return this->opt;
}

bool ExprOP1::isPostfix() {
    if ((this->opt == POST_INC) || (this->opt == POST_DEC))
    {
        return true;
    }
    return false;
}
