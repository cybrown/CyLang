#ifndef __NODE_STM_FOR__
#define __NODE_STM_FOR__

#include "Stm.hpp"
#include "Expr.hpp"

class StmFor: public Stm {
protected:
    Expr *initial;
    Expr *condition;
    Expr *loop;
    Stm *body;
public:
    StmFor(Expr* init, Expr *c, Expr* l, Stm *b);
    Expr* getInitial();
    Expr* getCondition();
    Expr* getLoop();
    Stm* getBody();
    void accept(VisitorNode &v);
};

#endif
