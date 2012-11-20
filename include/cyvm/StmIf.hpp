#ifndef __NODE_STM_IF__
#define __NODE_STM_IF__

#include "Stm.hpp"
#include "Expr.hpp"

class StmIf: public Stm {
protected:
    Expr *condition;
    Stm *ontrue;
    Stm *onfalse;
public:
    StmIf(Expr *c, Stm *t, Stm *f);
    Expr* getCondition();
    Stm* getOntrue();
    Stm* getOnfalse();
    void accept(VisitorNode &v);
};

#endif
