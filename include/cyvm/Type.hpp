#ifndef __TYPE__
#define __TYPE__

#include <vector>
#include <string>
#include "VisitorType.hpp"

/*
// Declaration of variables

int my_int // simple integer

int my_var[10] // array of integers

int my_var[8][10] // array of arrays of integers

int my_var[4,5] // multidimensionnal array

Object my_obj // object

Object my_objs[8] // Array of objects

Vector<double> values // Vector of double

Map<string, Object> dictionnairy // Map of string and object

Vector<int> my_vector[6] // Array of Vector of integers


base_type (primary_type | class)
array_depth
array_dimensions
Template classes


//Operations
Type comparison

*/

/**
The basic class for the type system.
*/
class Type {
public:
    virtual bool isArray();
    virtual bool isClass();
    virtual bool isFunction();
    virtual bool isPrimary();
    virtual bool equals(Type *t) =0;
    virtual void acceptVisitor(class VisitorType &v)=0;
    virtual int stackSize();
    virtual int heapSize();
    virtual bool canReceive(Type* t)=0;
    virtual std::string mangle();
};

#endif
