#ifndef __NODE_EXPR_ARRAY__
#define __NODE_EXPR_ARRAY__

#include "TypeArray.hpp"
#include "Expr.hpp"
#include "ExprLiteral.hpp"

/**
Node for an array.
*/
class ExprArray: public Expr {
protected:
    std::vector<Expr*>* values;
    Type* t;
    Type* contentType;
    int size;
    Expr* expr_size;
    void initialize();
public:
    ExprArray();
    ExprArray(Type* t, int num);
    ExprArray(Type* t, Expr* num);
    ExprArray(char* str);

    void addExpr(Expr* e);
    std::vector<Expr*>* getValues();

    void accept(VisitorNode &v);
    Type* getType();
    void setType(Type*);

    void setContentType(Type*);
    Type* getContentType();
    
    int getSize();
    Expr* getExprSize();
};

#endif
