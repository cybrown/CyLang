#ifndef __NODE_STM_RETURN__
#define __NODE_STM_RETURN__

#include "Stm.hpp"
#include "Expr.hpp"

class StmReturn: public Stm {
protected:
    Expr* value;
public:
    void accept(VisitorNode &v);
    void setValue(Expr* v);
    Expr* getValue();
    StmReturn(Expr* v);
};

#endif
