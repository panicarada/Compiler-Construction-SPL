; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [19 x i8] c"Input your index: \00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@2 = private unnamed_addr constant [6 x i8] c"true\0A\00", align 1
@3 = private unnamed_addr constant [7 x i8] c"false\0A\00", align 1
@4 = private unnamed_addr constant [33 x i8] c"Index:%d\09Value:%.5f\09testBool:%d\0A\00", align 1

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
  br i1 true, label %if, label %else

if:                                               ; preds = %main_entry
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @2, i32 0, i32 0))
  br label %after

else:                                             ; preds = %main_entry
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @3, i32 0, i32 0))
  br label %after

after:                                            ; preds = %else, %if
  %index1 = load i32, i32* %index, align 4
  %value2 = load double, double* %value, align 8
  %testBool3 = load i1, i1* %testBool, align 1
  %bool2int_tmp_ = sext i1 %testBool3 to i32
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @4, i32 0, i32 0), i32 %index1, double %value2, i32 %bool2int_tmp_)
  ret void
}
