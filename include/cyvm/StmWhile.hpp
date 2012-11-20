#ifndef __NODE_STM_WHILE__
#define __NODE_STM_WHILE__

#include "Stm.hpp"
#include "Expr.hpp"

class StmWhile: public Stm {
protected:
    Expr *condition;
    Stm *body;
public:
    StmWhile(Expr *c, Stm *b);
    Expr* getCondition();
    Stm* getBody();
    void accept(VisitorNode &v);
};

#endif
