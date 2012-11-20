#ifndef __FUNCTION__
#define __FUNCTION__

#include <vector>
#include "Argument.hpp"
#include "Stm.hpp"

namespace cy
{
    class Function {
    protected:
        Type* type;
        Stm* body;
        std::vector<Argument*>* args;
        std::map<std::string, Variable*>* vars;
        std::string original_name;
        std::string mangled_name;
        bool is_static;
        bool is_virtual;
    public:
        Function(Type* t, std::vector<Argument*>* a, Stm* b, std::map<std::string, Variable*>* v = 0);
        void setArgs(std::vector<Argument*>* v);
        void setType(Type* t);
        Type* getType();
        void setVars(std::map<std::string, Variable*>* v);
        std::map<std::string, Variable*>* getVars();

        std::vector<Argument*>* getArgs();
        void setBody(Stm* b);
        Stm* getBody();

        void setOriginalName(std::string on);
        std::string getOriginalName();
        void setMangledName(std::string mn);
        std::string getMangledName();
        void createMangledName();
        void createMangledName(std::string class_name);

        bool isStatic();
        void setStatic(bool s);
        bool isVirtual();
        void setVirtual(bool v);
    };
}

#endif
