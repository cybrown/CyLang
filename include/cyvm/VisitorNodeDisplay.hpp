#ifndef __VISITOR_DISPLAY__
#define __VISITOR_DISPLAY__

#include "VisitorNode.hpp"
#include "AllNodes.hpp"
#include "AllTypes.hpp"
#include "Argument.hpp"

/**
This visitor displays the content of the AST.
usefull for debug.
*/
class VisitorNodeDisplay: public VisitorNode {
protected:
    int tabs;
    void tabInc();
    void tabDec();
    void showTabs();
    Symtab* symt;
public:
    VisitorNodeDisplay();
    void visit(ExprAssign *n);
    void visit(ExprArray *n);
    void visit(ExprCondition *n);
    void visit(ExprLiteral *n);
    void visit(ExprObject *n);
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
    void visit(StmDecl *n);
    void visit(StmSwitch *n);
    void visit(ExprCall *n);
    void visit(StmBreak *n);
    void visit(StmContinue *n);
    static const char* type2str(Type* t);
    void setSymtab(Symtab* s);
};

#endif
