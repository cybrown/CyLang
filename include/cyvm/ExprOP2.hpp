#ifndef __NODE_EXPR_OP2__
#define __NODE_EXPR_OP2__

#include "Expr.hpp"

/**
Node for binary operators.
For assignement operations, look at ExprAsssignement class.
*/
class ExprOP2: public Expr {
protected:
    Expr *left;
    Expr *right;
    ExprOP2();
public:
    enum op {
        NULL_OP,
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,

        AND,
        OR,

        ARRAY,
        DOT,

        LT,
        LTE,
        GT,
        GTE,
        EQ,
        NEQ,

        B_AND,
        B_XOR,
        B_OR,
        SHL,
        SHR,
        ASHR
    };

    ExprOP2(ExprOP2::op t, Expr *l, Expr *r);
    void accept(VisitorNode &v);
    Expr* getLeft();
    Expr* getRight();
protected:
    ExprOP2::op opt;
public:
    ExprOP2::op getOperator();
};

#endif
