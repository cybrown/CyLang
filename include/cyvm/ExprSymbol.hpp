#ifndef __NODE_EXPR_SYMBOL__
#define __NODE_EXPR_SYMBOL__

#include <string>
#include "Expr.hpp"

/**
Node for symbol.
smbol can contains a lot of things, namespace, class, object, values, functions, methods etc...
*/
class ExprSymbol: public Expr {
protected:
    std::string name;
public:
    ExprSymbol(std::string n);
    void accept(VisitorNode &v);
    std::string getName();
    void setName(std::string n);
    bool assignable();
};

#endif
