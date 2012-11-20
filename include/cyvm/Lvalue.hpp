#ifndef __LVALUE__
#define __LVALUE__

#include "Type.hpp"
#include "Expr.hpp"

/*

assignable types:

primary
label to function
pointer to array
pointer to class



*/


class Lvalue {
protected:
    union {
        char Char;
        unsigned char Byte;
        short Short;
        int Int;
        long Long;
        float Float;
        double Double;
    } value;
    Type* type;
public:
    void assign(unsigned char v);
    void assign(short v);
    void assign(int v);
    void assign(long v);
    void assign(float v);
    void assign(double v);

    unsigned char getByte();
    short getShort();
    int getInt();
    long getLong();
    float getFloat();
    double getDouble();

    void setType(Type* t);
    Type* getType();
};

#endif
