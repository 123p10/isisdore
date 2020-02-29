#ifndef CODE_GEN_H
#define CODE_GEN_H
#include "../AST/ASTNodes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "../JIT/KaleidoscopeJIT.h"
#include "../types/type_manager.h"
class PrototypeAST;
class TypeManager;
struct Variable
{
    llvm::AllocaInst *value;
    llvm::Type *type;
};
struct Argument
{
    llvm::Type * type;
    std::string name;
};
class CodeGenerator{
    public:
        TypeManager * typeManager;
        void initPrecedence();
        std::map<std::string, int> BinopPrecedence;
        std::unique_ptr<llvm::Module> *TheModule;
        llvm::LLVMContext *TheContext;
        llvm::IRBuilder<> *Builder;
        std::map<std::string, Variable> NamedValues;
        std::unique_ptr<llvm::legacy::FunctionPassManager> *TheFPM;
        std::unique_ptr<llvm::orc::KaleidoscopeJIT> *TheJIT;
        std::map<std::string, std::unique_ptr<PrototypeAST>> *FunctionProtos;
        
        llvm::Function *getFunction(std::string Name);
        void InitializeModuleAndPassManager(void);
        llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction,llvm::Type * type, const std::string &VarName);
        llvm::Value * operator_instructions(std::string instruction, llvm::Value *L, llvm::Value *R);
        CodeGenerator();
        ~CodeGenerator();

};
llvm::Value *LogErrorV(const char *Str);
#endif