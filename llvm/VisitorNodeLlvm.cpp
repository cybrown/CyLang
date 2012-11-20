#include "VisitorNodeLlvm.hpp"

using namespace llvm;

#pragma GCC diagnostic ignored "-Wunused-parameter"

// TODO DEBUG
#include <iostream>
using namespace std;

#define QUOTE(x) PREQUOTE(x)
#define PREQUOTE(x) #x

// Convert Type into llvm Type
const llvm::Type* VisitorNodeLlvm::type2llvm(::Type* t, bool no_pointer = false) {
    TypePrimary* tp = dynamic_cast<TypePrimary*>(t);
    TypeArray* ta = dynamic_cast<TypeArray*>(t);
    TypeClass* tc = dynamic_cast<TypeClass*>(t);
    if (tp != 0)
    {
        if (tp->isVoid())
        {
            return llvm::Type::getVoidTy(getGlobalContext());
        }
        else if (tp->isBool())
        {
            return llvm::Type::getInt1Ty(getGlobalContext());
        }
        else if (tp->isByte())
        {
            return llvm::Type::getInt8Ty(getGlobalContext());
        }
        else if (tp->isShort())
        {
            return llvm::Type::getInt16Ty(getGlobalContext());
        }
        else if (tp->isInt())
        {
            return llvm::Type::getInt32Ty(getGlobalContext());
        }
        else if (tp->isLong())
        {
            return llvm::Type::getInt64Ty(getGlobalContext());
        }
        else if (tp->isFloat())
        {
            return llvm::Type::getFloatTy(getGlobalContext());
        }
        else if (tp->isDouble())
        {
            return llvm::Type::getDoubleTy(getGlobalContext());
        }
        else
        {
            throw __FILE__ "(" QUOTE(__LINE__) "): Is not a primary type.";
        }
    }
    else if (ta != 0)
    {
        return PointerType::get(type2llvm(ta->getType()), 0);
    }
    else if (tc != 0)
    {
        // TODO LLVM 3 HERE!!!
        /*
        StructType *StructTy_struct = this->module->getTypeByName("struct." + tc->getClass()->getName());
        if (!StructTy_struct)
        {
            StructTy_struct = StructType::create(this->module->getContext(), "struct." + tc->getClass()->getName());
        }
        std::vector<llvm::Type*>StructTy_struct_fields;
        StructTy_struct_fields.push_back(IntegerType::get(this->module->getContext(), 32));
        StructTy_struct_fields.push_back(IntegerType::get(this->module->getContext(), 32));
        if (StructTy_struct->isOpaque())
        {
            StructTy_struct->setBody(StructTy_struct_A_fields, isPacked=false);
        }
        */

        std::vector<const llvm::Type*> StructTy_struct_fields;
        std::vector<std::string>::iterator it;
        for (it = tc->getClass()->getAttributes()->begin(); it != tc->getClass()->getAttributes()->end(); it++)
        {
            StructTy_struct_fields.push_back(type2llvm(tc->getClass()->getAttrType(*it)));
        }
        StructType *StructTy_struct = StructType::get(this->module->getContext(), StructTy_struct_fields);
        if (no_pointer)
        {
            return StructTy_struct;
        }
        else
        {
            return PointerType::get(StructTy_struct, 0);
        }
    }
    else
    {
        throw __FILE__ "(" QUOTE(__LINE__) "): Is not a supported type.";
    }
}

Module* VisitorNodeLlvm::getModule() {
    return this->module;
}

VisitorNodeLlvm::VisitorNodeLlvm() {
    this->module = new Module("cyexec", getGlobalContext());
    this->Builder = new IRBuilder<>(getGlobalContext());
    this->no_load = false;
    this->targetData = new TargetData(this->module);

    // Declare malloc function
    std::vector<const llvm::Type*> arg_type(1, llvm::Type::getInt64Ty(getGlobalContext()));
    FunctionType *FT = FunctionType::get(PointerType::get(llvm::Type::getInt8Ty(getGlobalContext()), 0), arg_type, false);
    Function::Create(FT, Function::ExternalLinkage, "cy_malloc", this->module);
    Function::Create(FT, Function::ExternalLinkage, "cy_malloc2", this->module);
}

