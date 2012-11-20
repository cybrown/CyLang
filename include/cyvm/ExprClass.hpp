#ifndef __NODE_EXPR_CLASS__
#define __NODE_EXPR_CLASS__

#include <vector>
#include "Expr.hpp"
#include "Class.hpp"

/**
Node for literal classes.
*/
class ExprClass: public Expr {
protected:
    Class* cl;
public:
    ExprClass();
    ExprClass(Class* c);
    void accept(VisitorNode &v);
    Class* getClass();
    void setClass(Class* c);
};

#endif
