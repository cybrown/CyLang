#include "Expr.hpp"

Type* Expr::getType() {
    return this->type;
}

void Expr::setType(Type*t) {
    this->type = t;
}

bool Expr::assignable() {
    return false;
}

std::pair<int, int>* Expr::getRef() {
    return 0;
}
