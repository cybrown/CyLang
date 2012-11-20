#ifndef __NODE_STM_BLOCK__
#define __NODE_STM_BLOCK__

#include "Stm.hpp"
#include <vector>

class StmBlock: public Stm {
protected:
    std::vector<Stm*>* statements;
public:
    StmBlock();
    StmBlock(Stm* n);
    void accept(VisitorNode &v);
    void addStatement(Stm* n);
    std::vector<Stm*>* getStatements();
};

#endif
