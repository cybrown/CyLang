#include "ExprOP2.hpp"
#include <iostream>

ExprOP2::ExprOP2(ExprOP2::op t, Expr *l, Expr *r) {
    this->opt = t;
    this->left = l;
    this->right = r;
}

void ExprOP2::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* ExprOP2::getLeft() {
    return this->left;
}

Expr* ExprOP2::getRight() {
    return this->right;
}

ExprOP2::op ExprOP2::getOperator() {
    return this->opt;
}
