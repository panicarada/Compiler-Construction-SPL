; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [26 x i8] c"please enter your value: \00", align 1
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %value = alloca i32, align 4
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @0, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %value)
  %value1 = load i32, i32* %value, align 4
  %igt_tmp_ = icmp sgt i32 %value1, 0
  br i1 %igt_tmp_, label %if, label %else

if:                                               ; preds = %main_entry
  br label %after

else:                                             ; preds = %main_entry
  br label %after

after:                                            ; preds = %else, %if
  %value2 = load i32, i32* %value, align 4
  %ieq_tmp_ = icmp eq i32 %value2, 0
  br i1 %ieq_tmp_, label %if3, label %else4

if3:                                              ; preds = %after
  br label %after5

else4:                                            ; preds = %after
  br label %after5

after5:                                           ; preds = %else4, %if3
  %value6 = load i32, i32* %value, align 4
  %ilt_tmp_ = icmp slt i32 %value6, 0
  br i1 %ilt_tmp_, label %if7, label %else8

if7:                                              ; preds = %after5
  br label %after9

else8:                                            ; preds = %after5
  br label %after9

after9:                                           ; preds = %else8, %if7
  ret void
}
