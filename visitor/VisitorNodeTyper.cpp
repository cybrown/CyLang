#include "VisitorNodeTyper.hpp"

// TODO DEBUG
#include <iostream>
using namespace std;

#define QUOTE(x) PREQUOTE(x)
#define PREQUOTE(x) #x

VisitorNodeTyper::VisitorNodeTyper() {
    this->cur_class = 0;
    this->look_for_mangled = false;
}

void VisitorNodeTyper::visit(ExprArray *n){
    std::vector<Expr*>::iterator it;
    for (it = n->getValues()->begin(); it != n->getValues()->end(); it++)
    {
        (*it)->accept(*this);
    }
    if (n->getExprSize())
    {
        n->getExprSize()->accept(*this);
    }
    if (!n->getSize() && !n->getExprSize())  // If node has a size not zero, type is already definied
    {
        n->setContentType((*n->getValues()->begin())->getType());
        // TODO Set type of most basic ancestor
        // TODO Exception if types are incompatible
        n->setType(new TypeArray(n->getContentType(), n->getValues()->size()));
    }
}

void VisitorNodeTyper::visit(ExprSymbol *n){
    // TODO Set flag if global or local
    if (this->cur_class)
    {
        Type* t = this->cur_class->getAttrType(n->getName());   // Get type from class
        if (!t) // If no type returned, it might be an unmangled method name
        {
            if (this->look_for_mangled)
            {
                TypeFunction* tf = new TypeFunction();
                tf->setClass(this->cur_class);
                tf->setName(n->getName());
                t = tf;
            }
            else
            {
                throw __FILE__ "(" QUOTE(__LINE__) "): Attribute " + n->getName() + " not found in class" + this->cur_class->getName() + ".";
            }
        }
        n->setType(t);
    }
    else
    {
        Variable* v = this->symt->get(n->getName());
        if (!v)     // Symbol not found
        {
            if (this->look_for_mangled)     // Look for an unmangled name
            {
                TypeFunction* tf = new TypeFunction();
                tf->setName(n->getName());
                tf->setStatic(true);
                tf->setVirtual(false);
                n->setType(tf);
            }
            else
            {
                throw __FILE__ "(" QUOTE(__LINE__) "): Variable " + n->getName() + " not found.";
            }
        }
        else
        {
            n->setType(v->getType());
        }
    }
}

void VisitorNodeTyper::visit(ExprClass *n){
    TypeClass* tc = new TypeClass(n->getClass());
    tc->setStatic(true);
    n->setType(tc);
}

void VisitorNodeTyper::visit(ExprAssign *n){
    // TODO Detect non assignable expressions
    n->getLeft()->accept(*this);
    if (n->getRight())
        n->getRight()->accept(*this);
    // TODO Check compatible types
    n->setType(n->getRight() ? n->getRight()->getType() : n->getLeft()->getType());
}

void VisitorNodeTyper::visit(ExprOP1 *n){
    n->getOperand()->accept(*this);
    // Type of unary expression is type of operand, except for NOT operator
    n->setType(n->getOperator() == ExprOP1::NOT ? TypePrimary::getBool() : n->getOperand()->getType());
}

void VisitorNodeTyper::visit(ExprOP2 *n){
    n->getLeft()->accept(*this);
    TypeClass* tc = dynamic_cast<TypeClass*>(n->getLeft()->getType());
    Class* old_cur_class = this->cur_class;
    this->cur_class = tc ? tc->getClass() : 0;
    n->getRight()->accept(*this);
    // Type of binary operator is type of operands (with promotion), except for comparison operators
    if (   n->getOperator() == ExprOP2::LT || n->getOperator() == ExprOP2::LTE
        || n->getOperator() == ExprOP2::GT || n->getOperator() == ExprOP2::GTE
        || n->getOperator() == ExprOP2::EQ || n->getOperator() == ExprOP2::NEQ
    )
    {
        n->setType(TypePrimary::getBool());
    }
    else if (n->getOperator() == ExprOP2::DOT)
    {
        if (!tc)
            throw __FILE__ "(" QUOTE(__LINE__) "): Left hand side of . operator must be an object / class.";
        n->setType(n->getRight()->getType());
    }
    else if (n->getOperator() == ExprOP2::ARRAY)
    {
        // TODO Check rhs type
        TypeArray* ta = dynamic_cast<TypeArray*>(n->getLeft()->getType());
        if (!ta)
            throw __FILE__ "(" QUOTE(__LINE__) "): Left hand side of [] operator must be an array.";
        n->setType(ta->getType());
    }
    else    // All other operators
    {
        n->setType(n->getLeft()->getType());
    }
    this->cur_class = old_cur_class;
}

