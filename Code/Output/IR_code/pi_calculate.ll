; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [26 x i8] c"please enter your steps: \00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@2 = private unnamed_addr constant [23 x i8] c"pi: %.20f\09steps:%d/%d\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %index = alloca i32, align 4
  %factor = alloca double, align 8
  %steps = alloca i32, align 4
  %temp = alloca double, align 8
  %pi = alloca double, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @0, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %steps)
  store i32 0, i32* %index, align 4
  store double 0.000000e+00, double* %pi, align 8
  store double 1.000000e+00, double* %factor, align 8
  br label %loop_condition

loop_condition:                                   ; preds = %loop_body, %main_entry
  %index1 = load i32, i32* %index, align 4
  %steps2 = load i32, i32* %steps, align 4
  %ilt_tmp_ = icmp slt i32 %index1, %steps2
  br i1 %ilt_tmp_, label %loop_body, label %after

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
  %index19 = load i32, i32* %index, align 4
  %iadd_tmp_ = add i32 %index19, 1
  store i32 %iadd_tmp_, i32* %index, align 4
  %factor20 = load double, double* %factor, align 8
  %fdiv_tmp_21 = fdiv double %factor20, 1.600000e+01
  store double %fdiv_tmp_21, double* %factor, align 8
  %pi22 = load double, double* %pi, align 8
  %index23 = load i32, i32* %index, align 4
  %steps24 = load i32, i32* %steps, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @2, i32 0, i32 0), double %pi22, i32 %index23, i32 %steps24)
  br label %loop_condition

after:                                            ; preds = %loop_condition
  ret void
}
