#ifndef __NODE_EXPR__
#define __NODE_EXPR__

#include <map>
#include "Node.hpp"
#include "Type.hpp"

/**
Base class for expression nodes.
Expression nodes can not be evaluated them selves, use visitors to do so.
*/
class Expr : public Node {
protected:
    Type* type;
public:
    /**
    Get type of the node.
    Look at the type system for more informations.
    */
    virtual Type* getType();
    virtual void  setType(Type* t);
    /**
    Method to accept a visitor.
    */
    virtual void accept(class VisitorNode &v)=0;
    virtual bool assignable();
    virtual std::pair<int, int>* getRef();
};

#endif
