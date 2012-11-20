#include <iostream>
#include "VisitorNodeSimplify.hpp"

using namespace std;
#pragma GCC diagnostic ignored "-Wunused-parameter"

void VisitorNodeSimplify::visit(ExprAssign *n){
    n->getLeft()->accept(*this);
    if (n->getRight())
        n->getRight()->accept(*this);
    if (n->isUnary())
    {
        ExprLiteral* el;
        if (n->getLeft()->getType()->equals(TypePrimary::getFloat()))
        {
            el = new ExprLiteral(1.0f);
        }
        else if (n->getLeft()->getType()->equals(TypePrimary::getDouble()))
        {
            el = new ExprLiteral(1.0);
        }
        else
        {
            el = new ExprLiteral(1);
        }
        el->getValue()->setType(n->getLeft()->getType());
        n->setRight(new ExprOP2(n->isNegative() ? ExprOP2::SUB : ExprOP2::ADD, n->getLeft(), el));
        n->setExprValue(n->getLeft());
    }
    else if (n->getOperator())
    {
        n->setRight(new ExprOP2(n->getOperator(), n->getLeft(), n->getRight()));
        n->setOperator(ExprOP2::NULL_OP);
    }
}

void VisitorNodeSimplify::visit(ExprArray *n){
    // STUB
}

void VisitorNodeSimplify::visit(ExprCondition *n){
    n->getCondition()->accept(*this);
    n->getOntrue()->accept(*this);
    n->getOnfalse()->accept(*this);
}

void VisitorNodeSimplify::visit(ExprLiteral *n){

}

void VisitorNodeSimplify::visit(ExprOP1 *n){
    n->getOperand()->accept(*this);
}

void VisitorNodeSimplify::visit(ExprOP2 *n){
    n->getLeft()->accept(*this);
    n->getRight()->accept(*this);
}

void VisitorNodeSimplify::visit(class ExprCall *n) {
    n->getCallee()->accept(*this);
    for (std::vector<Expr*>::iterator it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
    {
        (*it)->accept(*this);
    }
}

void VisitorNodeSimplify::visit(ExprSymbol *n){
}

void VisitorNodeSimplify::visit(class StmExpr *n) {
    this->append_return = false;
    n->getExpr()->accept(*this);
}

void VisitorNodeSimplify::visit(class StmIf *n) {
    this->append_return = false;
    n->getCondition()->accept(*this);
    n->getOntrue()->accept(*this);
    if (n->getOnfalse())
    {
        n->getOnfalse()->accept(*this);
    }
}

void VisitorNodeSimplify::visit(class StmWhile *n) {
    this->append_return = false;
    n->getCondition()->accept(*this);
    n->getBody()->accept(*this);
}

void VisitorNodeSimplify::visit(class StmDo *n) {
    this->append_return = false;
    n->getCondition()->accept(*this);
    n->getBody()->accept(*this);
}

void VisitorNodeSimplify::visit(class StmFor *n) {
    this->append_return = false;
    n->getInitial()->accept(*this);
    n->getCondition()->accept(*this);
    n->getLoop()->accept(*this);
    n->getBody()->accept(*this);
}

void VisitorNodeSimplify::visit(class StmReturn *n) {
    this->append_return = false;
    if (n->getValue())
        n->getValue()->accept(*this);
}

void VisitorNodeSimplify::visit(class StmBlock *n) {
    bool _append_return = this->append_return;
    this->append_return = false;
    std::vector<Stm*>* stm = n->getStatements();
    if (n->getStatements()->size() > 0)
    {
        for (std::vector<Stm*>::iterator it = stm->begin(); it != stm->end(); it++)
        {
            (*it)->accept(*this);
        }
    }
    if (_append_return)
    {
        stm->push_back(new StmReturn(0));
    }
}

void VisitorNodeSimplify::visit(class StmDecl *n) {
    this->append_return = false;
    if (n->getBody())
    {
        /*
        std::vector<Argument*>::iterator it;
        for (it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
        {
            // TODO OPtimize
            //(*it)->accept(*this);
        }
        */
        // Append a void return statement at end of void functions.
        // If return is present, it is ignored.
        this->append_return = true;
        n->getBody()->accept(*this);
    }
}

void VisitorNodeSimplify::visit(class StmClass *n) {
    //std::map<std::string, cy::Function*>::iterator it;
    //for (it = n->getClass()->getMethods()->begin(); it != n->getClass()->getMethods()->end(); it++)
    std::vector<cy::Function*>::iterator it;
    for (it = n->getClass()->getMethods()->begin(); it != n->getClass()->getMethods()->end(); it++)
    {
        this->append_return = true;
        //cout << "Append return to: " << it->first << endl;
        //it->second->getBody()->accept(*this);
        (*it)->getBody()->accept(*this);
    }
}

void VisitorNodeSimplify::visit(class StmNop *n) {
    this->append_return = false;
    
}

void VisitorNodeSimplify::visit(class StmBreak *n) {
    this->append_return = false;
    
}

void VisitorNodeSimplify::visit(class StmContinue *n) {
    this->append_return = false;
    
}

void VisitorNodeSimplify::visit(class StmSwitch *n) {
    this->append_return = false;
    n->getCondition()->accept(*this);
    // TODO Accept cases
}

VisitorNodeSimplify::VisitorNodeSimplify() {
    this->append_return = false;
}
