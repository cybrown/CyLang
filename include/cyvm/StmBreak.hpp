#ifndef __NODE_STM_Break__
#define __NODE_STM_Break__

#include "Stm.hpp"

class StmBreak: public Stm {
public:
    void accept(VisitorNode &v);
};

#endif
