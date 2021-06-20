; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [31 x i8] c"Please enter your array size: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@string_tmp_.2 = private unnamed_addr constant [18 x i8] c"Please enter arr[\00", align 1
@string_tmp_.3 = private unnamed_addr constant [4 x i8] c"]: \00", align 1
@format.4 = private unnamed_addr constant [7 x i8] c"%s%d%s\00", align 1
@string_tmp_.5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@format.6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.7 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@string_tmp_.8 = private unnamed_addr constant [13 x i8] c"after sort: \00", align 1
@format.9 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@string_tmp_.10 = private unnamed_addr constant [10 x i8] c"arr[i] = \00", align 1
@format.11 = private unnamed_addr constant [7 x i8] c"%s%lf\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %size = alloca i32, align 4
  %temp = alloca double, align 8
  %j = alloca i32, align 4
  %i = alloca i32, align 4
  %arr = alloca [100 x double], align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %size)
  %size1 = load i32, i32* %size, align 4
  store i32 1, i32* %i, align 4
  br label %loop_condition

loop_condition:                                   ; preds = %loop_body, %main_entry
  %i2 = load i32, i32* %i, align 4
  %ile_tmp_ = icmp sle i32 %i2, %size1
  br i1 %ile_tmp_, label %loop_body, label %after

loop_body:                                        ; preds = %loop_condition
  %i3 = load i32, i32* %i, align 4
  %isub_tmp_ = sub i32 %i3, 1
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @format.4, i32 0, i32 0), i8* getelementptr inbounds ([18 x i8], [18 x i8]* @string_tmp_.2, i32 0, i32 0), i32 %isub_tmp_, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @string_tmp_.3, i32 0, i32 0))
  %i4 = load i32, i32* %i, align 4
  %isub_tmp_5 = sub i32 %i4, 1
  %3 = getelementptr [100 x double], [100 x double]* %arr, i32 0, i32 %isub_tmp_5
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.6, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @string_tmp_.5, i32 0, i32 0))
  %5 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.7, i32 0, i32 0), double* %3)
  %iadd_tmp_ = add i32 %i2, 1
  store i32 %iadd_tmp_, i32* %i, align 4
  br label %loop_condition

after:                                            ; preds = %loop_condition
  %i6 = load i32, i32* %i, align 4
  %j7 = load i32, i32* %j, align 4
  %temp8 = load double, double* %temp, align 8
  %size9 = load i32, i32* %size, align 4
  call void (i32, i32, double, [100 x double]*, i32, ...) @sort(i32 %i6, i32 %j7, double %temp8, [100 x double]* %arr, i32 %size9)
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.9, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @string_tmp_.8, i32 0, i32 0))
  store i32 0, i32* %i, align 4
  br label %loop

loop:                                             ; preds = %loop, %after
  %i11 = load i32, i32* %i, align 4
  %7 = getelementptr [100 x double], [100 x double]* %arr, i32 0, i32 %i11
  %8 = load double, double* %7, align 8
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @format.11, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.10, i32 0, i32 0), double %8)
  %i12 = load i32, i32* %i, align 4
  %iadd_tmp_13 = add i32 %i12, 1
  store i32 %iadd_tmp_13, i32* %i, align 4
  %i14 = load i32, i32* %i, align 4
  %size15 = load i32, i32* %size, align 4
  %ieq_tmp_ = icmp eq i32 %i14, %size15
  br i1 %ieq_tmp_, label %after10, label %loop

after10:                                          ; preds = %loop
  ret void
}

define internal void @swap(double %0, double* %1, double* %2, ...) {
swap:
  %temp = alloca double, align 8
  store double %0, double* %temp, align 8
  %x = load double, double* %1, align 8
  store double %x, double* %temp, align 8
  %y = load double, double* %2, align 8
  store double %y, double* %1, align 8
  %temp1 = load double, double* %temp, align 8
  store double %temp1, double* %2, align 8
  ret void
}

define internal void @sort(i32 %0, i32 %1, double %2, [100 x double]* %3, i32 %4, ...) {
sort:
  %i = alloca i32, align 4
  store i32 %0, i32* %i, align 4
  %j = alloca i32, align 4
  store i32 %1, i32* %j, align 4
  %temp = alloca double, align 8
  store double %2, double* %temp, align 8
  %size = alloca i32, align 4
  store i32 %4, i32* %size, align 4
  %size1 = load i32, i32* %size, align 4
  %isub_tmp_ = sub i32 %size1, 1
  store i32 0, i32* %i, align 4
  br label %loop_condition

loop_condition:                                   ; preds = %after6, %sort
  %i2 = load i32, i32* %i, align 4
  %ile_tmp_ = icmp sle i32 %i2, %isub_tmp_
  br i1 %ile_tmp_, label %loop_body, label %after

loop_body:                                        ; preds = %loop_condition
  %i3 = load i32, i32* %i, align 4
  store i32 %i3, i32* %j, align 4
  br label %loop_condition4

after:                                            ; preds = %loop_condition
  ret void

loop_condition4:                                  ; preds = %after11, %loop_body
  %j7 = load i32, i32* %j, align 4
  %ige_tmp_ = icmp sge i32 %j7, 1
  br i1 %ige_tmp_, label %loop_body5, label %after6

loop_body5:                                       ; preds = %loop_condition4
  %j8 = load i32, i32* %j, align 4
  %5 = getelementptr [100 x double], [100 x double]* %3, i32 0, i32 %j8
  %6 = load double, double* %5, align 8
  %j9 = load i32, i32* %j, align 4
  %isub_tmp_10 = sub i32 %j9, 1
  %7 = getelementptr [100 x double], [100 x double]* %3, i32 0, i32 %isub_tmp_10
  %8 = load double, double* %7, align 8
  %flt_tmp_ = fcmp olt double %6, %8
  br i1 %flt_tmp_, label %if, label %else

after6:                                           ; preds = %loop_condition4
  %iadd_tmp_ = add i32 %i2, 1
  store i32 %iadd_tmp_, i32* %i, align 4
  br label %loop_condition

if:                                               ; preds = %loop_body5
  %temp12 = load double, double* %temp, align 8
  %j13 = load i32, i32* %j, align 4
  %9 = getelementptr [100 x double], [100 x double]* %3, i32 0, i32 %j13
  %j14 = load i32, i32* %j, align 4
  %isub_tmp_15 = sub i32 %j14, 1
  %10 = getelementptr [100 x double], [100 x double]* %3, i32 0, i32 %isub_tmp_15
  call void (double, double*, double*, ...) @swap(double %temp12, double* %9, double* %10)
  br label %after11

else:                                             ; preds = %loop_body5
  br label %after11

after11:                                          ; preds = %else, %if
  %isub_tmp_16 = sub i32 %j7, 1
  store i32 %isub_tmp_16, i32* %j, align 4
  br label %loop_condition4
}
