//
// Created by 邱泽鸿 on 2021/6/15.
//

#pragma once

#include <iostream>
#include <sstream>
#include <stack>
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



namespace Typing
{   // 提前声明Typing::Node类
    class Node;
};
namespace AST
{   // 提前声明AST::Node类
    class Node;
}

class Interpreter; // 提前声明Interpreter类
class ST; // 提前声明符号表类

class CodeGenerator
{
public:
    // llvm 初始化
    static llvm::LLVMContext Context;
    static llvm::IRBuilder<> Builder;
    llvm::Module* Module;

    // 全局变量
    // <名字，对应地址>
    std::map<std::string, llvm::Value*> GlobalVariables;
    // 常量
    std::map<std::string, llvm::Value*> GlobalConst;
    // 函数参数列表
    // 一个函数内部能够访问的变量只有GlobalVariable以及栈顶的Arguments
    std::stack<std::map<std::string, llvm::Value*>> ArgumentsStack;

    // I/O的输入参数
    std::vector<llvm::Value*> IOArguments;
public:
    CodeGenerator()
    {
        Module = new llvm::Module("main", Context);
        setupIO();
    }
    void setupGlobal(ST* SymbolTable);
    inline void setupIO() // 设置printf和scanf函数
    {
        auto ArgumentsType = std::vector<llvm::Type*>{llvm::Type::getInt8PtrTy(Context)};
        // 向Module中插入printf函数
        llvm::Function::Create(
                llvm::FunctionType::get(Builder.getInt32Ty(), ArgumentsType, true),
                llvm::Function::ExternalLinkage,
                "printf", // Rmk: 名字不能改
                Module
        );
        // 向Module中插入scanf函数
        llvm::Function::Create(
                llvm::FunctionType::get(Builder.getInt32Ty(), ArgumentsType, true),
                llvm::Function::ExternalLinkage,
                "scanf",
                Module
        );
    }
    inline void callWrite(bool newLine, const std::string& Format, const std::vector<llvm::Value*>& Params)
    {
        IOArguments.clear();
        IOArguments.emplace_back(Builder.CreateGlobalStringPtr((newLine) ? Format + std::string("\n") : Format));
        IOArguments.insert(IOArguments.end(), Params.begin(), Params.end());
        Builder.CreateCall(
                Module->getFunction("printf"),
                IOArguments
        );
    }
    inline void callRead(const std::string& Format, const std::vector<llvm::Value*>& Params)
    {
        IOArguments.clear();
        IOArguments.emplace_back(Builder.CreateGlobalStringPtr(Format));
        IOArguments.insert(IOArguments.end(), Params.begin(), Params.end());
        Builder.CreateCall(
                Module->getFunction("scanf"),
                IOArguments
        );
    }
    inline void callWrite(bool newLine, const std::string& Format, int Number, ...)
    {
        IOArguments.clear();
        IOArguments.emplace_back(Builder.CreateGlobalStringPtr(newLine ? (Format + std::string ("\n")) : Format));
        va_list ap;
        va_start(ap, Number);
        for (int i = 0;i < Number; ++i)
        {
            IOArguments.emplace_back(va_arg(ap, llvm::Value*));
        }
        va_end(ap);
        Builder.CreateCall(
            Module->getFunction("printf"),
            IOArguments
        );
    }
    inline void callRead(const std::string& Format, int Number, ...)
    {
        IOArguments.clear();
        IOArguments.emplace_back(Builder.CreateGlobalStringPtr(Format));
        va_list ap;
        va_start(ap, Number);
        for (int i = 0;i < Number; ++i)
        {
            IOArguments.emplace_back(va_arg(ap, llvm::Value*));
        }
        va_end(ap);
        Builder.CreateCall(
                Module->getFunction("scanf"),
                IOArguments
        );
    }
    // 把Typing::Node类转为llvm::Type类
    static llvm::Type* toLLVM(Typing::Node* tNode);
    void execute(const Interpreter* ipt, std::ofstream& Out);
    llvm::Value* genCode(AST::Node* ASTNode, bool getVarByAddr);
};