#ifndef __NODE_EXPR_CONDITION__
#define __NODE_EXPR_CONDITION__

#include "Expr.hpp"

/**
Node for ?: operator.
*/
class ExprCondition: public Expr {
protected:
    Expr *condition;
    Expr *ontrue;
    Expr *onfalse;
public:
    ExprCondition(Expr *c, Expr *t, Expr *f);
    void accept(VisitorNode &v);
    Expr* getCondition();
    Expr* getOntrue();
    Expr* getOnfalse();
};

#endif
