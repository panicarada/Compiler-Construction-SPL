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



#include "AST.hpp"
#include "Typing.hpp"

class CodeGenerator
{
private:
    static llvm::LLVMContext Context;
    static llvm::IRBuilder<> Builder;
    std::stringstream Code;
public:
    CodeGenerator()
    {

    }
    void genCode(AST::Node* p);
    // 把AST结点转为llvm类型
    static llvm::Type* toLLVMType(AST::Node* node);
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