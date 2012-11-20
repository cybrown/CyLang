#ifndef __NODE_EXPR_ASSIGN__
#define __NODE_EXPR_ASSIGN__

#include "Expr.hpp"
#include "ExprOP2.hpp"

/**
Assignement expression node.
There are no nodes for each assignement operators (+=, *=...).
Create a binary expression node with operation, then assignement node.
*/
class ExprAssign: public Expr {
protected:
    Expr *left;
    Expr *right;
    ExprOP2::op opt;
    bool is_unary;
    bool is_negative;
    bool is_postfix;
    Expr* expr_value;
    void initialize(Expr* l, Expr* r = 0, ExprOP2::op t = ExprOP2::NULL_OP);
public:
    ExprAssign(Expr *l, Expr *r);
    ExprAssign(ExprOP2::op t, Expr *l, Expr *r);
    ExprAssign(Expr *l, bool postfix, bool negative);
    void accept(VisitorNode &v);
    Expr* getLeft();
    Expr* getRight();
    void setRight(Expr* e);
    ExprOP2::op getOperator();
    void setOperator(ExprOP2::op o);
    bool isUnary();
    bool isNegative();
    bool isPostfix();
    Expr* getExprValue();
    void setExprValue(Expr* ev);
};

#endif
