; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [26 x i8] c"Please enter the number: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@format.2 = private unnamed_addr constant [5 x i8] c"%lf\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %avg = alloca double, align 8
  %temp = alloca i32, align 4
  %count = alloca i32, align 4
  %total = alloca i32, align 4
  br label %loop

loop:                                             ; preds = %loop, %main_entry
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %temp)
  %total1 = load i32, i32* %total, align 4
  %temp2 = load i32, i32* %temp, align 4
  %iadd_tmp_ = add i32 %total1, %temp2
  store i32 %iadd_tmp_, i32* %total, align 4
  %count3 = load i32, i32* %count, align 4
  %iadd_tmp_4 = add i32 %count3, 1
  store i32 %iadd_tmp_4, i32* %count, align 4
  %temp5 = load i32, i32* %temp, align 4
  %ieq_tmp_ = icmp eq i32 %temp5, 0
  br i1 %ieq_tmp_, label %after, label %loop

after:                                            ; preds = %loop
  %count6 = load i32, i32* %count, align 4
  %isub_tmp_ = sub i32 %count6, 1
  store i32 %isub_tmp_, i32* %count, align 4
  %total7 = load i32, i32* %total, align 4
  %si2double_tmp_ = sitofp i32 %total7 to double
  %fmul_tmp_ = fmul double 1.000000e+00, %si2double_tmp_
  %count8 = load i32, i32* %count, align 4
  %si2double_tmp_9 = sitofp i32 %count8 to double
  %fdiv_tmp_ = fdiv double %fmul_tmp_, %si2double_tmp_9
  store double %fdiv_tmp_, double* %avg, align 8
  %avg10 = load double, double* %avg, align 8
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @format.2, i32 0, i32 0), double %avg10)
  ret void
}
