; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [19 x i8] c"Input your value: \00", align 1
@1 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@2 = private unnamed_addr constant [12 x i8] c"%lf >= %lf\0A\00", align 1
@3 = private unnamed_addr constant [11 x i8] c"%lf < %lf\0A\00", align 1
@4 = private unnamed_addr constant [9 x i8] c"ending!\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %value = alloca double, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @0, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0), double* %value)
  %value1 = load double, double* %value, align 8
  %fge_tmp_ = fcmp oge double %value1, 0x400921FB4D12D84A
  br i1 %fge_tmp_, label %if, label %else

if:                                               ; preds = %main_entry
  %value2 = load double, double* %value, align 8
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @2, i32 0, i32 0), double %value2, double 0x400921FB4D12D84A)
  br label %after

else:                                             ; preds = %main_entry
  %value3 = load double, double* %value, align 8
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @3, i32 0, i32 0), double %value3, double 0x400921FB4D12D84A)
  br label %after

after:                                            ; preds = %else, %if
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @4, i32 0, i32 0))
  ret void
}
