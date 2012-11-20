#ifndef __NODE_EXPR_LITERAL__
#define __NODE_EXPR_LITERAL__

#include "Expr.hpp"
#include "Value.hpp"

/**
Node for a constant value.
*/
class ExprLiteral: public Expr {
protected:
    cy::Value* value;
public:
    bool getBool();
    char getByte();
    short getShort();
    int getInt();
    long getLong();
    float getFloat();
    double getDouble();

    ExprLiteral(bool arg);
    ExprLiteral(char arg);
    ExprLiteral(short arg);
    ExprLiteral(int arg);
    ExprLiteral(long arg);
    ExprLiteral(float arg);
    ExprLiteral(double arg);

    Type* getType();
    cy::Value* getValue();
    
    void accept(VisitorNode &v);
};

#endif
