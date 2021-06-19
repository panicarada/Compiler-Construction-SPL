; ModuleID = 'main'
source_filename = "main"

%info = type { i32, double, i8* }

@temp = common global i32
@info = common global %info
@string_tmp_ = private unnamed_addr constant [4 x i8] c"QZH\00", align 1
@string_tmp_.1 = private unnamed_addr constant [7 x i8] c"Name: \00", align 1
@string_tmp_.2 = private unnamed_addr constant [7 x i8] c"\09age: \00", align 1
@string_tmp_.3 = private unnamed_addr constant [7 x i8] c"\09GPA: \00", align 1
@format = private unnamed_addr constant [15 x i8] c"%s%s%s%d%s%lf\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %temp = alloca i32, align 4
  %info = alloca %info, align 8
  %0 = call i32 (i32, i8*, double, ...) @wrap(i32 8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @string_tmp_, i32 0, i32 0), double 5.555000e+00)
  store i32 %0, i32* %temp, align 4
  %member_tmp_ = getelementptr inbounds %info, %info* %info, i32 0, i32 2
  %1 = load i8*, i8** %member_tmp_, align 8
  %member_tmp_1 = getelementptr inbounds %info, %info* %info, i32 0, i32 0
  %2 = load i32, i32* %member_tmp_1, align 4
  %member_tmp_2 = getelementptr inbounds %info, %info* %info, i32 0, i32 1
  %3 = load double, double* %member_tmp_2, align 8
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.1, i32 0, i32 0), i8* %1, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.2, i32 0, i32 0), i32 %2, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.3, i32 0, i32 0), double %3)
  ret void
}

define i32 @wrap(i32 %0, i8* %1, double %2, ...) {
wrap:
  %Age = alloca i32, align 4
  store i32 %0, i32* %Age, align 4
  %Name = alloca i8*, align 8
  store i8* %1, i8** %Name, align 8
  %GPA = alloca double, align 8
  store double %2, double* %GPA, align 8
  %wrap1 = alloca i32, align 4
  %member_tmp_ = getelementptr inbounds %info, %info* %info, i32 0, i32 0
  %Age2 = load i32, i32* %Age, align 4
  store i32 %Age2, i32* %member_tmp_, align 4
  %member_tmp_3 = getelementptr inbounds %info, %info* %info, i32 0, i32 2
  %Name4 = load i8*, i8** %Name, align 8
  store i8* %Name4, i8** %member_tmp_3, align 8
  %member_tmp_5 = getelementptr inbounds %info, %info* %info, i32 0, i32 1
  %GPA6 = load double, double* %GPA, align 8
  store double %GPA6, double* %member_tmp_5, align 8
  %3 = load i32, i32* %wrap1, align 4
  ret i32 %3
}
