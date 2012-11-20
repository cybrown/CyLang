#include "StmNop.hpp"

void StmNop::accept(VisitorNode &v) {
    v.visit(this);
}