void VisitorNodeLlvm::optimize() {
    this->fpm = new FunctionPassManager(this->module);

    // Set up the optimizer pipeline.  Start with registering info about how the
    // target lays out data structures.
    this->fpm->add(new TargetData(*this->exec->getTargetData()));
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    this->fpm->add(createInstructionCombiningPass());
    // Reassociate expressions.
    this->fpm->add(createReassociatePass());
    // Eliminate Common SubExpressions.
    this->fpm->add(createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    this->fpm->add(createCFGSimplificationPass());

    this->fpm->doInitialization();
}

void VisitorNodeLlvm::visit(ExprAssign *n) {
    this->no_load = true;   // Do not load the left value, we need to write there
    n->getLeft()->accept(*this);
    Value* L = val_stack.back();    // Do not pop back left value, keeping it for expression value
    val_stack.pop_back();
    AllocaInst* ai;
    if (n->isPostfix())     // Unary postfix operator ++ or --, keep right hand value
    {
        ai = Builder->CreateAlloca(type2llvm(n->getLeft()->getType()), 0, "");
        Builder->CreateStore(Builder->CreateLoad(L), ai);
    }
    //LoadInst* value = new LoadInst(ptr_a, "", false, this->Builder->GetInsertBlock());
    n->getRight()->accept(*this);
    Value* R = val_stack.back();
    Builder->CreateStore(R, L);
    if (n->isPostfix())         // Discard last value on stack and put right hand value
    {
        val_stack.pop_back();
        val_stack.push_back(Builder->CreateLoad(ai));
    }
}

void VisitorNodeLlvm::visit(ExprArray *n) {
    // Create alloca where array is
    AllocaInst* ai_array = Builder->CreateAlloca(type2llvm(n->getType()), 0);

    // Allocate memory for array
    std::vector<Value*> argv;
    // Push amount of memory needed
    Expr* expr_size = n->getExprSize();
    if (expr_size)
    {
        expr_size->accept(*this);
        Value* VSize = val_stack.back();
        val_stack.pop_back();
        argv.push_back(
            this->Builder->CreateMul(
                Builder->CreateIntCast(VSize, llvm::Type::getInt64Ty(getGlobalContext()), true), 
                ConstantInt::get(
                    getGlobalContext(),
                    APInt(
                        64,
                        this->targetData->getTypeAllocSize(type2llvm(n->getContentType())),
                        true
                    )
                )
            )
        );
    }
    else
    {
        int size;
        size = n->getSize();
        if (!size)
        {
            size = n->getValues()->size();
        }
        argv.push_back(
            ConstantInt::get(
                getGlobalContext(),
                APInt(
                    64,
                    size * this->targetData->getTypeAllocSize(
                        type2llvm(n->getContentType())
                    ),
                    true
                )
            )
        );   
    }

    // Store allocated memory on allocainst
    Builder->CreateStore(
        Builder->CreateBitCast(
            Builder->CreateCall(
                this->module->getFunction("cy_malloc"),
                argv.begin(),
                argv.end()
            ),
            type2llvm(n->getType())
        ),
        ai_array
    );

    // Assign each expression to there table cell, if not an array of empty values
    if (!n->getSize())
    {
        std::vector<Expr*>::iterator it;
        int index = 0;
        std::vector<Value*> ind;
        for (it = n->getValues()->begin(); it != n->getValues()->end(); it++)
        {
            ind.clear();
            (*it)->accept(*this);
            ind.push_back(ConstantInt::get(getGlobalContext(), APInt(64, index, true)));
            Builder->CreateStore(
                val_stack.back(),
                Builder->CreateGEP(
                    Builder->CreateLoad(ai_array),
                    ind.begin(),
                    ind.end()
                )
            );
            
            val_stack.pop_back();
            index++;
        }
    }

    // Load array in the stack
    val_stack.push_back(Builder->CreateLoad(ai_array, "tmparr"));
}

void VisitorNodeLlvm::visit(ExprCondition *n) {
    n->getCondition()->accept(*this);
    Value *CondV = val_stack.back();
    val_stack.pop_back();

    Function *cur_func = current_func.back();

    // Create blocks for the then and else cases.  Insert the 'then' block at the
    // end of the function.
    BasicBlock *ThenBB = BasicBlock::Create(getGlobalContext(), "then", cur_func);
    BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "else");
    BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");

    Builder->CreateCondBr(CondV, ThenBB, ElseBB);

    // Emit then value.
    Builder->SetInsertPoint(ThenBB);

    n->getOntrue()->accept(*this);
    Value *ThenV = val_stack.back();
    val_stack.pop_back();

    Builder->CreateBr(MergeBB);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    ThenBB = Builder->GetInsertBlock();

    // Emit else block.
    cur_func->getBasicBlockList().push_back(ElseBB);
    Builder->SetInsertPoint(ElseBB);

    n->getOnfalse()->accept(*this);
    Value *ElseV =val_stack.back();
    val_stack.pop_back();

    Builder->CreateBr(MergeBB);
    // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
    ElseBB = Builder->GetInsertBlock();

    // Emit merge block.
    cur_func->getBasicBlockList().push_back(MergeBB);
    Builder->SetInsertPoint(MergeBB);
    PHINode *PN = Builder->CreatePHI(type2llvm(n->getType()),"iftmp");

    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);
    val_stack.push_back(PN);

    // Update current insertion
    //block_stack.pop_back();
    //block_stack.push_back(MergeBB);
}

void VisitorNodeLlvm::visit(ExprLiteral *n) {
    if (n->getType()->equals(TypePrimary::getBool()))
        val_stack.push_back(ConstantInt::get(getGlobalContext(), APInt(1, n->getBool(), false)));
    else if (n->getType()->equals(TypePrimary::getByte()))
        val_stack.push_back(ConstantInt::get(getGlobalContext(), APInt(8, n->getByte(), true)));
    else if (n->getType()->equals(TypePrimary::getShort()))
        val_stack.push_back(ConstantInt::get(getGlobalContext(), APInt(16, n->getShort(), true)));
    else if (n->getType()->equals(TypePrimary::getInt()))
        val_stack.push_back(ConstantInt::get(getGlobalContext(), APInt(32, n->getInt(), true)));
    else if (n->getType()->equals(TypePrimary::getLong()))
        val_stack.push_back(ConstantInt::get(getGlobalContext(), APInt(64, n->getLong(), true)));
    else if (n->getType()->equals(TypePrimary::getFloat()))
        val_stack.push_back(ConstantFP::get(getGlobalContext(), APFloat(n->getFloat())));
    else if (n->getType()->equals(TypePrimary::getDouble()))
        val_stack.push_back(ConstantFP::get(getGlobalContext(), APFloat(n->getDouble())));
}

void VisitorNodeLlvm::visit(ExprOP1 *n) {
    // Get value of operand
    n->getOperand()->accept(*this);
    Value *Operand = val_stack.back();
    val_stack.pop_back();

    if (Operand == 0)
        throw __FILE__ "(" QUOTE(__LINE__) "): Operand is null.";

    // Boolean
    if (n->getOperand()->getType()->equals(TypePrimary::getBool()))
    {
        switch (n->getOperator()) {
            case ExprOP1::B_NOT: val_stack.push_back(Builder->CreateNot(Operand)); break;
            case ExprOP1::NOT:   val_stack.push_back(Builder->CreateNot(Operand)); break;
            default:
                throw __FILE__ "(" QUOTE(__LINE__) "): Unknown binary operator for boolean.";
                break;
        }
    }
    // Integer
    else if (
        n->getOperand()->getType()->equals(TypePrimary::getByte())
        || n->getOperand()->getType()->equals(TypePrimary::getInt())
        || n->getOperand()->getType()->equals(TypePrimary::getShort())
        || n->getOperand()->getType()->equals(TypePrimary::getLong())
    )
    {
        switch (n->getOperator()) {
            case ExprOP1::NEG:   val_stack.push_back(Builder->CreateNeg(Operand)); break;
            case ExprOP1::POS:   val_stack.push_back(Operand); break;
            case ExprOP1::B_NOT: val_stack.push_back(Builder->CreateNot(Operand)); break;
            case ExprOP1::NOT:
                Constant* cons_int_zero;
                if (n->getOperand()->getType()->equals(TypePrimary::getByte()))
                    cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(8, 0, true));
                else if (n->getOperand()->getType()->equals(TypePrimary::getShort()))
                    cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(16, 0, true));
                else if (n->getOperand()->getType()->equals(TypePrimary::getInt()))
                    cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(32, 0, true));
                else if (n->getOperand()->getType()->equals(TypePrimary::getLong()))
                    cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(64, 0, true));
                val_stack.push_back(Builder->CreateICmpEQ(Operand, cons_int_zero));
                break;
            default:
                throw __FILE__ "(" QUOTE(__LINE__) "): Unknown unary operator for integer.";
                break;
        }
    }
    // Float
    else if (
        n->getOperand()->getType()->equals(TypePrimary::getFloat())
        || n->getOperand()->getType()->equals(TypePrimary::getDouble())
    )
    {
        switch (n->getOperator()) {
            case ExprOP1::NEG:   val_stack.push_back(Builder->CreateFNeg(Operand)); break;
            case ExprOP1::POS:   val_stack.push_back(Operand); break;
            case ExprOP1::NOT:
                Constant* cons_float_zero;
                if (n->getOperand()->getType()->equals(TypePrimary::getFloat()))
                    cons_float_zero = ConstantFP::get(getGlobalContext(), APFloat(0.0f));
                else if (n->getOperand()->getType()->equals(TypePrimary::getDouble()))
                    cons_float_zero = ConstantFP::get(getGlobalContext(), APFloat(0.0));
                val_stack.push_back(Builder->CreateFCmpUEQ(Operand, cons_float_zero));
                break;
            default:
                throw __FILE__ "(" QUOTE(__LINE__) "): Unknown binary operator for float.";
                break;
        }
    }
    // Other types
    else
    {
        throw __FILE__ "(" QUOTE(__LINE__) "): Unknown type for unary operator.";
    }
}

