; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [4 x i8] c"QZH\00", align 1
@string_tmp_.1 = private unnamed_addr constant [7 x i8] c"Name: \00", align 1
@string_tmp_.2 = private unnamed_addr constant [7 x i8] c"\09age: \00", align 1
@string_tmp_.3 = private unnamed_addr constant [7 x i8] c"\09GPA: \00", align 1
@format = private unnamed_addr constant [15 x i8] c"%s%s%s%d%s%lf\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %info = alloca { i32, double, i8* }, align 8
  call void (i32, i8*, double, { i32, double, i8* }*, ...) @wrap(i32 8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @string_tmp_, i32 0, i32 0), double 5.555000e+00, { i32, double, i8* }* %info)
  %record_access_tmp_ = getelementptr inbounds { i32, double, i8* }, { i32, double, i8* }* %info, i32 0, i32 2
  %load_tmp_ = load i8*, i8** %record_access_tmp_, align 8
  %record_access_tmp_1 = getelementptr inbounds { i32, double, i8* }, { i32, double, i8* }* %info, i32 0, i32 0
  %load_tmp_2 = load i32, i32* %record_access_tmp_1, align 4
  %record_access_tmp_3 = getelementptr inbounds { i32, double, i8* }, { i32, double, i8* }* %info, i32 0, i32 1
  %load_tmp_4 = load double, double* %record_access_tmp_3, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.1, i32 0, i32 0), i8* %load_tmp_, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.2, i32 0, i32 0), i32 %load_tmp_2, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.3, i32 0, i32 0), double %load_tmp_4)
  ret void
}

define internal void @wrap(i32 %0, i8* %1, double %2, { i32, double, i8* }* %3, ...) {
wrap:
  %Age = alloca i32, align 4
  store i32 %0, i32* %Age, align 4
  %Name = alloca i8*, align 8
  store i8* %1, i8** %Name, align 8
  %GPA = alloca double, align 8
  store double %2, double* %GPA, align 8
  %record_access_tmp_ = getelementptr inbounds { i32, double, i8* }, { i32, double, i8* }* %3, i32 0, i32 0
  %Age1 = load i32, i32* %Age, align 4
  store i32 %Age1, i32* %record_access_tmp_, align 4
  %record_access_tmp_2 = getelementptr inbounds { i32, double, i8* }, { i32, double, i8* }* %3, i32 0, i32 2
  %Name3 = load i8*, i8** %Name, align 8
  store i8* %Name3, i8** %record_access_tmp_2, align 8
  %record_access_tmp_4 = getelementptr inbounds { i32, double, i8* }, { i32, double, i8* }* %3, i32 0, i32 1
  %GPA5 = load double, double* %GPA, align 8
  store double %GPA5, double* %record_access_tmp_4, align 8
  ret void
}
