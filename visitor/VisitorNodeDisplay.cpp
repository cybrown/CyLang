#include <iostream>
#include "VisitorNodeDisplay.hpp"
#include "TypePrimary.hpp"

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-parameter"

void VisitorNodeDisplay::visit(ExprAssign *n){
    this->showTabs();
    cout << "Assignement (" << type2str(n->getType()) << ")" << endl;
    this->tabInc();
    n->getLeft()->accept(*this);
    if (n->getRight())
        n->getRight()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(ExprArray *n){
    this->showTabs();
    cout << "Array of " << n->getValues()->size() << " (" << type2str(n->getContentType()) << ")" << endl;
    std::vector<Expr*>::iterator it;
    this->tabInc();
    for (it = n->getValues()->begin(); it != n->getValues()->end(); it++)
    {
        (*it)->accept(*this);
    }
    this->tabDec();
}

void VisitorNodeDisplay::visit(ExprCondition *n){
    this->showTabs();
    cout << "Condition (" << type2str(n->getType()) << ")" << endl;
    this->tabInc();
    n->getCondition()->accept(*this);
    n->getOntrue()->accept(*this);
    n->getOnfalse()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(ExprLiteral *n){
    this->showTabs();
    if (n->getType()->isPrimary())
    {
        TypePrimary* t = static_cast<TypePrimary*>(n->getType());
        cout << type2str(n->getType()) << ": ";
        if (t->isBool())
            cout << (n->getBool() ? "true" : "false");
        else if (t->isByte())
            cout << n->getByte();
        else if (t->isShort())
            cout << n->getShort();
        else if (t->isInt())
            cout << n->getInt();
        else if (t->isLong())
            cout << n->getLong();
        else if (t->isFloat())
            cout << n->getFloat();
        else if (t->isDouble())
            cout << n->getDouble();
    }
    cout << endl;
}

void VisitorNodeDisplay::visit(ExprOP1 *n){
    this->showTabs();
    cout << "Unary (" << type2str(n->getType()) << ")" << endl;
    this->tabInc();
    n->getOperand()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(ExprOP2 *n){
    this->showTabs();
    cout << "Binary ";
    switch(n->getOperator())
    {
        case ExprOP2::NULL_OP:
            cout << "0";
            break;
        case ExprOP2::ADD:
            cout << "+";
            break;
        case ExprOP2::SUB:
            cout << "-";
            break;
        case ExprOP2::MUL:
            cout << "*";
            break;
        case ExprOP2::DIV:
            cout << "/";
            break;
        case ExprOP2::MOD:
            cout << "%";
            break;
        case ExprOP2::AND:
            cout << "&&";
            break;
        case ExprOP2::OR:
            cout << "||";
            break;
        case ExprOP2::ARRAY:
            cout << "[]";
            break;
        case ExprOP2::DOT:
            cout << ".";
            break;
        case ExprOP2::LT:
            cout << "<";
            break;
        case ExprOP2::LTE:
            cout << "<=";
            break;
        case ExprOP2::GT:
            cout << ">";
            break;
        case ExprOP2::GTE:
            cout << ">=";
            break;
        case ExprOP2::EQ:
            cout << "==";
            break;
        case ExprOP2::NEQ:
            cout << "!=";
            break;
        case ExprOP2::B_AND:
            cout << "&";
            break;
        case ExprOP2::B_XOR:
            cout << "^";
            break;
        case ExprOP2::B_OR:
            cout << "|";
            break;
        case ExprOP2::SHL:
            cout << "<<";
            break;
        case ExprOP2::SHR:
            cout << ">>";
            break;
        case ExprOP2::ASHR:
            cout << ">>>";
            break;
    }
    cout << " (" << type2str(n->getType()) << ")" << endl;
    this->tabInc();
    n->getLeft()->accept(*this);
    n->getRight()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(ExprSymbol *n){
    this->showTabs();
    cout << "Symbol " << n->getName() << " (" << type2str(n->getType()) << ")" << endl;
}

void VisitorNodeDisplay::visit(class StmExpr *n) {
    this->showTabs();
    cout << "EXPR" << endl;
    this->tabInc();
    n->getExpr()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmIf *n) {
    this->showTabs();
    cout << "IF" << endl;
    this->tabInc();
    n->getCondition()->accept(*this);
    n->getOntrue()->accept(*this);
    if (n->getOnfalse())
        n->getOnfalse()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmWhile *n) {
    this->showTabs();
    cout << "WHILE" << endl;
    this->tabInc();
    n->getCondition()->accept(*this);
    n->getBody()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmDo *n) {
    this->showTabs();
    cout << "DO" << endl;
    this->tabInc();
    n->getCondition()->accept(*this);
    n->getBody()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmFor *n) {
    this->showTabs();
    cout << "FOR" << endl;
    this->tabInc();
    n->getInitial()->accept(*this);
    n->getCondition()->accept(*this);
    n->getLoop()->accept(*this);
    n->getBody()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmReturn *n) {
    this->showTabs();
    cout << "RETURN" << endl;
    this->tabInc();
    if (n->getValue())
        n->getValue()->accept(*this);
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmBlock *n) {
    std::vector<Stm*>* stm = n->getStatements();
    this->showTabs();
    cout << "BLOCK" << endl;
    this->tabInc();
    if (n->getStatements()->size() > 0)
    {
        for (std::vector<Stm*>::iterator it = stm->begin(); it != stm->end(); it++)
        {
            (*it)->accept(*this);
        }
    }
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmDecl *n) {
    this->showTabs();
    cout << "DECL " << n->getName() << " as "<< this->type2str(n->getType()) << endl;
    this->tabInc();
    if (n->getInitial())
    {
        this->showTabs();
        cout << "INITIAL" << endl;
        n->getInitial()->accept(*this);
    }
    if (n->getBody())
    {
        n->getBody()->accept(*this);
    }
    this->tabDec();
}

void VisitorNodeDisplay::visit(class ExprCall *n) {
    this->showTabs();
    cout << "CALL " << this->type2str(n->getType()) << endl;
    this->tabInc();
    this->showTabs(); cout << "CALLEE" << endl;
    n->getCallee()->accept(*this);
    if (n->getArgs())
    {
        this->showTabs(); cout << "ARGUMENTS" << endl;
        for (std::vector<Expr*>::iterator it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
        {
            (*it)->accept(*this);
        }
    }
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmSwitch *n) {
    this->showTabs();
    cout << "SWITCH" << endl;
    this->tabInc();
    n->getCondition()->accept(*this);
    if (n->getDefault())
    {
        this->showTabs(); cout << "default" << endl;
        n->getDefault()->accept(*this);
    }
    std::map<long, Stm*>* c;
    c = n->getCases();
    std::map<long, Stm*>::iterator it;
    for (it = c->begin(); it != c->end(); ++it)
    {
        this->showTabs(); cout << (*it).first << endl;
        (*it).second->accept(*this);
    }
    this->tabDec();
}

void VisitorNodeDisplay::visit(class StmNop *n) {
    this->showTabs();
    cout << "NOP" << endl;
}

void VisitorNodeDisplay::visit(class StmBreak *n) {
    this->showTabs();
    cout << "BREAK" << endl;
}

void VisitorNodeDisplay::visit(class StmContinue *n) {
    this->showTabs();
    cout << "CONTINUE" << endl;
}

void VisitorNodeDisplay::visit(class ExprObject *n) {
    this->showTabs();
    cout << "OBJECT (" << type2str(n->getType()) << ")" << endl;
}

void VisitorNodeDisplay::tabInc() {
    this->tabs += 4;
}

void VisitorNodeDisplay::tabDec() {
    this->tabs -= 4;
}

void VisitorNodeDisplay::showTabs() {
    for (int i = 0; i < this->tabs; i++)
    {
        cout << " ";
    }
}

VisitorNodeDisplay::VisitorNodeDisplay() {
    this->tabs = 0;
}

const char* VisitorNodeDisplay::type2str(Type* t) {
    // TODO Use type visitor
    if (t == 0)
        return "NULL";
    if (t->isPrimary())
    {
        TypePrimary* tp = static_cast<TypePrimary*>(t);
        if (tp->isVoid())
            return "Void";
        if (tp->isBool())
            return "Bool";
        if (tp->isByte())
            return "Byte";
        if (tp->isShort())
            return "Short";
        if (tp->isInt())
            return "Int";
        if (tp->isLong())
            return "Long";
        if (tp->isFloat())
            return "Float";
        if (tp->isDouble())
            return "Double";
        return "Unknown primary type";
    }
    else if (t->isArray())
    {
        return "Array";
    }
    else if (t->isClass())
    {
        TypeClass* tc = dynamic_cast<TypeClass*>(t);
        return ("Class: " + tc->getClass()->getName()).c_str();
    }
    else if (t->isFunction())
    {
        TypeFunction* tf = dynamic_cast<TypeFunction*>(t);
        return ("Function: " + tf->getName()).c_str();
    }
    return "Unknown type";
}

void VisitorNodeDisplay::setSymtab(Symtab* s) {
    this->symt = s;
}
