#include "StmDecl.hpp"

void StmDecl::initialize(Type* t, char* id, std::vector<Argument*>* a, Stm* b) {
    // If arglist or body are def, it is a function
    this->is_func = a || b ? true : false;
    this->init = 0;
    this->vars = 0;
    this->setType(t);
    this->setName(id);

    this->function = new cy::Function(t, a == 0 ? new std::vector<Argument*>() : a, b);
}

StmDecl::StmDecl(Type* t, char* id, std::vector<Argument*>* a, Stm* b, bool is_ext) {
    this->initialize(t, id, a, b);
    this->is_ext = is_ext;
}

StmDecl::StmDecl(Type* t, char* id, Expr* init) {
    this->initialize(t, id);
    this->init = init;
}

Type* StmDecl::getType() {
    return this->type;
}

void StmDecl::setType(Type* t) {
    if (this->isFunction())
    {
        TypeFunction* tf = new TypeFunction(t);
        tf->setName(this->getName());
        tf->setStatic(true);
        this->type = tf;
    }
    else
    {
        this->type = t;
    }
}

std::string StmDecl::getName() {
    return this->name;
}

void StmDecl::setName(std::string n) {
    this->name = n;
    if (this->isFunction())
    {
        dynamic_cast<TypeFunction*>(this->type)->setName(n);
    }
}

Stm* StmDecl::getBody() {
    return this->function->getBody();
}

std::vector<Argument*>* StmDecl::getArgs() {
    return this->function->getArgs();
}

void StmDecl::addArg(Argument* arg) {
    this->getArgs()->push_back(arg);
}

void StmDecl::accept(VisitorNode &v) {
    v.visit(this);
}

void StmDecl::setVars(std::map<std::string, Variable*>* v) {
    this->vars = v;
}

std::map<std::string, Variable*>* StmDecl::getVars() {
    return this->vars;
}

Expr* StmDecl::getInitial() {
    return this->init;
}

void StmDecl::setInitial(Expr* arg) {
    this->init = arg;
}

bool StmDecl::isFunction() {
    return this->is_func;
}

bool StmDecl::isVar() {
    return !this->isFunction();
}

bool StmDecl::isExtern() {
    return this->is_ext;
}
