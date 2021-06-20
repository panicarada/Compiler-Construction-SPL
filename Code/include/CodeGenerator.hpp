//
// Created by 邱泽鸿 on 2021/6/15.
//

#pragma once

#include <iostream>
#include <sstream>
#include <stack>
#include <set>
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
    class functNode;
    class procNode;
    class recordNode;
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

    // 全局符号表
    ST* SymbolTable;

    // 全局变量
    // <名字，对应地址>
    std::map<std::string, llvm::Value*> GlobalVariables;
    // 常量
    // <名字，对应值>
    std::map<std::string, llvm::Value*> GlobalConst;
    // 函数参数列表
    // 一个函数内部能够访问的变量只有GlobalVariable以及栈顶的Arguments
    std::stack<std::map<std::string, llvm::Value*>> ArgumentsStack;

    // 结构体列表
    std::stack<std::map<std::string, Typing::recordNode*>> RecordsStack;

    // 函数集合，用于保存函数声明，最后再实现
    std::set<std::pair<llvm::Function*, Typing::functNode*>> FunctionSet;
    std::set<std::pair<llvm::Function*, Typing::procNode*>> ProcedureSet;

    // 调用函数的输入参数
    std::vector<llvm::Value*> CallerArguments;

    // 被调用过的系统函数（之后需要定义）
    std::set<std::string> CalledSystemFunctions;
public:
    CodeGenerator()
    {
        Module = new llvm::Module("main", Context);
        setupIO();
    }
    void defineFunctions(); // 完成函数的定义
    void defineProcedures(); // 完成过程的定义

    void setupGlobal();
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
    inline void callWrite(bool newLine, const std::vector<llvm::Value*>& Params)
    {
        CallerArguments.clear();
        std::stringstream Format;

        for (const auto& it : Params)
        {
            auto* Param = dynamic_cast<llvm::Value*>(it);
            auto* Type = Param->getType();
            if (Type == Builder.getInt32Ty())
            { // integer
                Format << "%d";
            }
            else if (Type == Builder.getDoubleTy())
            { // real
                Format << "%lf";
            }
            else if (Type == Builder.getInt8Ty())
            { // char
                Format << "%c";
            }
            else if (Type == Builder.getInt1Ty())
            { // bool不存在，在输入前已经被cast到整数

            }
            else if (Type == Builder.getInt8PtrTy())
            { // string
                Format << "%s";
            }
        }
        if (newLine)
        {
            Format << std::endl;
        }
        CallerArguments.emplace_back(Builder.CreateGlobalStringPtr(Format.str(), "format"));
        CallerArguments.insert(CallerArguments.end(), Params.begin(), Params.end());
        Builder.CreateCall(
                Module->getFunction("printf"),
                CallerArguments
        );
    }
    inline void callRead(const std::vector<llvm::Value*>& Params)
    { // read格式为<read, 提示字符串, 待输入的参数>
        callWrite(false, {Params[0]});
        CallerArguments.clear();
        auto* ReadPtr = Params[1];
        auto* ReadType = ReadPtr->getType()->getPointerElementType(); // read param一定是指针
        if (ReadType == Builder.getInt32Ty())
        { // integer
            CallerArguments.emplace_back(Builder.CreateGlobalStringPtr("%d", "format"));
        }
        else if (ReadType == Builder.getDoubleTy())
        { // real
            CallerArguments.emplace_back(Builder.CreateGlobalStringPtr("%lf", "format"));
        }
        else if (ReadType == Builder.getInt8Ty())
        { // char
            CallerArguments.emplace_back(Builder.CreateGlobalStringPtr("%c", "format"));
        }
        else if (ReadType == Builder.getInt1Ty())
        { // boolean，输入时也只能用整数，之后再截取
            CallerArguments.emplace_back(Builder.CreateGlobalStringPtr("%d", "format"));
        }
        CallerArguments.emplace_back(ReadPtr);
        Builder.CreateCall(
                Module->getFunction("scanf"),
                CallerArguments
        );
    }
    // 把Typing::Node类转为llvm::Type类
    static llvm::Type* toLLVM(Typing::Node* tNode);
    void execute(const Interpreter* ipt, std::ofstream& Out);
    llvm::Value* genCode(AST::Node* ASTNode, bool getVarByAddr);
};