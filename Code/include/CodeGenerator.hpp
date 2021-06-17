//
// Created by 邱泽鸿 on 2021/6/15.
//

#pragma once

#include <iostream>
#include <sstream>
#include <stdarg.h>


#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/ValueSymbolTable.h>

#include "Typing.hpp"


// 提前声明Interpreter类
class Interpreter;
namespace CodeGeneration
{
    struct BasicType
    {
        int Id = 0;
        llvm::Type* Type;
        llvm::Constant* InitConstant;
        BasicType(llvm::Type* Type, llvm::Constant* InitConstant, int Id)
            : Type(Type), InitConstant(InitConstant), Id(Id){}
    };
    struct VarType
    {
        std::string Name;   // 变量名
        llvm::Value* Addr;  // 指针地址
        BasicType* refType;    // 指针指向的类型
        VarType(const std::string& Name, llvm::Value* Addr, BasicType* Type)
            : Name(Name), Addr(Addr), refType(Type){}
    };
    struct ArrayType : public BasicType
    {
        llvm::ConstantInt* LowerBound;
        llvm::ConstantInt* UpperBound;
        ArrayType(llvm::ArrayType* Type, llvm::ConstantInt* LowerBound, llvm::ConstantInt* UpperBound, llvm::Constant* Init)
            : BasicType(Type, Init, 1), LowerBound(LowerBound), UpperBound(UpperBound){}
    };
    struct StructType : public BasicType
    {
        std::vector<VarType*> Members; // 指针指向成员
        StructType(llvm::StructType* Type, std::vector<VarType*>& Members, llvm::Constant* Init)
            : BasicType(Type, Init, 2), Members(Members){}
        int getIndex(const std::string& Name)
        {
            auto it = std::find_if(Members.begin(), Members.end(), [&](VarType* Member) -> bool{
                return Member->Name == Name;
            });
            return (it == Members.end()) ? -1 : it - Members.begin();
        }
    };

    class CodeBlock
    {
    public:
        std::map<std::string, llvm::Constant*> Constants;
        std::map<std::string, BasicType*> Types;
        std::map<std::string, VarType*> Vars;

        std::map<int, llvm::BasicBlock*> Labels;
    public:
        inline VarType* getVar(const std::string& Name) const
        {
            auto it = Vars.find(Name);
            return (it == Vars.end()) ? nullptr : it->second;
        }
        ~CodeBlock()
        {

        }
    };
}


namespace AST
{   // 提前声明AST类
    class Node;
};
class CodeGenerator
{
public:
    // llvm 初始化
    static llvm::LLVMContext Context;
    static llvm::IRBuilder<> Builder;


    llvm::Module* Module;

    llvm::Function* mainFunction;   // 主函数
    llvm::Function* writeFunction;  // write函数
    llvm::Function* readFunction;   // read函数
    bool isGlobal = false; // 是否是全局的定义
    bool isVar    = false; // 是否是引用（指针）

    std::vector<CodeGeneration::CodeBlock*> CodeBlockList;

private:
    std::stringstream Code;
public:
    CodeGenerator()
    {
        Module = new llvm::Module("main", Context);
    }
    void genCode_init(Interpreter* ipt);
    llvm::Value* genCode(AST::Node* node);
    void setupIO();
    inline CodeGeneration::VarType* getVar(const std::string& Name)
    {
        for (auto CodeBlock = CodeBlockList.rbegin(); CodeBlock != CodeBlockList.rend(); ++CodeBlock)
        {
            auto var = (*CodeBlock)->getVar(Name);
            if (var)
                return var;
        }
        raiseError("没有找到对应var类型");
        return nullptr;
    }
private:
    inline void emitCode(int Number, ...)
    {   // 生成一行代码
        va_list ap;
        va_start(ap, Number);
        for (int i = 0;i < Number; ++i)
        {
            Code << va_arg(ap, char*) << " ";
        }
        Code << std::endl;
    }
};