void VisitorNodeTyper::visit(ExprCondition *n){
    n->getCondition()->accept(*this);
    if (!n->getCondition()->getType()->equals(TypePrimary::getBool()))
        throw __FILE__ "(" QUOTE(__LINE__) "): Condition expresion type of ternary operator must be bool.";
    n->getOntrue()->accept(*this);
    n->getOnfalse()->accept(*this);
    // Exception if ontrue and onfalse does not have the same type
    if (!n->getOntrue()->getType()->equals(n->getOnfalse()->getType()))
    {
        throw __FILE__ "(" QUOTE(__LINE__) "): Ontrue and Onfalse expressions does not have the same type.";
    }
    n->setType(n->getOntrue()->getType());
}

bool areCompatible(std::vector<Expr*>* e, std::vector<Type*>* t, bool skip_first = false) {
    std::vector<Expr*>::iterator ite;
    std::vector<Type*>::iterator itt;
    // Not compatible if size are different
    if (e->size() != (t->size() - (skip_first ? 1 : 0)))
    {
        return false;
    }
    // Testing each arguments and each types
    itt = t->begin();
    if (skip_first)
    {
        itt++;
    }
    for (ite = e->begin(); ite != e->end(); ite++, itt++)
    {
        if (!(*ite)->getType()->equals(*itt))
        {
            return false;
        }
    }
    return true;
}

