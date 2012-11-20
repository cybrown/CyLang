#ifndef __VISITOR_NODE_LLVM__
#define __VISITOR_NODE_LLVM__

#include <map>
#include <string>
#include <vector>

#include "llvm/DerivedTypes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/IRBuilder.h"

#include "VisitorNode.hpp"
#include "AllNodes.hpp"
#include "AllTypes.hpp"
#include "Class.hpp"
#include "Argument.hpp"

/**
Visitor to create LLVM instructions via the API.
*/

class VisitorNodeLlvm: public VisitorNode {
public:
    llvm::Module* module;
    std::vector<llvm::Value*> val_stack;            // stack of values for expressions
    llvm::IRBuilder<> *Builder;
    std::map<std::string, llvm::Value*> locals;     // Local scope

    std::vector<llvm::BasicBlock *> block_stack;

    std::vector<llvm::BasicBlock *> block_continue; // Blocks where to continue
    std::vector<llvm::BasicBlock *> block_break;    // Blocks where to break

    std::vector<llvm::Function*> current_func;

    llvm::ExecutionEngine *exec;
    llvm::FunctionPassManager *fpm;

    bool no_load;   // Set to true if next value must not be loaded, for left hand side assignement value

    bool verify;
    const llvm::Type* type2llvm(::Type* t, bool no_pointer);
    llvm::AllocaInst * CreateEntryBlockAlloca(llvm::Function *TheFunction, const std::string &VarName, ::Type* t);
    llvm::TargetData* targetData;
public:
    VisitorNodeLlvm();
    void visit(ExprAssign *n);
    void visit(ExprArray *n);
    void visit(ExprCondition *n);
    void visit(ExprLiteral *n);
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
    void visit(StmBreak *n);
    void visit(StmContinue *n);
    void visit(ExprObject *n);
    void visit(StmClass *n);
    void visit(ExprClass *n);

    void optimize();
    llvm::Module* getModule();
};

#endif