void VisitorNodeLlvm::visit(ExprClass *n) {
    val_stack.push_back(ConstantInt::get(getGlobalContext(), APInt(8, 0, true)));
}

void VisitorNodeLlvm::visit(ExprOP2 *n) {
    bool _no_load = this->no_load;
    this->no_load = false;
    Value* L = 0;
    Value* R = 0;

    // Get left value
    /*if (n->getOperator() == ExprOP2::DOT)
    {
        this->no_load = true;
    }*/
    n->getLeft()->accept(*this);
    L = val_stack.back();
    val_stack.pop_back();
    /*if (n->getOperator() == ExprOP2::DOT)
    {
        this->no_load = false;
    }*/

    // Right hand value is not evaluated right now, some operators take short circuits
    // and arrays/class must not have them to be loaded


    if (n->getOperator() == ExprOP2::DOT)
    {
        // GEP left value on index of right value
        TypeClass* tc = dynamic_cast<TypeClass*>(n->getLeft()->getType());
        ExprSymbol* sym = dynamic_cast<ExprSymbol*>(n->getRight());
        if (!tc)
        {
            throw "Not a class...";
        }
        if (!sym)
        {
            throw "Not a symbol...";
        }

        n->getLeft()->accept(*this);
        L = val_stack.back();
        val_stack.pop_back();


        std::vector<Value*> ind;

        ind.push_back(ConstantInt::get(getGlobalContext(), APInt(32, 0, true)));
        ind.push_back(ConstantInt::get(getGlobalContext(), APInt(
            32,
            tc->getClass()->getAttrOffset(sym->getName()),
            true)
        ));

        Value* ret;
        ret = Builder->CreateGEP(L, ind.begin(), ind.end(), "mygep");

        if (!_no_load)
        {
            ret = Builder->CreateLoad(ret);
        }
        val_stack.push_back(ret);
    }
    // Evaluate short circuit operators
    else if (n->getOperator() == ExprOP2::OR || n->getOperator() == ExprOP2::AND)
    {
        // Create blocks
        Function *cur_func = current_func.back();
        BasicBlock *KeepLeftBB  = BasicBlock::Create(getGlobalContext(), "logical_keep_left");
        BasicBlock *KeepRightBB = BasicBlock::Create(getGlobalContext(), "logical_keep_right");
        BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "logical_merge");

        // Create comparison and jump for integer types
        if (
            n->getLeft()->getType()->equals(TypePrimary::getBool())
            || n->getLeft()->getType()->equals(TypePrimary::getByte())
            || n->getLeft()->getType()->equals(TypePrimary::getInt())
            || n->getLeft()->getType()->equals(TypePrimary::getShort())
            || n->getLeft()->getType()->equals(TypePrimary::getLong())
        )
        {
            // Get 0 of int type
            Constant* cons_int_zero;
            if (n->getLeft()->getType()->equals(TypePrimary::getBool()))
                cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(1, 0, true));
            else if (n->getLeft()->getType()->equals(TypePrimary::getByte()))
                cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(8, 0, true));
            else if (n->getLeft()->getType()->equals(TypePrimary::getShort()))
                cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(16, 0, true));
            else if (n->getLeft()->getType()->equals(TypePrimary::getInt()))
                cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(32, 0, true));
            else if (n->getLeft()->getType()->equals(TypePrimary::getLong()))
                cons_int_zero = ConstantInt::get(getGlobalContext(), APInt(64, 0, true));

            // Compare Left with 0 (convert to bool), and jump if true
            if (n->getOperator() == ExprOP2::AND)
            {
                Builder->CreateCondBr(Builder->CreateICmpEQ(L, cons_int_zero), KeepLeftBB, KeepRightBB);
            }
            else
            {
                Builder->CreateCondBr(Builder->CreateICmpNE(L, cons_int_zero), KeepLeftBB, KeepRightBB);
            }
        }
        // Create comparison and jump for float types
        else if (
            n->getLeft()->getType()->equals(TypePrimary::getFloat())
            || n->getLeft()->getType()->equals(TypePrimary::getDouble())
        )
        {
            // Get 0 of int type
            Constant* cons_float_zero;
            if (n->getLeft()->getType()->equals(TypePrimary::getFloat()))
                cons_float_zero = ConstantFP::get(getGlobalContext(), APFloat(0.0f));
            else if (n->getLeft()->getType()->equals(TypePrimary::getDouble()))
                cons_float_zero = ConstantFP::get(getGlobalContext(), APFloat(0.0));

            // Compare Left with 0 (convert to bool), and jump if true
            if (n->getOperator() == ExprOP2::AND)
            {
                Builder->CreateCondBr(Builder->CreateFCmpUEQ(L, cons_float_zero), KeepLeftBB, KeepRightBB);
            }
            else
            {
                Builder->CreateCondBr(Builder->CreateFCmpUNE(L, cons_float_zero), KeepLeftBB, KeepRightBB);
            }
        }

        // Write to keep right block
        cur_func->getBasicBlockList().push_back(KeepRightBB);
        Builder->SetInsertPoint(KeepRightBB);

        // Get right value
        n->getRight()->accept(*this);
        R = val_stack.back();
        val_stack.pop_back();

        Builder->CreateBr(MergeBB);
        KeepRightBB = Builder->GetInsertBlock();

        // Write to keep left block
        cur_func->getBasicBlockList().push_back(KeepLeftBB);
        Builder->SetInsertPoint(KeepLeftBB);
        Builder->CreateBr(MergeBB);

        // Write to merge block
        cur_func->getBasicBlockList().push_back(MergeBB);
        Builder->SetInsertPoint(MergeBB);

        PHINode *PN = Builder->CreatePHI(type2llvm(n->getType()),"ortmp");
        PN->addIncoming(L, KeepLeftBB);
        PN->addIncoming(R, KeepRightBB);
        val_stack.push_back(PN);
        return;
    }
    // Evaluate other operators
    else
    {
        // Get right value
        n->getRight()->accept(*this);
        R = val_stack.back();
        val_stack.pop_back();

        if (L == 0 || R == 0)
            throw __FILE__ "(" QUOTE(__LINE__) "): null";   // TODO Error

        // Boolean
        if (n->getLeft()->getType()->equals(TypePrimary::getBool()))
        {
            switch (n->getOperator()) {
                // Comparison
                case ExprOP2::EQ:    val_stack.push_back(Builder->CreateICmpEQ(L, R)); break;
                case ExprOP2::NEQ:   val_stack.push_back(Builder->CreateICmpNE(L, R)); break;
                // Bitwise
                case ExprOP2::B_AND: val_stack.push_back(Builder->CreateAnd(L, R)); break;
                case ExprOP2::B_XOR: val_stack.push_back(Builder->CreateXor(L, R)); break;
                case ExprOP2::B_OR:  val_stack.push_back(Builder->CreateOr(L, R)); break;
                default:
                    throw __FILE__ "(" QUOTE(__LINE__) "): Unknown binary operator for boolean.";
                    break;
            }
        }
        // Integer
        else if (
            n->getLeft()->getType()->equals(TypePrimary::getByte())
            || n->getLeft()->getType()->equals(TypePrimary::getInt())
            || n->getLeft()->getType()->equals(TypePrimary::getShort())
            || n->getLeft()->getType()->equals(TypePrimary::getLong())
        )
        {
            switch (n->getOperator()) {
                // Aritmetic
                case ExprOP2::ADD:   val_stack.push_back(Builder->CreateAdd(L, R)); break;
                case ExprOP2::SUB:   val_stack.push_back(Builder->CreateSub(L, R)); break;
                case ExprOP2::MUL:   val_stack.push_back(Builder->CreateMul(L, R)); break;
                case ExprOP2::DIV:   val_stack.push_back(Builder->CreateSDiv(L, R)); break;
                case ExprOP2::MOD:   val_stack.push_back(Builder->CreateSRem(L, R)); break;
                // Comparison
                case ExprOP2::LT:    val_stack.push_back(Builder->CreateICmpSLT(L, R)); break;
                case ExprOP2::LTE:   val_stack.push_back(Builder->CreateICmpSLE(L, R)); break;
                case ExprOP2::GT:    val_stack.push_back(Builder->CreateICmpSGT(L, R)); break;
                case ExprOP2::GTE:   val_stack.push_back(Builder->CreateICmpSGE(L, R)); break;
                case ExprOP2::EQ:    val_stack.push_back(Builder->CreateICmpEQ(L, R)); break;
                case ExprOP2::NEQ:   val_stack.push_back(Builder->CreateICmpNE(L, R)); break;
                // Bitwise
                case ExprOP2::B_AND: val_stack.push_back(Builder->CreateAnd(L, R)); break;
                case ExprOP2::B_XOR: val_stack.push_back(Builder->CreateXor(L, R)); break;
                case ExprOP2::B_OR:  val_stack.push_back(Builder->CreateOr(L, R)); break;
                case ExprOP2::SHL:   val_stack.push_back(Builder->CreateShl(L, R)); break;
                case ExprOP2::SHR:   val_stack.push_back(Builder->CreateLShr(L, R)); break;
                case ExprOP2::ASHR:  val_stack.push_back(Builder->CreateAShr(L, R)); break;
                default:
                    throw __FILE__ "(" QUOTE(__LINE__) "): Unknown binary operator for integer.";
                    break;
            }
        }
        // Float
        else if (
            n->getLeft()->getType()->equals(TypePrimary::getFloat())
            || n->getLeft()->getType()->equals(TypePrimary::getDouble())
        )
        {
            switch (n->getOperator()) {
                // Aritmetic
                case ExprOP2::ADD:   val_stack.push_back(Builder->CreateFAdd(L, R)); break;
                case ExprOP2::SUB:   val_stack.push_back(Builder->CreateFSub(L, R)); break;
                case ExprOP2::MUL:   val_stack.push_back(Builder->CreateFMul(L, R)); break;
                case ExprOP2::DIV:   val_stack.push_back(Builder->CreateFDiv(L, R)); break;
                case ExprOP2::MOD:   val_stack.push_back(Builder->CreateFRem(L, R)); break;
                // Comparison
                case ExprOP2::LT:    val_stack.push_back(Builder->CreateFCmpULT(L, R)); break;
                case ExprOP2::LTE:   val_stack.push_back(Builder->CreateFCmpULE(L, R)); break;
                case ExprOP2::GT:    val_stack.push_back(Builder->CreateFCmpUGT(L, R)); break;
                case ExprOP2::GTE:   val_stack.push_back(Builder->CreateFCmpUGE(L, R)); break;
                case ExprOP2::EQ:    val_stack.push_back(Builder->CreateFCmpUEQ(L, R)); break;
                case ExprOP2::NEQ:   val_stack.push_back(Builder->CreateFCmpUNE(L, R)); break;
                default:
                    throw __FILE__ "(" QUOTE(__LINE__) "): Unknown binary operator for float.";
                    break;
            }
        }
        // Array
        else if (n->getLeft()->getType()->isArray())
        {
            std::vector<Value*> ind;
            switch (n->getOperator()) {
                case ExprOP2::ARRAY:
                    //ind = new std::vector<Value*>();
                    ind.push_back(R);
                    Value* ret;
                    if (_no_load)
                    {
                        ret = Builder->CreateGEP(
                                //Builder->CreateLoad(L)
                                L
                            , ind.begin(), ind.end(), "mygep");
                    }
                    else
                    {
                        ret = Builder->CreateLoad(
                            Builder->CreateGEP(
                                //Builder->CreateLoad(L)
                                L
                            , ind.begin(), ind.end(), "mygep")
                        );
                    }
                    val_stack.push_back(ret);
                    break;
                default:
                    throw __FILE__ "(" QUOTE(__LINE__) "): Unknown binary operator for array.";
                    break;
            }
        }
        else
        {
            throw __FILE__ "(" QUOTE(__LINE__) "): Unknown type for binary operator.";
        }
    }
}

