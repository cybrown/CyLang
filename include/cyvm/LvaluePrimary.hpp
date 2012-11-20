#ifndef __LVALUE_PRIMARY__
#define __LVALUE_PRIMARY__

#include "Lvalue.hpp"

class LvaluePrimary: public Lvalue {
public:
    void assign(Expr* e);
};

#endif
