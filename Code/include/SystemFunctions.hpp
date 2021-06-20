//
// Created by 邱泽鸿 on 2021/6/19.
//

#pragma once

#include "CodeGenerator.hpp"

// 用来定义系统函数
namespace SystemFunctions
{
    void declare(const std::string& Name, llvm::IRBuilder<>& Builder, llvm::Module* Module)
    {
        if (Name == "odd")
        { // 判断整数输入是否为奇数
            llvm::Function::Create(
                llvm::FunctionType::get(Builder.getInt1Ty(), {Builder.getInt32Ty()}, true),
                llvm::GlobalValue::ExternalLinkage,
                Name,
                Module
            );
        }
        else if (Name == "iabs" || Name == "isqr")
        { // 单元整数，返回整数
            llvm::Function::Create(
                llvm::FunctionType::get(Builder.getInt32Ty(), {Builder.getInt32Ty()}, true),
                llvm::GlobalValue::ExternalLinkage,
                Name,
                Module
            );
        }
        else if (Name == "fabs" || Name == "fsqr" || Name == "sqrt")
        { // 单元浮点，返回浮点
            llvm::Function::Create(
                    llvm::FunctionType::get(Builder.getDoubleTy(), {Builder.getDoubleTy()}, true),
                    llvm::GlobalValue::ExternalLinkage,
                    Name,
                    Module
            );
        }
        else if (Name == "chr")
        { // 输入字符，输出整数
            llvm::Function::Create(
                    llvm::FunctionType::get(Builder.getInt8Ty(), {Builder.getInt32Ty()}, true),
                    llvm::GlobalValue::ExternalLinkage,
                    Name,
                    Module
            );
        }
    }

