#include "StmBreak.hpp"

void StmBreak::accept(VisitorNode &v) {
    v.visit(this);
}
