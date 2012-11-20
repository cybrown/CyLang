#ifndef __NODE_STM__
#define __NODE_STM__

#include "Node.hpp"

class Stm: public Node {
public:
    virtual void accept(class VisitorNode &v)=0;
};

#endif