void VisitorNodeTyper::visit(class ExprCall *n) {
    ExprSymbol* sym = dynamic_cast<ExprSymbol*>(n->getCallee());
    TypeFunction* tf = 0;

    // If there are arguments, pass through them to find there types
    if (n->getArgs())
    {
        for (std::vector<Expr*>::iterator it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
        {
            (*it)->accept(*this);
        }
    }

    // Set looking for mangled mode to avoid not in symbol table exception
    bool old_look_for_mangled = this->look_for_mangled;
    this->look_for_mangled = true;
    n->getCallee()->accept(*this);
    this->look_for_mangled = old_look_for_mangled;
    
    tf = dynamic_cast<TypeFunction*>(n->getCallee()->getType());

    std::vector<Signature*>* ss = 0;
    Class* cur_class = 0;

    if (!tf->getClass())
    {
        ss = this->sigs[tf->getName()];
    }
    else
    {
        std::map<std::string, std::vector<Signature*>* >* spc;
        cur_class = tf->getClass();

        while (cur_class != 0)
        {
            spc = this->sigs_per_class[cur_class];
            if (spc)
            {
                ss = (*spc)[tf->getName()];
                if (ss)
                {
                    break;
                }
            }
            cur_class = cur_class->getParent();
        }
        if (!spc)
            throw __FILE__ "(" QUOTE(__LINE__) "): No signature table for class " + tf->getClass()->getName() + ".";
    }

    // TODO optimize
    if (!ss)
        throw __FILE__ "(" QUOTE(__LINE__) "): Symbol " + tf->getName() + " not in signature tables.";

    // Select good function
    std::vector<Signature*>::iterator it;
    bool insert_this = false;
    std::vector<Type*>* choosen_sig = 0;
    for (it = ss->begin(); it != ss->end(); it++)
    {
        // Test for method
        if (areCompatible(n->getArgs(), (*it)->getTypes(), true))
        {
            if (tf->getClass())
            {
                tf = tf->getClass()->getMethodType((*it)->getMangledName());
                n->getCallee()->setType(tf);
            }
            tf->setName((*it)->getMangledName());
            if (choosen_sig)
                throw __FILE__ "(" QUOTE(__LINE__) "): Overloading ambiguity !";
            tf->setStatic(false);
            choosen_sig = (*it)->getTypes();
            // Function is non static, get left part of callee and add it on front of arg stack (this)
            insert_this = true;
        }
        // Test for function OR static method
        else if(areCompatible(n->getArgs(), (*it)->getTypes()))
        {
            if (tf->getClass())
            {
                tf = tf->getClass()->getMethodType((*it)->getMangledName());
                n->getCallee()->setType(tf);
            }
            tf->setName((*it)->getMangledName());
            if (choosen_sig)
                throw __FILE__ "(" QUOTE(__LINE__) "): Overloading ambiguity !";
            choosen_sig = (*it)->getTypes();
            tf->setStatic(true);
            if (sym)
            {
                sym->setName((*it)->getMangledName());
            }
        }
    }
    if (!choosen_sig)
        throw __FILE__ "(" QUOTE(__LINE__) "): No method " + tf->getName()+ " found.";
    if (insert_this)
    {
        ExprOP2* e2 = dynamic_cast<ExprOP2*>(n->getCallee());
        if (!e2)
            throw __FILE__ "(" QUOTE(__LINE__) "): Callee must be OP2.";
        n->getArgs()->insert(n->getArgs()->begin(), e2->getLeft());
    }

    // Set expected types to arguments (derived class to parent class)
    std::vector<Expr*>::iterator ite;
    std::vector<Type*>::iterator itt;
    itt = choosen_sig->begin();
    for (ite = n->getArgs()->begin(); ite != n->getArgs()->end(); ite++, itt++)
    {
        (*ite)->setType(*itt);
    }

    if (sym)
    {
        n->getCallee()->accept(*this);
        tf = dynamic_cast<TypeFunction*>(n->getCallee()->getType());
        if (!tf)
            throw __FILE__ "(" QUOTE(__LINE__) "): Callee value must be of type TypeFunction.";
    }
    else
    {
        tf->setType(tf->getClass()->getMethodReturnType(tf->getName()));
    }
    n->setType(tf->getType());
}

void VisitorNodeTyper::visit(class StmExpr *n) {
    n->getExpr()->accept(*this);
}

void VisitorNodeTyper::visit(class StmIf *n) {
    n->getCondition()->accept(*this);
    if (!n->getCondition()->getType()->equals(TypePrimary::getBool()))
        throw __FILE__ "(" QUOTE(__LINE__) "): Condition expresion type of if statement must be bool.";
    n->getOntrue()->accept(*this);
    if (n->getOnfalse())
        n->getOnfalse()->accept(*this);
}

void VisitorNodeTyper::visit(class StmWhile *n) {
    n->getCondition()->accept(*this);
    if (!n->getCondition()->getType()->equals(TypePrimary::getBool()))
        throw __FILE__ "(" QUOTE(__LINE__) "): Condition expresion type of while statement must be bool.";
    n->getBody()->accept(*this);
}

void VisitorNodeTyper::visit(class StmDo *n) {
    n->getCondition()->accept(*this);
    if (!n->getCondition()->getType()->equals(TypePrimary::getBool()))
        throw __FILE__ "(" QUOTE(__LINE__) "): Condition expresion type of do statement must be bool.";
    n->getBody()->accept(*this);
}

void VisitorNodeTyper::visit(class StmFor *n) {
    n->getInitial()->accept(*this);
    n->getCondition()->accept(*this);
    if (!n->getCondition()->getType()->equals(TypePrimary::getBool()))
        throw __FILE__ "(" QUOTE(__LINE__) "): Condition expresion type of for statement must be bool.";
    n->getLoop()->accept(*this);
    n->getBody()->accept(*this);
}

void VisitorNodeTyper::visit(class StmReturn *n) {
    // TODO Check we are in a function
    // TODO check return type with current function or method return type
    if (n->getValue())
        n->getValue()->accept(*this);
}

void VisitorNodeTyper::visit(class StmBlock *n) {
    std::vector<Stm*>* stm = n->getStatements();
    if (n->getStatements()->size() > 0)
    {
        for (std::vector<Stm*>::iterator it = stm->begin(); it != stm->end(); it++)
        {
            (*it)->accept(*this);
        }
    }
}

void VisitorNodeTyper::addFunctionSignature(std::string n, Signature* sig) {
    // If signature table for name doesn't exists, create it
    if (!this->sigs[n])
    {
        this->sigs[n] = new std::vector<Signature*>();
    }
    this->sigs[n]->push_back(sig);
}

void VisitorNodeTyper::addMethodSignature(Class* cl, std::string method_name, Signature* sig) {
    // If signature table for class doesn't exists, create it
    std::map<std::string, std::vector<Signature*>* >* spc = this->sigs_per_class[cl];
    if (spc == 0)
    {
        this->sigs_per_class[cl] = new std::map<std::string, std::vector<Signature*>* >();
        spc = this->sigs_per_class[cl];
    }
    // If signature table for name doesn't exists, create it
    if (!(*spc)[method_name])
    {
        (*spc)[method_name] = new std::vector<Signature*>();
    }
    (*spc)[method_name]->push_back(sig);
}

void VisitorNodeTyper::visit(class StmDecl *n) {
    // Declaration has initial value
    if (n->getInitial())
    {
        n->getInitial()->accept(*this);
        // Declaratoin does not have a type (with var keyword), take initial value type.
        if (!n->getType())
            n->setType(n->getInitial()->getType());
        // Type mismatch if both types are not compatible
        else if (!n->getInitial()->getType()->equals(n->getType()))
            throw __FILE__ "(" QUOTE(__LINE__) "): Type mismatch for initialization.";
    }
    else if (n->isFunction())
    {
        Signature* sgn = new Signature();
        std::string mangle_name = n->getName();
        this->addFunctionSignature(n->getName(), sgn);

        this->symt->pushScope();
        // If args is null, do not lookup them...
        if (n->getArgs())
        {
            std::vector<Argument*>::iterator it;
            for (it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
            {
                // Parse arg and put it in current scope
                this->symt->add((*it)->getName(), (*it)->getType());
                // Add arg type in signature
                sgn->addType((*it)->getType());
                // Generate mangled name
                mangle_name += "_";
                mangle_name += (*it)->getType()->mangle();
            }
        }

        // Do not mangle external functions
        if (!n->isExtern())
        {
            n->setName(mangle_name);
        }
        sgn->setMangledName(n->getName());

        // Populate symbol table (before parsing body, in case of recursion)
        this->symt->addInParent(n->getName(), n->getType());

        // Parse body, put variables in current scope
        if (n->getBody())
        {
            n->getBody()->accept(*this);
        }
        // set the vars of the function, with there address and size
        n->setVars(this->symt->getScope());
        this->symt->popScope();
        return;
    }
    // Populate symbol table
    this->symt->add(n->getName(), n->getType());
}

void VisitorNodeTyper::visit(StmClass *n) {
    Signature* sgn = 0;
    std::vector<Argument*>::iterator it_arg;

    // Iterate through all methods, make mangled names
    std::vector<cy::Function*>::iterator it;
    for (it = n->getClass()->getMethods()->begin(); it != n->getClass()->getMethods()->end(); it++)
    {
        sgn = new Signature();
        this->addMethodSignature(n->getClass(), (*it)->getOriginalName(), sgn);
        // If args is null, do not lookup them...
        if ((*it)->getArgs())
        {
            for (it_arg = (*it)->getArgs()->begin(); it_arg != (*it)->getArgs()->end(); it_arg++)
            {
                // Add arg type in signature
                sgn->addType((*it_arg)->getType());
            }
        }
        // Set mangled name
        (*it)->createMangledName(n->getClass()->getName());
        sgn->setMangledName((*it)->getMangledName());

        // Populate symbol table (before parsing body, in case of recursion)
        this->symt->add((*it)->getMangledName(), (*it)->getType());
    }

    // Iterate through all methods, parsing bodies
    for (it = n->getClass()->getMethods()->begin(); it != n->getClass()->getMethods()->end(); it++)
    {
        this->symt->pushScope();
        // If args is null, do not lookup them...
        if ((*it)->getArgs())
        {
            for (it_arg = (*it)->getArgs()->begin(); it_arg != (*it)->getArgs()->end(); it_arg++)
            {
                // Parse arg and put it_arg in current scope
                this->symt->add((*it_arg)->getName(), (*it_arg)->getType());
            }
        }

        // Parse body, put variables in current scope
        if ((*it)->getBody())
        {
            (*it)->getBody()->accept(*this);
        }
        // set the vars of the function, with there address and size
        (*it)->setVars(this->symt->getScope());
        this->symt->popScope();
    }
}

void VisitorNodeTyper::visit(class StmSwitch *n) {
    n->getCondition()->accept(*this);
    Type* cond_type = n->getCondition()->getType();
    if (!cond_type->equals(TypePrimary::getByte()) && !cond_type->equals(TypePrimary::getShort())
        && !cond_type->equals(TypePrimary::getInt()) && !cond_type->equals(TypePrimary::getLong())
    )
        throw __FILE__ "(" QUOTE(__LINE__) "): Condition expression in switch statement must be an integer.";
    if (n->getDefault())
        n->getDefault()->accept(*this);
    std::map<long, Stm*>::iterator it;
    for (it = n->getCases()->begin(); it != n->getCases()->end(); ++it)
    {
        it->second->accept(*this);
    }
}

void VisitorNodeTyper::setSymtab(Symtab* s) {
    this->symt = s;
}
