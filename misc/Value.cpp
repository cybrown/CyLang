#include "Value.hpp"

#include <iostream>

#pragma GCC diagnostic ignored "-Wlong-long"

// Values are casted to long long to initialize trailing zeros in one assignement
// TODO compare with assignement first with zero, and then uncasted assignment

namespace cy {

Type* Value::getType() {
    return this->type;
}

void Value::setType(Type* t) {
    this->type = t;
}

bool Value::getBool() {
    return value.Bool;
}

void Value::setBool(bool v) {
    this->type = TypePrimary::getBool();
    value.Bool = v;
}

char Value::getByte() {
    return value.Byte;
}

void Value::setByte(char v) {
    this->type = TypePrimary::getByte();
    value.Long = (long long)v;
}

short Value::getShort() {
    return value.Short;
}

void Value::setShort(short v) {
    this->type = TypePrimary::getShort();
    value.Long = (long long)v;
}

int Value::getInt() {
    return value.Int;
}

void Value::setInt(int v) {
    this->type = TypePrimary::getInt();
    value.Long = (long long)v;
}

long Value::getLong() {
    return value.Long;
}

void Value::setLong(long v) {
    this->type = TypePrimary::getLong();
    value.Long = v;
}

float Value::getFloat() {
    return value.Float;
}

void Value::setFloat(float v) {
    this->type = TypePrimary::getFloat();
    value.Float = v;
}

double Value::getDouble() {
    return value.Double;
}

void Value::setDouble(double v) {
    this->type = TypePrimary::getDouble();
    value.Double = v;
}

void* Value::getPointer() {
    return value.Pointer;
}

void Value::setPointer(void* v) {
    value.Pointer = v;
}

Value::Value(bool arg) {
    this->setBool(arg);
}

Value::Value(char arg) {
    this->setByte(arg);
}

Value::Value(short arg) {
    this->setShort(arg);
}

Value::Value(int arg) {
    this->setInt(arg);
}

Value::Value(long arg) {
    this->setLong(arg);
}

Value::Value(float arg) {
    this->setFloat(arg);
}

Value::Value(double arg) {
    this->setDouble(arg);
}

Value::Value(void* arg) {
    this->setPointer(arg);
}

Value::Value() {
    this->type = 0;
}

void Value::display() {
    if (this->getType() == TypePrimary::getBool())
        std::cout << "Bool: " << (this->getBool() ? "true" : "false") << std::endl;
    else if (this->getType() == TypePrimary::getByte())
        std::cout << "Byte: " << this->getByte() << std::endl;
    else if (this->getType() == TypePrimary::getShort())
        std::cout << "Short: " << this->getShort() << std::endl;
    else if (this->getType() == TypePrimary::getInt())
        std::cout << "Int: " << this->getInt() << std::endl;
    else if (this->getType() == TypePrimary::getLong())
        std::cout << "Long: " << this->getLong() << std::endl;
    else if (this->getType() == TypePrimary::getFloat())
        std::cout << "Float: " << this->getFloat() << std::endl;
    else if (this->getType() == TypePrimary::getDouble())
        std::cout << "Double: " << this->getDouble() << std::endl;
}

}
