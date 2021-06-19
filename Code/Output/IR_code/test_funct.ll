; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [12 x i8] c"Hello World\00", align 1
@string_tmp_.1 = private unnamed_addr constant [26 x i8] c"Please Enter your value: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@string_tmp_.3 = private unnamed_addr constant [9 x i8] c"Ni hao a\00", align 1
@string_tmp_.4 = private unnamed_addr constant [3 x i8] c": \00", align 1
@format.5 = private unnamed_addr constant [8 x i8] c"%s%s%d\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
set_label:
  br label %main_entry

main_entry:                                       ; preds = %set_label
  %tmp = alloca i32, align 4
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @string_tmp_.1, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.2, i32 0, i32 0), i32* %tmp)
  %tmp1 = load i32, i32* %tmp, align 4
  %2 = call i32 (i8*, i32, ...) @print(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @string_tmp_.3, i32 0, i32 0), i32 %tmp1)
  store i32 %2, i32* %tmp, align 4
  ret void
}

define internal i32 @print(i8* %0, i32 %1, ...) {
print:
  %sentence = alloca i8*, align 8
  store i8* %0, i8** %sentence, align 8
  %id = alloca i32, align 4
  store i32 %1, i32* %id, align 4
  %print1 = alloca i32, align 4
  %sentence2 = load i8*, i8** %sentence, align 8
  %id3 = load i32, i32* %id, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @format.5, i32 0, i32 0), i8* %sentence2, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @string_tmp_.4, i32 0, i32 0), i32 %id3)
  %id4 = load i32, i32* %id, align 4
  store i32 %id4, i32* %print1, align 4
  %3 = load i32, i32* %print1, align 4
  ret i32 %3
}
