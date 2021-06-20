; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [26 x i8] c"Please enter your input: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@string_tmp_.2 = private unnamed_addr constant [11 x i8] c"The input \00", align 1
@string_tmp_.3 = private unnamed_addr constant [10 x i8] c" is even.\00", align 1
@format.4 = private unnamed_addr constant [8 x i8] c"%s%d%s\0A\00", align 1
@string_tmp_.5 = private unnamed_addr constant [11 x i8] c"The input \00", align 1
@string_tmp_.6 = private unnamed_addr constant [14 x i8] c" is not even.\00", align 1
@format.7 = private unnamed_addr constant [8 x i8] c"%s%d%s\0A\00", align 1
@string_tmp_.8 = private unnamed_addr constant [5 x i8] c"abs(\00", align 1
@string_tmp_.9 = private unnamed_addr constant [5 x i8] c") = \00", align 1
@format.10 = private unnamed_addr constant [10 x i8] c"%s%d%s%d\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %input = alloca i32, align 4
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %input)
  %2 = call i1 (i32*, ...) @is_even(i32* %input)
  br i1 %2, label %if, label %else

if:                                               ; preds = %main_entry
  %input1 = load i32, i32* %input, align 4
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @format.4, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @string_tmp_.2, i32 0, i32 0), i32 %input1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.3, i32 0, i32 0))
  br label %after

else:                                             ; preds = %main_entry
  %input2 = load i32, i32* %input, align 4
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @format.7, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @string_tmp_.5, i32 0, i32 0), i32 %input2, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @string_tmp_.6, i32 0, i32 0))
  br label %after

after:                                            ; preds = %else, %if
  ret void
}

define internal i1 @is_even(i32* %0, ...) {
is_even:
  %is_even1 = alloca i1, align 1
  %num = load i32, i32* %0, align 4
  %num2 = load i32, i32* %0, align 4
  %1 = call i32 (i32, ...) @iabs(i32 %num2)
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @format.10, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @string_tmp_.8, i32 0, i32 0), i32 %num, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @string_tmp_.9, i32 0, i32 0), i32 %1)
  %num3 = load i32, i32* %0, align 4
  %3 = call i32 (i32, ...) @iabs(i32 %num3)
  store i32 %3, i32* %0, align 4
  %num4 = load i32, i32* %0, align 4
  %fmod_tmp_ = srem i32 %num4, 2
  br label %case_condition_0

after:                                            ; preds = %case_body_1, %case_condition_1, %case_body_0
  %load_tmp_ = load i1, i1* %is_even1, align 1
  ret i1 %load_tmp_

case_condition_0:                                 ; preds = %is_even
  %ieq_tmp_ = icmp eq i32 %fmod_tmp_, 0
  br i1 %ieq_tmp_, label %case_body_0, label %case_condition_1

case_body_0:                                      ; preds = %case_condition_0
  store i1 true, i1* %is_even1, align 1
  br label %after

case_condition_1:                                 ; preds = %case_condition_0
  %ieq_tmp_5 = icmp eq i32 %fmod_tmp_, 1
  br i1 %ieq_tmp_5, label %case_body_1, label %after

case_body_1:                                      ; preds = %case_condition_1
  store i1 false, i1* %is_even1, align 1
  br label %after
}

define i32 @iabs(i32 %0, ...) {
iabs:
  %ile_tmp_ = icmp slt i32 %0, 0
  br i1 %ile_tmp_, label %if_lt_0_, label %after_

if_lt_0_:                                         ; preds = %iabs
  %ineg_tmp_ = sub i32 0, %0
  ret i32 %ineg_tmp_

after_:                                           ; preds = %iabs
  ret i32 %0
}
