; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [22 x i8] c"Please enter your x: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@string_tmp_.2 = private unnamed_addr constant [22 x i8] c"Please enter your y: \00", align 1
@format.3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.4 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@string_tmp_.5 = private unnamed_addr constant [12 x i8] c"After Swap:\00", align 1
@format.6 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@string_tmp_.7 = private unnamed_addr constant [4 x i8] c"x: \00", align 1
@string_tmp_.8 = private unnamed_addr constant [5 x i8] c"\09y: \00", align 1
@format.9 = private unnamed_addr constant [12 x i8] c"%s%lf%s%lf\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %temp = alloca double, align 8
  %x = alloca double, align 8
  %y = alloca double, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.1, i32 0, i32 0), double* %x)
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.3, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @string_tmp_.2, i32 0, i32 0))
  %3 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.4, i32 0, i32 0), double* %y)
  %temp1 = load double, double* %temp, align 8
  call void (double, double*, double*, ...) @swap(double %temp1, double* %x, double* %y)
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.6, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @string_tmp_.5, i32 0, i32 0))
  %x2 = load double, double* %x, align 8
  %y3 = load double, double* %y, align 8
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @format.9, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @string_tmp_.7, i32 0, i32 0), double %x2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @string_tmp_.8, i32 0, i32 0), double %y3)
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