void VisitorNodeLlvm::visit(ExprCall *n) {
    // TODO visit lhs
    // Get the type of callee to fetch the function name
    TypeFunction* tf = dynamic_cast<TypeFunction*>(n->getCallee()->getType());
    if (!tf)    // Callee node does not have a type function
        throw __FILE__ "(" QUOTE(__LINE__) "): Callee expression is not TypeFunction";
    Function* CalleeF = this->module->getFunction(tf->getName());
    if (CalleeF == 0)   // Function not found in module
        throw __FILE__ "(" QUOTE(__LINE__) "): Unknown function referenced: " + tf->getName();
    // If argument mismatch error.
    if (CalleeF->arg_size() != n->getArgs()->size())    // Arg length mismatch
        throw __FILE__ "(" QUOTE(__LINE__) "): Incorrect # arguments passed for " + tf->getName();
    // Compute each arguments, and add it to the call
    std::vector<Expr*>::iterator it;
    std::vector<Value*> argv;

    std::vector<const llvm::Type*> arg_types;

    for (it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
    {
        (*it)->accept(*this);
        Value* V = val_stack.back();
        // Cast value to argument type (in case of parent class)
        V = Builder->CreateBitCast(V, type2llvm((*it)->getType()));
        arg_types.push_back(type2llvm((*it)->getType()));
        argv.push_back(V);
        val_stack.pop_back();
    }

    /*
    get object
    (i8*) get pointer to vtable
    (i32) get index of method in vtable
    (i8*) load pointer to method
    cast pointer to method from i8* to function type
    (res) call method
    */
    //cout << tf->getName() << ": " << (tf->isOverridden() ? "override" : tf->isVirtual() ? "virtual" : tf->isStatic() ? "static" : "") << endl;
    if (tf->isOverridden() || tf->isVirtual())
    {
        int vmOffset = tf->getClass()->getVirtualMethodOffset(tf->getName());
        //cout << "# Index: " << vmOffset << endl;
        std::vector<Value*> ind;

        ind.push_back(ConstantInt::get(getGlobalContext(), APInt(32, 0, true)));
        ind.push_back(ConstantInt::get(getGlobalContext(), APInt(
            32,
            tf->getClass()->getAttrOffset("vpointer"),
            true)
        ));

        Value* VThis = *argv.begin();
        Value* pointeur_vers_vtable = Builder->CreateGEP(
            VThis,
            ind.begin(),
            ind.end(),
            "p_vtable"
        );

        ind.clear();
        ind.push_back(ConstantInt::get(getGlobalContext(), APInt(32, 0, true)));

        Value* pointeur_vers_methode = Builder->CreateGEP(
            Builder->CreateLoad(pointeur_vers_vtable),
            ConstantInt::get(
                getGlobalContext(), APInt(32, vmOffset, true)
            ),
            "p_method"
            // ind.begin(),
            // ind.end()
        );

        pointeur_vers_methode = Builder->CreateLoad(pointeur_vers_methode);

        //cout << "#### " << tf->getType() << endl;
        Value* pointeur_caste_vers_fonction = Builder->CreateBitCast(
            pointeur_vers_methode,
            PointerType::get(FunctionType::get(type2llvm(tf->getType()), arg_types, false), 0)
            //FunctionType::get(type2llvm(dynamic_cast<TypeFunction*>(tf->getType())->getType()), arg_types, false)
        );

        //pointeur_caste_vers_fonction = this->module->getFunction(tf->getName());
        val_stack.push_back(Builder->CreateCall(pointeur_caste_vers_fonction, argv.begin(), argv.end()));
    }
    else
    {
        val_stack.push_back(Builder->CreateCall(CalleeF, argv.begin(), argv.end()));
    }
}

void VisitorNodeLlvm::visit(ExprSymbol *n) {
    Value *v = locals[n->getName()];
    if (v == 0)
    {
        v = this->module->getGlobalVariable(n->getName());
    }
    if (v == 0)
    {
        throw __FILE__ "(" QUOTE(__LINE__) "): Value " + n->getName() + " not in locals nor globals.";
    }

    if (this->no_load)
    {
        val_stack.push_back(v);
    }
    else
    {
        val_stack.push_back(Builder->CreateLoad(v, n->getName()));
    }
    this->no_load = false;
}

void VisitorNodeLlvm::visit(StmExpr *n) {
    n->getExpr()->accept(*this);
    val_stack.pop_back();
}

void VisitorNodeLlvm::visit(StmIf *n) {
    bool is_false = n->getOnfalse() ? true : false;
    Function *cur_func = current_func.back();
    BasicBlock *IfTrue = BasicBlock::Create(getGlobalContext(), "if_true", cur_func);
    BasicBlock *IfFalse;
    if (is_false)
        IfFalse = BasicBlock::Create(getGlobalContext(), "if_false");
    BasicBlock *IfEnd = BasicBlock::Create(getGlobalContext(), "if_end");

    n->getCondition()->accept(*this);
    Value* Cond = val_stack.back();
    val_stack.pop_back();

    if (is_false)
        Builder->CreateCondBr(Cond, IfTrue, IfFalse);
    else
        Builder->CreateCondBr(Cond, IfTrue, IfEnd);

    Builder->SetInsertPoint(IfTrue);

    n->getOntrue()->accept(*this);
    Builder->CreateBr(IfEnd);

    if (is_false)
    {
        cur_func->getBasicBlockList().push_back(IfFalse);
        Builder->SetInsertPoint(IfFalse);
        n->getOnfalse()->accept(*this);
        Builder->CreateBr(IfEnd);
    }

    cur_func->getBasicBlockList().push_back(IfEnd);
    Builder->SetInsertPoint(IfEnd);
}

void VisitorNodeLlvm::visit(StmWhile *n) {
    // Create blocks
    Function *cur_func      = current_func.back();
    BasicBlock *WhileBB     = BasicBlock::Create(getGlobalContext(), "while", cur_func);
    BasicBlock *WhileBodyBB = BasicBlock::Create(getGlobalContext(), "while_body");
    BasicBlock *WhileEndBB  = BasicBlock::Create(getGlobalContext(), "while_end");

    // Put block where to break or continue
    block_break.push_back(WhileEndBB);
    block_continue.push_back(WhileBB);

    // Enter in the loop
    Builder->CreateBr(WhileBB);

    // Set insert point in while loop
    Builder->SetInsertPoint(WhileBB);

    // Get condition Value
    n->getCondition()->accept(*this);
    Value* Cond = val_stack.back();
    val_stack.pop_back();

    // Create branch on true
    Builder->CreateCondBr(Cond, WhileBodyBB, WhileEndBB);

    // While Body Block
    cur_func->getBasicBlockList().push_back(WhileBodyBB);
    Builder->SetInsertPoint(WhileBodyBB);

    // Visit while body
    n->getBody()->accept(*this);

    Builder->CreateBr(WhileBB);


    // Set insert point after while loop
    cur_func->getBasicBlockList().push_back(WhileEndBB);
    Builder->SetInsertPoint(WhileEndBB);

    // Remove last block where to break or continue
    block_break.pop_back();
    block_continue.pop_back();
}

void VisitorNodeLlvm::visit(StmDo *n) {
    // Create blocks
    Function *cur_func      = current_func.back();
    BasicBlock *DoBB     = BasicBlock::Create(getGlobalContext(), "do", cur_func);
    BasicBlock *DoEndBB  = BasicBlock::Create(getGlobalContext(), "do_end");

    // Put block where to break or continue
    block_break.push_back(DoEndBB);
    block_continue.push_back(DoBB);

    // Enter in the loop
    Builder->CreateBr(DoBB);

    // Set insert point in do loop
    Builder->SetInsertPoint(DoBB);

    // Visit do body
    n->getBody()->accept(*this);

    // Get condition Value
    n->getCondition()->accept(*this);
    Value* Cond = val_stack.back();
    val_stack.pop_back();

    // Create branch on true
    Builder->CreateCondBr(Cond, DoBB, DoEndBB);

    // Set insert point after do loop
    cur_func->getBasicBlockList().push_back(DoEndBB);
    Builder->SetInsertPoint(DoEndBB);

    // Remove last block where to break or continue
    block_break.pop_back();
    block_continue.pop_back();
}

void VisitorNodeLlvm::visit(StmFor *n) {
    // Create blocks
    Function *cur_func     = current_func.back();
    BasicBlock *ForBeginBB = BasicBlock::Create(getGlobalContext(), "for", cur_func);
    BasicBlock *ForBodyBB  = BasicBlock::Create(getGlobalContext(), "for_body");
    BasicBlock *ForEndBB   = BasicBlock::Create(getGlobalContext(), "for_end");

    // Put block where to break or continue
    block_break.push_back(ForEndBB);
    block_continue.push_back(ForBeginBB);

    // Evaluate initial
    n->getInitial()->accept(*this);
    val_stack.pop_back();

    // Enter in the loop
    Builder->CreateBr(ForBeginBB);

    // Set insert point in for loop
    Builder->SetInsertPoint(ForBeginBB);

    // Get condition Value
    n->getCondition()->accept(*this);
    Value* Cond = val_stack.back();
    val_stack.pop_back();

    // Create branch on true
    Builder->CreateCondBr(Cond, ForBodyBB, ForEndBB);

    // For Body Block
    cur_func->getBasicBlockList().push_back(ForBodyBB);
    Builder->SetInsertPoint(ForBodyBB);

    // Visit for body
    n->getBody()->accept(*this);

    // Visit loop expression
    n->getLoop()->accept(*this);
    val_stack.pop_back();

    // Jump to begining of loop
    Builder->CreateBr(ForBeginBB);

    // Set insert point after for loop
    cur_func->getBasicBlockList().push_back(ForEndBB);
    Builder->SetInsertPoint(ForEndBB);

    // Remove last block where to break or continue
    block_break.pop_back();
    block_continue.pop_back();
}

void VisitorNodeLlvm::visit(StmBlock *n) {
    std::vector<Stm*>* stm = n->getStatements();
    if (!n->getStatements()->empty())
    {
        // For each statement in block, visit it
        for (std::vector<Stm*>::iterator it = stm->begin(); it != stm->end(); it++)
        {
            (*it)->accept(*this);
        }
    }
}

void VisitorNodeLlvm::visit(StmReturn *n) {
    if (n->getValue())
    {
        n->getValue()->accept(*this);
        Builder->CreateRet(val_stack.back());
    }
    else
    {
        Builder->CreateRetVoid();
    }
    // Create new block after return, do that it is the terminate block
    BasicBlock* RetBB = BasicBlock::Create(getGlobalContext(), "next_ret");
    //this->current_func.getBasicBlockList().push_back(RetBB);
    Builder->SetInsertPoint(RetBB);
}

void VisitorNodeLlvm::visit(StmSwitch *n) {
    // Evaluate condition
    n->getCondition()->accept(*this);
    Value* condition = val_stack.back();
    val_stack.pop_back();

    // Get current function to write blocks to
    Function* cur_func = current_func.back();

    // Create needed blocks
    BasicBlock* DefaultBB = BasicBlock::Create(getGlobalContext(), "switch_default");
    BasicBlock* SwitchContinueBB = BasicBlock::Create(getGlobalContext(), "switch_end");

    // Push block where to go on break statement
    this->block_break.push_back(SwitchContinueBB);

    // Create switch instruction
    SwitchInst* si = Builder->CreateSwitch(condition, DefaultBB, n->getCases()->size());

    // Add case blocks
    BasicBlock* CaseBB = 0;
    BasicBlock* NextCaseBB = 0;
    std::map<long, Stm*>::iterator it;
    it = n->getCases()->begin();
    int case_num = 0;
    int case_index = 0; // Counter of case statements processed,to put default statement
    bool default_passed = false;    // This flag is set if default is already passed
    while (it != n->getCases()->end())
    {
        // Set case as next case, if null, create one.
        if (NextCaseBB == 0)
            CaseBB = BasicBlock::Create(getGlobalContext(), "switch_case");
        else
            CaseBB = NextCaseBB;

        // If current position is default, write it
        if (case_index == n->getDefaultPosition())
        {
            // Evaluate default block, it is created even if is null, but only branch to end of switch
            cur_func->getBasicBlockList().push_back(DefaultBB);
            Builder->SetInsertPoint(DefaultBB);
            if (n->getDefault())
            {
                n->getDefault()->accept(*this);
            }
            Builder->CreateBr(CaseBB);
            default_passed = true;
        }

        // Put case block and write into
        cur_func->getBasicBlockList().push_back(CaseBB);
        Builder->SetInsertPoint(CaseBB);
        (*it).second->accept(*this);
        case_num = (*it).first;

        // Get next case
        ++it;
        // If there is no case left, next block to branch is end of switch
        if (it == n->getCases()->end())
        {
            NextCaseBB = default_passed ? SwitchContinueBB : DefaultBB;
        }
        else
        {
            NextCaseBB = BasicBlock::Create(getGlobalContext(), "switch_case");
        }
        // Increment case block index
        case_index++;
        // Branch to next case block, end of switch, or default
        if (case_index == n->getDefaultPosition())
        {
            Builder->CreateBr(DefaultBB);
        }
        else
        {
            Builder->CreateBr(NextCaseBB);
        }
        // Add case to the switch statement
        si->addCase(ConstantInt::get(getGlobalContext(), APInt(n->getCondition()->getType()->stackSize()*8, case_num, true)), CaseBB);
    }

    // If current position is default, write it
    if (!default_passed)
    {
        // Evaluate default block, it is created even if is null, but only branch to end of switch
        cur_func->getBasicBlockList().push_back(DefaultBB);
        Builder->SetInsertPoint(DefaultBB);
        if (n->getDefault())
        {
            n->getDefault()->accept(*this);
        }
        Builder->CreateBr(SwitchContinueBB);
        default_passed = true;
    }

    // Put end of switch label, break statements jump to it.
    cur_func->getBasicBlockList().push_back(SwitchContinueBB);
    Builder->SetInsertPoint(SwitchContinueBB);

    // Release last block where break would branch
    this->block_break.pop_back();
}

void VisitorNodeLlvm::visit(StmBreak *n) {
    // Create jump to block in stack
    Builder->CreateBr(this->block_break.back());
    // Crate new block for next instructions
    BasicBlock* b = BasicBlock::Create(getGlobalContext(), "break_next");
    // New instructions are written to new block
    // TODO Look after unreachable code
    current_func.back()->getBasicBlockList().push_back(b);
    Builder->SetInsertPoint(b);
}

void VisitorNodeLlvm::visit(StmContinue *n) {
    // Create jump to block in stack
    Builder->CreateBr(this->block_continue.back());
    // Crate new block for next instructions
    BasicBlock* b = BasicBlock::Create(getGlobalContext(), "continue_next");
    // New instructions are written to new block
    // TODO Look after unreachable code
    current_func.back()->getBasicBlockList().push_back(b);
    Builder->SetInsertPoint(b);
}

AllocaInst * VisitorNodeLlvm::CreateEntryBlockAlloca(Function *TheFunction, const std::string &VarName, ::Type* t) {
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(type2llvm(t), 0, VarName.c_str());
}

void VisitorNodeLlvm::visit(StmDecl *n) {
    /** TODO
        If body is wrong, erase function from parent.
        Manage function redefinition.
        Manage function overloading.
    */

    if (n->isVar())
    {
        if (current_func.size() == 1)   // Check if we are in the __main__ function
        {
            // Declare a global variable
            GlobalVariable *g = new GlobalVariable(
                *this->module,
                type2llvm(n->getType()),
                false,
                GlobalValue::ExternalLinkage,
                ConstantAggregateZero::get(type2llvm(n->getType())),
                n->getName()
            );

            // Initial value
            if (n->getInitial())
            {
                n->getInitial()->accept(*this);
                Value *Variable = this->module->getGlobalVariable(n->getName());
                Builder->CreateStore(val_stack.back(), Variable);
                val_stack.pop_back();
            }
            // If type is an array, allocate memory on heap
            else if (n->getType()->isArray())
            {
                TypeArray* ta = dynamic_cast<TypeArray*>(n->getType());
                if (ta->getLength() > 0)
                {
                    Function *CalleeF = this->module->getFunction("cy_malloc");
                    std::vector<Value*> argv;

                    // Push amount of memory needed
                    argv.push_back(
                        ConstantInt::get(
                            getGlobalContext(),
                            APInt(
                                64,
                                ta->getLength()*this->targetData->getTypeAllocSize(
                                    type2llvm(ta->getType())
                                ),
                                true
                            )
                        )
                    );
                    Builder->CreateStore(
                        Builder->CreateBitCast(
                            Builder->CreateCall(CalleeF, argv.begin(), argv.end()), type2llvm(n->getType())
                        ), g
                    );
                }
            }
        }
        else
        {
            // Declare a local variable
            IRBuilder<> TmpB(&current_func.back()->getEntryBlock(), current_func.back()->getEntryBlock().begin());
            Value* alloca = TmpB.CreateAlloca(type2llvm(n->getType()), 0, n->getName());
            locals[n->getName()] = alloca;

            // If type is an array, allocate memory on heap
            if (n->getType()->isArray())
            {
                TypeArray* ta = dynamic_cast<TypeArray*>(n->getType());
                Function *CalleeF = this->module->getFunction("cy_malloc");
                std::vector<Value*> argv;

                // Push amount of memory needed
                argv.push_back(
                    ConstantInt::get(
                        getGlobalContext(),
                        APInt(
                            64,
                            ta->getLength()*this->targetData->getTypeAllocSize(
                                type2llvm(ta->getType())
                            ),
                            true
                        )
                    )
                );
                Builder->CreateStore(
                    Builder->CreateBitCast(
                        Builder->CreateCall(CalleeF, argv.begin(), argv.end()), type2llvm(n->getType())
                    ), alloca
                );
            }

            // If initial value, get it and affect it
            if (n->getInitial())
            {
                n->getInitial()->accept(*this);
                Builder->CreateStore(val_stack.back(), alloca);
                val_stack.pop_back();
            }
        }
    }
    else
    {
        // Get arguments type
        std::vector<const llvm::Type*> arg_type;
        std::vector< ::Argument*>::iterator it;
        for (it = n->getArgs()->begin(); it != n->getArgs()->end(); it++)
        {
            arg_type.push_back(type2llvm((*it)->getType()));
        }
        // Create function prototype
        FunctionType *FT = FunctionType::get(type2llvm(dynamic_cast<TypeFunction*>(n->getType())->getType()), arg_type, false);
        // Create function, using prototype, linkage type, identifier and module
        Function *F = Function::Create(FT, Function::ExternalLinkage, n->getName(), this->module);

        if (n->getBody())
        {
            // Create a new basic block to start insertion into.
            BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
            // Push the current insert point
            //block_stack.push_back(BB);
            block_stack.push_back(Builder->GetInsertBlock());
            // Set code insert point of the builder in the function
            Builder->SetInsertPoint(BB);
            // Set the current function
            current_func.push_back(F);
            // Remove all local variables
            locals.clear();
        }

        // Get arguments name
        unsigned Idx = 0;
        std::vector< ::Argument*> args = *n->getArgs();
        for (Function::arg_iterator AI = F->arg_begin(); Idx != arg_type.size(); ++AI, ++Idx)
        {
            if (n->getBody())
            {
                // Create an alloca for this variable.
                AllocaInst *Alloca = CreateEntryBlockAlloca(F, args[Idx]->getName(), args[Idx]->getType());
                // Store the initial value into the alloca.
                Builder->CreateStore(AI, Alloca);
                // Add arguments to variable symbol table.
                locals[args[Idx]->getName()] = Alloca;
            }

            // Set the name of argument
            AI->setName(args[Idx]->getName());
        }

        if (n->getBody())
        {
            // Visit function body
            n->getBody()->accept(*this);
            // Verify function's integrity
            if (this->verify)
                verifyFunction(*F);

            // Remove all local variables
            locals.clear();
            if (block_stack.back())
                Builder->SetInsertPoint(block_stack.back());
            block_stack.pop_back();
            if (!current_func.empty())
                current_func.pop_back();
        }
    }
}

void VisitorNodeLlvm::visit(StmClass* n) {
    std::vector<cy::Function*>::iterator it;
    unsigned Idx;
    Function::arg_iterator AI;
    // Create function prototypes
    for (it = n->getClass()->getMethods()->begin(); it != n->getClass()->getMethods()->end(); it++)
    {
        // Create a vector of argument llvm-type
        std::vector<const llvm::Type*> arg_type;
        std::vector< ::Argument*>::iterator it_arg;
        if ((*it)->getArgs())
        {
            for (it_arg = (*it)->getArgs()->begin(); it_arg != (*it)->getArgs()->end(); it_arg++)
            {
                arg_type.push_back(type2llvm((*it_arg)->getType()));
            }
        }
        // Create function prototype
        FunctionType *FT = FunctionType::get(type2llvm(dynamic_cast<TypeFunction*>((*it)->getType())->getType()), arg_type, false);
        // Create function, using prototype, linkage type, identifier and module
        Function *F = Function::Create(FT, Function::ExternalLinkage, (*it)->getMangledName(), this->module);

        // Set arguments name
        if ((*it)->getArgs())
        {
            std::vector< ::Argument*> args = *(*it)->getArgs();
            for ((AI = F->arg_begin()), Idx = 0; Idx != arg_type.size(); ++AI, ++Idx)
            {
                // Set the name of argument
                AI->setName(args[Idx]->getName());
            }
        }
    }

    // Create function bodies
    for (it = n->getClass()->getMethods()->begin(); it != n->getClass()->getMethods()->end(); it++)
    {
        // Get function with name
        Function *F = this->module->getFunction((*it)->getMangledName());

        // Create basic block for function entry, push it a write into
        BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", F);
        block_stack.push_back(Builder->GetInsertBlock());
        Builder->SetInsertPoint(BB);
        // Set the current function
        current_func.push_back(F);

        // For each arguments, create allocation and put name in locals
        locals.clear();
        if ((*it)->getArgs())
        {
            std::vector< ::Argument*> args = *(*it)->getArgs();
            for ((AI = F->arg_begin()), Idx = 0; Idx != F->arg_size(); ++AI, ++Idx)
            {
                // Create an alloca for this variable.
                AllocaInst *Alloca = CreateEntryBlockAlloca(F, args[Idx]->getName(), args[Idx]->getType());
                // Store the initial value into the alloca.
                Builder->CreateStore(AI, Alloca);
                // Add arguments to variable symbol table.
                locals[args[Idx]->getName()] = Alloca;
            }
        }

        // Visit function body
        (*it)->getBody()->accept(*this);
        // Verify function's integrity
        if (this->verify)
            verifyFunction(*F);

        if (block_stack.back())
            Builder->SetInsertPoint(block_stack.back());
        block_stack.pop_back();
        if (!current_func.empty())
            current_func.pop_back();
    }
    // Create VTable in LLVM
    //n->getClass()->dump();
    if (n->getClass()->hasVTable())
    {
        //n->getClass()->dumpVTable();
        std::vector<cy::Function*>* vms = n->getClass()->getVirtualMethods();
        std::vector<cy::Function*>::iterator it;

        std::vector<Constant*> methods_vector;
        //llvm::ArrayType* lft = ArrayType::get(FunctionType::get(llvm::Type::getVoidTy(this->module->getContext()), false), vms->size());
        llvm::ArrayType* lft = ArrayType::get(PointerType::get(llvm::Type::getInt8Ty(getGlobalContext()),0), vms->size());

        for (it = vms->begin(); it != vms->end(); it++)
        {
            std::vector< ::Argument*>::iterator itt;
            std::vector<const llvm::Type*> llvmtypes;
            for (itt = (*it)->getArgs()->begin(); itt != (*it)->getArgs()->end(); itt++)
            {
                llvmtypes.push_back(type2llvm((*itt)->getType()));
            }
            // TODO TypeFunction of a Function should have argument types
            //lft = ArrayType::get(FunctionType::get(type2llvm(tr), llvmtypes, false), vms->size());
            methods_vector.push_back(
                ConstantExpr::getCast(
                    Instruction::BitCast,
                    this->module->getFunction((*it)->getMangledName()),
                    type2llvm(new TypeArray(TypePrimary::getByte()))
                )
            );
        }

        // Global variable containing pointer to methods
        //GlobalVariable *g = new GlobalVariable(
        new GlobalVariable(
            *this->module,
            lft,
            false,
            GlobalValue::ExternalLinkage,
            ConstantArray::get(lft, methods_vector),
            n->getClass()->getName() + "_vtable"
        );
    }
}

void VisitorNodeLlvm::visit(ExprObject* n) {
    // Create alloca where object is
    AllocaInst* ai_object = Builder->CreateAlloca(type2llvm(n->getType()), 0);
    TypeClass* tc = dynamic_cast<TypeClass*>(n->getType());

    // Allocate memory for object
    std::vector<Value*> argv;
    // Push amount of memory needed
    argv.push_back(
        ConstantInt::get(
            getGlobalContext(),
            APInt(
                64,
                this->targetData->getTypeAllocSize(
                    type2llvm(n->getType(), true)
                ),
                true
            )
        )
    );

    // Store allocated memory on allocainst
    Builder->CreateStore(
        Builder->CreateBitCast(
            Builder->CreateCall(
                this->module->getFunction("cy_malloc"),
                argv.begin(),
                argv.end()
            ),
            type2llvm(n->getType())
        ),
        ai_object
    );


    // Assign pointer to vtable in first attribute of object if it has a vtable attribute
    //cout << this->module->getGlobalVariable(tc->getClass()->getName() + "_vtable") << endl;
    if (tc->getClass()->hasVTable())
    {
        std::vector<Value*> ind;
        ind.push_back(ConstantInt::get(getGlobalContext(), APInt(32, 0, true)));
        ind.push_back(ConstantInt::get(getGlobalContext(), APInt(
            32,
            tc->getClass()->getAttrOffset("vpointer"),
            true)
        ));
        Builder->CreateStore(
            Builder->CreateBitCast(
                this->module->getGlobalVariable(tc->getClass()->getName() + "_vtable"),
                PointerType::get(type2llvm(new TypeArray(TypePrimary::getByte())), 0)
            ),
            Builder->CreateGEP(
                Builder->CreateLoad(ai_object),
                ind.begin(),
                ind.end()
            )
        );
    }

    // Load object on the stack
    val_stack.push_back(Builder->CreateLoad(ai_object, tc->getClass()->getName() + "_object"));
}
