; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [26 x i8] c"please enter your steps: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@string_tmp_.2 = private unnamed_addr constant [5 x i8] c"pi: \00", align 1
@string_tmp_.3 = private unnamed_addr constant [9 x i8] c"\09steps: \00", align 1
@string_tmp_.4 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@format.5 = private unnamed_addr constant [15 x i8] c"%s%lf%s%d%s%d\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %index = alloca i32, align 4
  %factor = alloca double, align 8
  %steps = alloca i32, align 4
  %temp = alloca double, align 8
  %pi = alloca double, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %steps)
  store i32 0, i32* %index, align 4
  store double 0.000000e+00, double* %pi, align 8
  store double 1.000000e+00, double* %factor, align 8
  %steps1 = load i32, i32* %steps, align 4
  %isub_tmp_ = sub i32 %steps1, 1
  store i32 0, i32* %index, align 4
  br label %loop_condition

loop_condition:                                   ; preds = %loop_body, %main_entry
  %index2 = load i32, i32* %index, align 4
  %ile_tmp_ = icmp sle i32 %index2, %isub_tmp_
  br i1 %ile_tmp_, label %loop_body, label %after

loop_body:                                        ; preds = %loop_condition
  %index3 = load i32, i32* %index, align 4
  %imul_tmp_ = mul i32 8, %index3
  %si2double_tmp_ = sitofp i32 %imul_tmp_ to double
  store double %si2double_tmp_, double* %temp, align 8
  %pi4 = load double, double* %pi, align 8
  %factor5 = load double, double* %factor, align 8
  %temp6 = load double, double* %temp, align 8
  %fadd_tmp_ = fadd double %temp6, 1.000000e+00
  %fdiv_tmp_ = fdiv double 4.000000e+00, %fadd_tmp_
  %temp7 = load double, double* %temp, align 8
  %fadd_tmp_8 = fadd double %temp7, 4.000000e+00
  %fdiv_tmp_9 = fdiv double 2.000000e+00, %fadd_tmp_8
  %fsub_tmp_ = fsub double %fdiv_tmp_, %fdiv_tmp_9
  %temp10 = load double, double* %temp, align 8
  %fadd_tmp_11 = fadd double %temp10, 5.000000e+00
  %fdiv_tmp_12 = fdiv double 1.000000e+00, %fadd_tmp_11
  %fsub_tmp_13 = fsub double %fsub_tmp_, %fdiv_tmp_12
  %temp14 = load double, double* %temp, align 8
  %fadd_tmp_15 = fadd double %temp14, 6.000000e+00
  %fdiv_tmp_16 = fdiv double 1.000000e+00, %fadd_tmp_15
  %fsub_tmp_17 = fsub double %fsub_tmp_13, %fdiv_tmp_16
  %fmul_tmp_ = fmul double %factor5, %fsub_tmp_17
  %fadd_tmp_18 = fadd double %pi4, %fmul_tmp_
  store double %fadd_tmp_18, double* %pi, align 8
  %factor19 = load double, double* %factor, align 8
  %fdiv_tmp_20 = fdiv double %factor19, 1.600000e+01
  store double %fdiv_tmp_20, double* %factor, align 8
  %pi21 = load double, double* %pi, align 8
  %index22 = load i32, i32* %index, align 4
  %iadd_tmp_ = add i32 %index22, 1
  %steps23 = load i32, i32* %steps, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @format.5, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @string_tmp_.2, i32 0, i32 0), double %pi21, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @string_tmp_.3, i32 0, i32 0), i32 %iadd_tmp_, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @string_tmp_.4, i32 0, i32 0), i32 %steps23)
  %iadd_tmp_24 = add i32 %index2, 1
  store i32 %iadd_tmp_24, i32* %index, align 4
  br label %loop_condition

after:                                            ; preds = %loop_condition
  ret void
}
