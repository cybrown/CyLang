#ifndef __NODE_EXPR_OP1__
#define __NODE_EXPR_OP1__

#include "Expr.hpp"

/**
Node for unary operators.
*/
class ExprOP1: public Expr {
protected:
    Expr *operand;
public:
    enum op {
        NULL_OP1,
        NEG,
        PRE_INC,
        PRE_DEC,
        POS,
        B_NOT,
        NOT,
        POST_INC,
        POST_DEC
    };

    ExprOP1(ExprOP1::op t, Expr* opd);
    void accept(VisitorNode &v);
    Expr* getOperand();
protected:
    ExprOP1::op opt;
public:
    ExprOP1::op getOperator();
    bool isPostfix();
};

#endif
