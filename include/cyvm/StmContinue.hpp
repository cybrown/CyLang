#ifndef __NODE_STM_CONTINUE__
#define __NODE_STM_CONTINUE__

#include "Stm.hpp"

class StmContinue: public Stm {
public:
    void accept(VisitorNode &v);
};

#endif
