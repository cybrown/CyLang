#ifndef __VISITOR_NODE_BASIC__
#define __VISITOR_NODE_BASIC__

#include "VisitorNode.hpp"
#include "Argument.hpp"
#include "AllNodes.hpp"

/**
This visitor displays the content of the AST.
usefull for debug.
*/
class VisitorNodeBasic: public VisitorNode {
public:
    VisitorNodeBasic();
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
};

#endif
