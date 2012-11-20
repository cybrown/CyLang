#ifndef __NODE_EXPR_OBJECT__
#define __NODE_EXPR_OBJECT__

#include <string>
#include "Expr.hpp"
#include "Function.hpp"

/**
Node for an object value, or a method.
*/
class ExprObject: public Expr {
protected:
	std::string name;
    void initialize();
    cy::Function* function;
public:
    ExprObject();
    ExprObject(Type* t);
    Type* getType();
    void setType(Type* t);
    cy::Function* getFunction();
    void setFunction(cy::Function* f);
    void accept(VisitorNode &v);
    bool isMethod();
    std::string getName();
    void setName(std::string s);
};

#endif
