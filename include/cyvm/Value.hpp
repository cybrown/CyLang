#ifndef __VALUE__
#define __VALUE__

#include "TypePrimary.hpp"

namespace cy
{

class Value {
protected:
    Type* type;
    union {
        bool Bool;
        char Byte;
        short Short;
        int Int;
        long Long;
        float Float;
        double Double;
        void*  Pointer;
    } value;
public:
    Type* getType();
    void  setType(Type* t);

    Value();

    Value(bool arg);
    Value(char arg);
    Value(short arg);
    Value(int arg);
    Value(long arg);
    Value(float arg);
    Value(double arg);
    Value(void* arg);

    bool   getBool();
    char   getByte();
    short  getShort();
    int    getInt();
    long   getLong();
    float  getFloat();
    double getDouble();
    void*  getPointer();
    void setBool(bool v);
    void setByte(char v);
    void setShort(short v);
    void setInt(int v);
    void setLong(long v);
    void setFloat(float v);
    void setDouble(double v);
    void setPointer(void* v);

    void display();
};

}

#endif
