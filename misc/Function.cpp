#include "Function.hpp"

namespace cy
{
    Function::Function(Type* t, std::vector<Argument*>* a, Stm* b, std::map<std::string, Variable*>* v) {
        this->setType(t);
        this->setArgs(a);
        this->setBody(b);
        this->setVars(v);
        this->setStatic(true);
        this->setVirtual(false);
    }

    void Function::setType(Type* t) {
        this->type = t;
    }

    Type* Function::getType() {
        return this->type;
    }

    void Function::setArgs(std::vector<Argument*>* a) {
        this->args = a;
    }

    void Function::setVars(std::map<std::string, Variable*>* v) {
        this->vars = v;
    }

    std::map<std::string, Variable*>* Function::getVars() {
        return this->vars;
    }

    std::vector<Argument*>* Function::getArgs() {
        return this->args;
    }

    void Function::setBody(Stm* b) {
        this->body = b;
    }

    Stm* Function::getBody() {
        return this->body;
    }

    void Function::setOriginalName(std::string on) {
        this->original_name = on;
    }

    std::string Function::getOriginalName() {
        return this->original_name;
    }

    void Function::setMangledName(std::string on) {
        this->mangled_name = on;
    }

    std::string Function::getMangledName() {
        return this->mangled_name;
    }

    void Function::createMangledName() {
        std::string mangle_name;
        mangle_name += this->getOriginalName();
        // If args is null, do not lookup them...
        if (this->getArgs())
        {
            for (std::vector<Argument*>::iterator it_arg = this->getArgs()->begin(); it_arg != this->getArgs()->end(); it_arg++)
            {
                // Generate mangled name
                mangle_name += "_";
                mangle_name += (*it_arg)->getType()->mangle();
            }
        }
        this->setMangledName(mangle_name);
    }

    void Function::createMangledName(std::string class_name) {
        this->createMangledName();
        this->setMangledName(class_name + "_" + this->getMangledName());
    }

    bool Function::isStatic() {
        return this->is_static;
    }

    void Function::setStatic(bool s) {
        this->is_static = s;
    }

    bool Function::isVirtual() {
        return this->is_virtual;
    }

    void Function::setVirtual(bool v) {
        this->is_virtual = v;
    }

}
