#ifndef __NODE_STM_NOP__
#define __NODE_STM_NOP__

#include "Stm.hpp"

class StmNop: public Stm {
public:
    void accept(VisitorNode &v);
};

#endif
