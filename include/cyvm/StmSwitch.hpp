#ifndef __NODE_STM_SWITCH__
#define __NODE_STM_SWITCH__

#include "Stm.hpp"
#include "Expr.hpp"
#include <map>

class StmSwitch: public Stm {
protected:
    Expr *condition;
    std::map<long, Stm*>* cases;
    Stm* def;
    int def_pos;
public:
    StmSwitch();
    void setCondition(Expr* c);
    Expr* getCondition();
    std::map<long, Stm*>* getCases();
    void addCase(long index, Stm* s);
    void accept(VisitorNode &v);
    Stm* getDefault();
    void setDefault(Stm* s);
    int getDefaultPosition();
};

#endif
