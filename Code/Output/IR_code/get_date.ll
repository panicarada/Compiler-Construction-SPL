; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [7 x i8] c"Year: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@string_tmp_.2 = private unnamed_addr constant [8 x i8] c"Month: \00", align 1
@format.3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@string_tmp_.5 = private unnamed_addr constant [6 x i8] c"Day: \00", align 1
@format.6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.7 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@format.8 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@string_tmp_.9 = private unnamed_addr constant [10 x i8] c"\E6\98\9F\E6\9C\9F\E4\B8\80\00", align 1
@string_tmp_.10 = private unnamed_addr constant [10 x i8] c"\E6\98\9F\E6\9C\9F\E4\BA\8C\00", align 1
@string_tmp_.11 = private unnamed_addr constant [10 x i8] c"\E6\98\9F\E6\9C\9F\E4\B8\89\00", align 1
@string_tmp_.12 = private unnamed_addr constant [10 x i8] c"\E6\98\9F\E6\9C\9F\E5\9B\9B\00", align 1
@string_tmp_.13 = private unnamed_addr constant [10 x i8] c"\E6\98\9F\E6\9C\9F\E4\BA\94\00", align 1
@string_tmp_.14 = private unnamed_addr constant [10 x i8] c"\E6\98\9F\E6\9C\9F\E5\85\AD\00", align 1
@string_tmp_.15 = private unnamed_addr constant [10 x i8] c"\E6\98\9F\E6\9C\9F\E4\B8\83\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %date = alloca { i32, i32, i32 }, align 8
  %record_access_tmp_ = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %date, i32 0, i32 2
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %record_access_tmp_)
  %record_access_tmp_1 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %date, i32 0, i32 1
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.3, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @string_tmp_.2, i32 0, i32 0))
  %3 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.4, i32 0, i32 0), i32* %record_access_tmp_1)
  %record_access_tmp_2 = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %date, i32 0, i32 0
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.6, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @string_tmp_.5, i32 0, i32 0))
  %5 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.7, i32 0, i32 0), i32* %record_access_tmp_2)
  %date3 = load { i32, i32, i32 }, { i32, i32, i32 }* %date, align 4
  %6 = call i8* ({ i32, i32, i32 }, ...) @get_date({ i32, i32, i32 } %date3)
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.8, i32 0, i32 0), i8* %6)
  ret void
}

define internal i8* @get_date({ i32, i32, i32 } %0, ...) {
get_date:
  %date = alloca { i32, i32, i32 }, align 8
  store { i32, i32, i32 } %0, { i32, i32, i32 }* %date, align 4
  %get_date1 = alloca i8*, align 8
  %record_access_tmp_ = getelementptr inbounds { i32, i32, i32 }, { i32, i32, i32 }* %date, i32 0, i32 0
  %load_tmp_ = load i32, i32* %record_access_tmp_, align 4
  br label %case_condition_0

after:                                            ; preds = %case_body_6, %case_condition_6, %case_body_5, %case_body_4, %case_body_3, %case_body_2, %case_body_1, %case_body_0
  %load_tmp_8 = load i8*, i8** %get_date1, align 8
  ret i8* %load_tmp_8

case_condition_0:                                 ; preds = %get_date
  %ieq_tmp_ = icmp eq i32 %load_tmp_, 1
  br i1 %ieq_tmp_, label %case_body_0, label %case_condition_1

case_body_0:                                      ; preds = %case_condition_0
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.9, i32 0, i32 0), i8** %get_date1, align 8
  br label %after

case_condition_1:                                 ; preds = %case_condition_0
  %ieq_tmp_2 = icmp eq i32 %load_tmp_, 2
  br i1 %ieq_tmp_2, label %case_body_1, label %case_condition_2

case_body_1:                                      ; preds = %case_condition_1
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.10, i32 0, i32 0), i8** %get_date1, align 8
  br label %after

case_condition_2:                                 ; preds = %case_condition_1
  %ieq_tmp_3 = icmp eq i32 %load_tmp_, 3
  br i1 %ieq_tmp_3, label %case_body_2, label %case_condition_3

case_body_2:                                      ; preds = %case_condition_2
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.11, i32 0, i32 0), i8** %get_date1, align 8
  br label %after

case_condition_3:                                 ; preds = %case_condition_2
  %ieq_tmp_4 = icmp eq i32 %load_tmp_, 4
  br i1 %ieq_tmp_4, label %case_body_3, label %case_condition_4

case_body_3:                                      ; preds = %case_condition_3
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.12, i32 0, i32 0), i8** %get_date1, align 8
  br label %after

case_condition_4:                                 ; preds = %case_condition_3
  %ieq_tmp_5 = icmp eq i32 %load_tmp_, 5
  br i1 %ieq_tmp_5, label %case_body_4, label %case_condition_5

case_body_4:                                      ; preds = %case_condition_4
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.13, i32 0, i32 0), i8** %get_date1, align 8
  br label %after

case_condition_5:                                 ; preds = %case_condition_4
  %ieq_tmp_6 = icmp eq i32 %load_tmp_, 6
  br i1 %ieq_tmp_6, label %case_body_5, label %case_condition_6

case_body_5:                                      ; preds = %case_condition_5
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.14, i32 0, i32 0), i8** %get_date1, align 8
  br label %after

case_condition_6:                                 ; preds = %case_condition_5
  %ieq_tmp_7 = icmp eq i32 %load_tmp_, 7
  br i1 %ieq_tmp_7, label %case_body_6, label %after

case_body_6:                                      ; preds = %case_condition_6
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @string_tmp_.15, i32 0, i32 0), i8** %get_date1, align 8
  br label %after
}
