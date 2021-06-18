; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [19 x i8] c"Input your index: \00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@2 = private unnamed_addr constant [33 x i8] c"Index:%d\09Value:%.5f\09testBool:%d\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %value = alloca double, align 8
  %index = alloca i32, align 4
  %bool = alloca i1, align 1
  %testBool = alloca i1, align 1
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @0, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %index)
  %index1 = load i32, i32* %index, align 4
  %iadd_tmp_ = add i32 %index1, 3
  store i32 %iadd_tmp_, i32* %index, align 4
  %index2 = load i32, i32* %index, align 4
  %si2double_tmp_ = sitofp i32 %index2 to double
  %fadd_tmp_ = fadd double 0x400921FB4D12D84A, %si2double_tmp_
  %fmul_tmp_ = fmul double 0x400921FB4D12D84A, %fadd_tmp_
  %fdiv_tmp_ = fdiv double %fmul_tmp_, 1.440000e+01
  store double %fdiv_tmp_, double* %value, align 8
  store i1 false, i1* %testBool, align 1
  %index3 = load i32, i32* %index, align 4
  %value4 = load double, double* %value, align 8
  %testBool5 = load i1, i1* %testBool, align 1
  %bool2int_tmp_ = sext i1 %testBool5 to i32
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @2, i32 0, i32 0), i32 %index3, double %value4, i32 %bool2int_tmp_)
  ret void
}
