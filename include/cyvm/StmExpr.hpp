#ifndef __NODE_STM_EXPR__
#define __NODE_STM_EXPR__

#include "Stm.hpp"
#include "Expr.hpp"

/**
Expression statement.
*/
class StmExpr: public Stm {
protected:
    Expr* expr;
public:
    StmExpr(Expr* e);
    Expr* getExpr();
    void accept(VisitorNode &v);
};

#endif
