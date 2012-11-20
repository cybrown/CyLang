#include "VisitorNodeBasic.hpp"

void VisitorNodeBasic::visit(ExprAssign *n){
    n->getLeft()->accept(*this);
    n->getRight()->accept(*this);
}

void VisitorNodeBasic::visit(ExprCondition *n){
    n->getCondition()->accept(*this);
    n->getOntrue()->accept(*this);
    n->getOnfalse()->accept(*this);
}

void VisitorNodeBasic::visit(ExprLiteral *n){
    // ExprLiteral does not have other nodes.
}

void VisitorNodeBasic::visit(ExprOP1 *n){
    n->getOperand()->accept(*this);
}

void VisitorNodeBasic::visit(ExprOP2 *n){
    n->getLeft()->accept(*this);
    n->getRight()->accept(*this);
}

void VisitorNodeBasic::visit(ExprSymbol *n){
    // ExprSymbol does not have other nodes.
}

void VisitorNodeBasic::visit(class StmExpr *n) {
    n->getExpr()->accept(*this);
}

void VisitorNodeBasic::visit(class StmIf *n) {
    n->getCondition()->accept(*this);
    n->getOntrue()->accept(*this);
    n->getOnfalse()->accept(*this);
}

void VisitorNodeBasic::visit(class StmWhile *n) {
    n->getCondition()->accept(*this);
    n->getBody()->accept(*this);
}

void VisitorNodeBasic::visit(class StmDo *n) {
    n->getCondition()->accept(*this);
    n->getBody()->accept(*this);
}

void VisitorNodeBasic::visit(class StmFor *n) {
    n->getInitial()->accept(*this);
    n->getCondition()->accept(*this);
    n->getLoop()->accept(*this);
    n->getBody()->accept(*this);
}

void VisitorNodeBasic::visit(class StmReturn *n) {
    if (n->getValue())
    {
        n->getValue()->accept(*this);
    }
}

void VisitorNodeBasic::visit(class StmBlock *n) {
    std::vector<Stm*> stm = n->getStatements();
    if (!n->getStatements().empty())
    {
        for (std::vector<Stm*>::iterator it = stm.begin(); it != stm.end(); it++)
        {
            (*it)->accept(*this);
        }
    }
}

void VisitorNodeBasic::visit(class StmDecl *n) {
    if (n->getBody())
    {
        std::vector<StmDecl*>::iterator it;
        for (it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
        {
            (*it)->accept(*this);
        }
        n->getBody()->accept(*this);
    }
}

void VisitorNodeBasic::visit(class ExprCall *n) {
    n->getCallee()->accept(*this);
    for (std::vector<Expr*>::iterator it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
    {
        (*it)->accept(*this);
    }
    n->setType(n->getCallee()->getType());
}

void VisitorNodeBasic::visit(class StmNop *n) {
    // StmNop does not have other nodes.
}


VisitorNodeBasic::VisitorNodeBasic() {

}
