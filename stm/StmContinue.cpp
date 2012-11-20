#include "StmContinue.hpp"

void StmContinue::accept(VisitorNode &v) {
    v.visit(this);
}
