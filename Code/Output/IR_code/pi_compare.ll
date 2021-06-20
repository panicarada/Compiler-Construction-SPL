; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [19 x i8] c"Input your value: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@string_tmp_.2 = private unnamed_addr constant [5 x i8] c" >= \00", align 1
@format.3 = private unnamed_addr constant [10 x i8] c"%lf%s%lf\0A\00", align 1
@string_tmp_.4 = private unnamed_addr constant [4 x i8] c" < \00", align 1
@format.5 = private unnamed_addr constant [10 x i8] c"%lf%s%lf\0A\00", align 1
@string_tmp_.6 = private unnamed_addr constant [8 x i8] c"ending!\00", align 1
@format.7 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %value = alloca double, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.1, i32 0, i32 0), double* %value)
  %value1 = load double, double* %value, align 8
  %fge_tmp_ = fcmp oge double %value1, 0x400921FB4D12D84A
  br i1 %fge_tmp_, label %if, label %else

if:                                               ; preds = %main_entry
  %value2 = load double, double* %value, align 8
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @format.3, i32 0, i32 0), double %value2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @string_tmp_.2, i32 0, i32 0), double 0x400921FB4D12D84A)
  br label %after

else:                                             ; preds = %main_entry
  %value3 = load double, double* %value, align 8
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @format.5, i32 0, i32 0), double %value3, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @string_tmp_.4, i32 0, i32 0), double 0x400921FB4D12D84A)
  br label %after

after:                                            ; preds = %else, %if
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.7, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @string_tmp_.6, i32 0, i32 0))
  ret void
}
