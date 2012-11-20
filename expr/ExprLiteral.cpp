#include "ExprLiteral.hpp"
#include "TypePrimary.hpp"

bool ExprLiteral::getBool(){
    return this->value->getBool();
}

char ExprLiteral::getByte(){
    return this->value->getByte();
}

short ExprLiteral::getShort(){
    return this->value->getShort();
}

int ExprLiteral::getInt(){
    return this->value->getInt();
}

long ExprLiteral::getLong(){
    return this->value->getLong();
}

float ExprLiteral::getFloat(){
    return this->value->getFloat();
}

double ExprLiteral::getDouble(){
    return this->value->getDouble();
}

ExprLiteral::ExprLiteral(bool arg) {
    this->value = new cy::Value(arg);
}

ExprLiteral::ExprLiteral(char arg) {
    this->value = new cy::Value(arg);
}

ExprLiteral::ExprLiteral(short arg) {
    this->value = new cy::Value(arg);
}

ExprLiteral::ExprLiteral(int arg) {
    this->value = new cy::Value(arg);
}

ExprLiteral::ExprLiteral(long arg) {
    this->value = new cy::Value(arg);
}

ExprLiteral::ExprLiteral(float arg) {
    this->value = new cy::Value(arg);
}

ExprLiteral::ExprLiteral(double arg) {
    this->value = new cy::Value(arg);
}

void ExprLiteral::accept(VisitorNode &v) {
    v.visit(this);
}

Type* ExprLiteral::getType() {
    return this->value->getType();
}

cy::Value* ExprLiteral::getValue() {
    return this->value;
}
