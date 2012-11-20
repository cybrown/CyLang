#ifndef __VISITOR_NODE__
#define __VISITOR_NODE__

#include "Symtab.hpp"

/**
The base Visitor class to visit an AST.
*/
class VisitorNode {
protected:
    Symtab* symt;
public:
    virtual void visit(class ExprAssign *n);
    virtual void visit(class ExprArray *n);
    virtual void visit(class ExprCall *n);
    virtual void visit(class ExprCondition *n);
    virtual void visit(class ExprLiteral *n);
    virtual void visit(class ExprOP1 *n);
    virtual void visit(class ExprOP2 *n);
    virtual void visit(class ExprSymbol *n);
    virtual void visit(class StmBlock *n);
    virtual void visit(class StmDecl *n);
    virtual void visit(class StmDo *n);
    virtual void visit(class StmExpr *n);
    virtual void visit(class StmFor *n);
    virtual void visit(class StmIf *n);
    virtual void visit(class StmNop *n);
    virtual void visit(class StmReturn *n);
    virtual void visit(class StmWhile *n);
    virtual void visit(class StmSwitch *n);
    virtual void visit(class StmBreak *n);
    virtual void visit(class StmContinue *n);
    virtual void visit(class ExprObject *n);
    virtual void visit(class StmClass *n);
    virtual void visit(class StmInterface *n);
    virtual void visit(class ExprClass *n);
    virtual void setSymtab(Symtab* s);
};

#endif
