#include "StmSwitch.hpp"

StmSwitch::StmSwitch() {
    this->condition = 0;
    this->cases = new std::map<long, Stm*>;
    this->def = 0;
    this->def_pos = 0;
}

void StmSwitch::setCondition(Expr* c) {
    this->condition = c;
}

Expr* StmSwitch::getCondition() {
    return this->condition;
}

void StmSwitch::addCase(long index, Stm* s) {
    this->cases->insert(std::make_pair(index, s));
}

std::map<long, Stm*>* StmSwitch::getCases() {
    return this->cases;
}

void StmSwitch::accept(VisitorNode &v) {
    v.visit(this);
}

Stm* StmSwitch::getDefault() {
    return this->def;
}

void StmSwitch::setDefault(Stm* s) {
    if (this->def != 0)
        throw "Default case for switch statement can only be definied once.";
    this->def = s;
    this->def_pos = this->cases->size();
}

int StmSwitch::getDefaultPosition() {
    return this->def_pos;
}
