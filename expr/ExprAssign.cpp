#include "ExprAssign.hpp"

void ExprAssign::initialize(Expr* l, Expr* r, ExprOP2::op t) {
    this->left        = l;
    this->right       = r;
    this->opt         = t;
    this->is_unary    = false;
    this->is_negative = false;
    this->is_postfix  = false;
    this->expr_value  = 0;
}

// Constructor for normal assignment
ExprAssign::ExprAssign(Expr *l, Expr *r) {
    this->initialize(l, r);
}

// Constructor for qualified assignement (+=, *=...)
ExprAssign::ExprAssign(ExprOP2::op t, Expr *l, Expr *r) {
    this->initialize(l, r, t);
}

// Constructor for unary assignment (++, -- etc...)
ExprAssign::ExprAssign(Expr *l, bool postfix, bool negative) {
    this->initialize(l);
    this->is_unary = true;
    this->is_postfix = postfix;
    this->is_negative = negative;
}

void ExprAssign::accept(VisitorNode &v) {
    v.visit(this);
}

Expr* ExprAssign::getLeft() {
    return this->left;
}

Expr* ExprAssign::getRight() {
    return this->right;
}

void ExprAssign::setRight(Expr* e) {
    this->right = e;
}

ExprOP2::op ExprAssign::getOperator() {
	return this->opt;
}

void ExprAssign::setOperator(ExprOP2::op o) {
	this->opt = o;
}

bool ExprAssign::isUnary() {
    return this->is_unary;
}

bool ExprAssign::isNegative() {
    return this->is_negative;
}

bool ExprAssign::isPostfix() {
    return this->is_postfix;
}

Expr* ExprAssign::getExprValue() {
    return this->expr_value;
}

void ExprAssign::setExprValue(Expr* ev) {
    this->expr_value = ev;
}
