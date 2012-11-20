#include "StmBlock.hpp"

void StmBlock::accept(VisitorNode &v) {
    v.visit(this);
}

StmBlock::StmBlock() {
    this->statements = new std::vector<Stm*>();
}

StmBlock::StmBlock(Stm *n) {
    this->statements = new std::vector<Stm*>();
    this->addStatement(n);
}

void StmBlock::addStatement(Stm* n) {
    this->statements->push_back(n);
}

std::vector<Stm*>* StmBlock::getStatements() {
    return this->statements;
}
