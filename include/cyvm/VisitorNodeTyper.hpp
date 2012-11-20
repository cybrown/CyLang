#ifndef __VISITOR_NODE_TYPER__
#define __VISITOR_NODE_TYPER__

#include <map>
#include <string>

#include "VisitorNode.hpp"
#include "AllNodes.hpp"
#include "AllTypes.hpp"
#include "Signature.hpp"
#include "Argument.hpp"

/**
Class used to compute type values of expression, and
find variables to populate symbol table.
*/
class VisitorNodeTyper: public VisitorNode {
protected:
    std::map<std::string, std::vector<Signature*>* > sigs;   // "name" => {signature}
    std::map<Class*, std::map<std::string, std::vector<Signature*>* >* > sigs_per_class;   //"class" => {"name" => {signature}}
    void addFunctionSignature(std::string n, Signature* sig);
    void addMethodSignature(Class* cl, std::string method_name, Signature* sig);
    Class* cur_class;
    bool look_for_mangled;
public:
    VisitorNodeTyper();
    void visit(ExprAssign *n);
    void visit(ExprArray *n);
    void visit(ExprCondition *n);
    void visit(ExprOP1 *n);
    void visit(ExprOP2 *n);
    void visit(ExprSymbol *n);
    void visit(StmExpr *n);
    void visit(StmIf *n);
    void visit(StmWhile *n);
    void visit(StmDo *n);
    void visit(StmFor *n);
    void visit(StmBlock *n);
    void visit(StmReturn *n);
    void visit(StmDecl *n);
    void visit(StmSwitch *n);
    void visit(ExprCall *n);
    void visit(StmClass *n);
    void visit(ExprClass *n);
    void setSymtab(Symtab* s);
};

#endif
