#ifndef __VISITOR_NODE_SIMPLIFY__
#define __VISITOR_NODE_SIMPLIFY__

#include "VisitorNode.hpp"
#include "AllNodes.hpp"
#include "Argument.hpp"

/**
This visitor displays the content of the AST.
usefull for debug.
*/
class VisitorNodeSimplify: public VisitorNode {
protected:
    bool append_return;
public:
    VisitorNodeSimplify();
    void visit(ExprAssign *n);
    void visit(ExprArray *n);
    void visit(ExprCondition *n);
    void visit(ExprLiteral *n);
    void visit(ExprOP1 *n);
    void visit(ExprOP2 *n);
    void visit(ExprSymbol *n);
    void visit(StmExpr *n);
    void visit(StmIf *n);
    void visit(StmWhile *n);
    void visit(StmDo *n);
    void visit(StmFor *n);
    void visit(StmNop *n);
    void visit(StmBlock *n);
    void visit(StmReturn *n);
    void visit(StmSwitch *n);
    void visit(StmDecl *n);
    void visit(ExprCall *n);
    void visit(StmBreak *n);
    void visit(StmContinue *n);
    void visit(StmClass *n);
};

#endif
