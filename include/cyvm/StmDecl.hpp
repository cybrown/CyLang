#ifndef __NODE_STM_DECL__
#define __NODE_STM_DECL__

#include <vector>
#include <map>
#include <string>
#include "Stm.hpp"
#include "Type.hpp"
#include "Function.hpp"
#include "Expr.hpp"
#include "Argument.hpp"
#include "AllTypes.hpp"

/**
Expression statement.
*/
class StmDecl: public Stm {
protected:
    Type*                             type;
    Expr*                             init;
    cy::Function*                     function;
    std::string                       name;
    std::map<std::string, Variable*>* vars;

    bool                              is_func;
    bool                              is_var;
    bool                              is_ext;
    void initialize(Type* t, char* id, std::vector<Argument*>* a = 0, Stm* b = 0);
public:
    StmDecl(Type* t, char* id, std::vector<Argument*>* a, Stm* b, bool is_ext = false);
    StmDecl(Type* t, char* id, Expr* init);
    Type*                             getType();
    void                              setType(Type* t);
    std::string                       getName();
    void                              setName(std::string n);
    Stm*                              getBody();
    std::vector<Argument*>*           getArgs();
    void                              addArg(Argument* arg);
    void                              accept(VisitorNode &v);
    void                              setVars(std::map<std::string, Variable*>* v);
    std::map<std::string, Variable*>* getVars();
    Expr*                             getInitial();
    void                              setInitial(Expr* arg);
    bool                              isFunction();
    bool                              isVar();
    bool                              isExtern();
};

#endif
