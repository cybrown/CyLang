#ifndef __NODE_EXPR_CALL__
#define __NODE_EXPR_CALL__

#include <vector>
#include "Expr.hpp"
#include "TypePrimary.hpp"

/**
Node for calls.

Must verify that callee is TypeFunction, or TypeClass with operator overload.
*/
class ExprCall: public Expr {
protected:
    Expr* callee;
    std::vector<Expr*>* args;
public:
    ExprCall();
    void accept(VisitorNode &v);
    Expr* getCallee();
    void setCallee(Expr* e);
    std::vector<Expr*>* getArgs();
    void setArgs(std::vector<Expr*>* a);
    void addArg(Expr* e);
};

#endif
