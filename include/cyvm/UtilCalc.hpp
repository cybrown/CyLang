#ifndef __UTIL_CALC__
#define __UTIL_CALC__

#include "Value.hpp"
#include "ExprOP2.hpp"

class UtilCalc {
public:
    template <typename T> static cy::Value* CalcOP2(ExprOP2::op o, T a, T b);
    template <typename T> static cy::Value* CalcOP2F(ExprOP2::op o, T a, T b);
    template <typename T> static cy::Value* CalcOP1(ExprOP1::op o, T a);
    template <typename T> static cy::Value* CalcOP1F(ExprOP1::op o, T a);
};

#include "UtilCalc.tpp"

#endif