    void define(const std::string& Name, llvm::LLVMContext& Context, llvm::IRBuilder<>& Builder, const llvm::Module* Module)
    {
        llvm::Function* Function = Module->getFunction(Name);
        // 创建函数体代码区
        auto* FunctionBlock = llvm::BasicBlock::Create(Context, Function->getName(), Function);
        // 进入函数体代码区
        Builder.SetInsertPoint(FunctionBlock);

        auto* Input = dynamic_cast<llvm::Value*>(Function->arg_begin());
        llvm::Value* ret;
        if (Name == "chr")
        {   // 截取后八位即可
            Builder.CreateRet(Builder.CreateIntCast(Input, Builder.getInt8Ty(), false, "int_cast_tmp_"));
        }
        else if (Name == "isqr")
        {
            Builder.CreateRet(Builder.CreateMul(Input, Input, "imul_tmp_"));
        }
        else if (Name == "fsqr")
        {
            Builder.CreateRet(Builder.CreateFMul(Input, Input, "fmul_tmp_"));
        }
        else if (Name == "odd")
        {   // 截取最小位即可
            Builder.CreateRet(Builder.CreateIntCast(Input, Builder.getInt1Ty(), false, "int_cast_tmp_"));
        }
        else if (Name == "iabs")
        {
            ret = Builder.CreateAlloca(Builder.getInt32Ty(), nullptr, "ret_");
            auto* Condition = Builder.CreateICmp(llvm::ICmpInst::Predicate::ICMP_SLT, Input, llvm::ConstantInt::get(Builder.getInt32Ty(), 0), "ile_tmp_");
            auto* IFBlock = llvm::BasicBlock::Create(Context, "if_lt_0_", Builder.GetInsertBlock()->getParent());
            auto* ElseBlock = llvm::BasicBlock::Create(Context, "else_", Builder.GetInsertBlock()->getParent());
            auto* AfterBlock = llvm::BasicBlock::Create(Context, "after_", Builder.GetInsertBlock()->getParent());

            Builder.CreateCondBr(Condition, IFBlock, ElseBlock);
            Builder.SetInsertPoint(IFBlock);
            Builder.CreateStore(Builder.CreateNeg(Input, "neg_tmp_"), ret);
            Builder.CreateBr(AfterBlock);

            Builder.SetInsertPoint(ElseBlock);
            Builder.CreateStore(Input, ret);
            Builder.CreateBr(AfterBlock);

            Builder.SetInsertPoint(AfterBlock);
            Builder.CreateRet(Builder.CreateLoad(ret, "load_tmp_"));
        }
        else if (Name == "fabs")
        {
            ret = Builder.CreateAlloca(Builder.getDoubleTy(), nullptr, "ret_");

            auto* Condition = Builder.CreateFCmp(llvm::FCmpInst::Predicate::FCMP_OLT, Input, llvm::ConstantFP::get(Builder.getDoubleTy(), 0), "fle_tmp_");
            auto* IFBlock = llvm::BasicBlock::Create(Context, "if_lt_0_", Builder.GetInsertBlock()->getParent());
            auto* ElseBlock = llvm::BasicBlock::Create(Context, "else_", Builder.GetInsertBlock()->getParent());
            auto* AfterBlock = llvm::BasicBlock::Create(Context, "after_", Builder.GetInsertBlock()->getParent());

            Builder.CreateCondBr(Condition, IFBlock, ElseBlock);
            Builder.SetInsertPoint(IFBlock);
            Builder.CreateStore(Builder.CreateFNeg(Input, "fneg_tmp_"), ret);
            Builder.CreateBr(AfterBlock);

            Builder.SetInsertPoint(ElseBlock);
            Builder.CreateStore(Input, ret);
            Builder.CreateBr(AfterBlock);

            Builder.SetInsertPoint(AfterBlock);
            Builder.CreateRet(Builder.CreateLoad(ret, "load_tmp_"));
        }
        else if (Name == "sqrt")
        { // 平方根
            /* 牛顿法
             * double sqrt_(double x)
               {
                    double g=x;
                    while(ABS(g*g-x)>0.000001)
                    {
                        g=(g+x/g)/2;
                    }
                    return g;
               }
             */
            // 采用repeat until的写法
            ret = Builder.CreateAlloca(Builder.getDoubleTy(), nullptr, "ret_");
            Builder.CreateStore(Input, ret); // 首先ret <- x
            auto* LastRet = Builder.CreateLoad(ret);

            // 循环代码块
            auto* LoopBlock = llvm::BasicBlock::Create(Context, "loop_", Builder.GetInsertBlock()->getParent());
            // 跳出循环的代码块
            auto* AfterBlock = llvm::BasicBlock::Create(Context, "after_", Builder.GetInsertBlock()->getParent());

            // 进入循环体
            Builder.CreateBr(LoopBlock);
            Builder.SetInsertPoint(LoopBlock);
            // 计算ret <- (ret + ret / g) /2
            Builder.CreateStore(
                    Builder.CreateFDiv(Builder.CreateFAdd(LastRet, Builder.CreateFDiv(LastRet, Input, "fdiv_tmp_"), "fadd_tmp_"),
                                            llvm::ConstantFP::get(Builder.getDoubleTy(), 2.0)),
                    ret
            );
            LastRet = Builder.CreateLoad(ret);
            // 计算误差eps <- fabs(ret * ret - x)
            auto* eps = Builder.CreateCall(Module->getFunction("fabs"), {
                                    Builder.CreateFSub(Builder.CreateFMul(LastRet, LastRet, "fmul_tmp_"),
                                    Input,
                                   "fsub_tmp_")
            });
            // 判断条件eps <= EPS(0.00001)
            auto* Condition = Builder.CreateFCmp(llvm::FCmpInst::Predicate::FCMP_OLE, eps,
                                                 llvm::ConstantFP::get(Builder.getDoubleTy(), 0.00001),
                                                 "fle_tmp_");
            Builder.CreateCondBr(Condition, LoopBlock, AfterBlock);
            Builder.SetInsertPoint(AfterBlock);
            // 结束循环，返回值
            Builder.CreateRet(LastRet);
        }
    }
};