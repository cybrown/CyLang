#ifndef __NODE_STM_DO__
#define __NODE_STM_DO__

#include "Stm.hpp"
#include "Expr.hpp"

class StmDo: public Stm {
protected:
    Expr *condition;
    Stm *body;
public:
    StmDo(Expr *c, Stm *b);
    Expr* getCondition();
    Stm* getBody();
    void accept(VisitorNode &v);
};

#endif
