; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [41 x i8] c"option: [0]: pop\09[1]: push\09[other]: exit\00", align 1
@format = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@string_tmp_.1 = private unnamed_addr constant [27 x i8] c"Please enter your option: \00", align 1
@format.2 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@format.4 = private unnamed_addr constant [5 x i8] c"%lf\0A\00", align 1
@string_tmp_.5 = private unnamed_addr constant [44 x i8] c"Please enter the element you want to push: \00", align 1
@format.6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.7 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@string_tmp_.8 = private unnamed_addr constant [39 x i8] c"[Error]: No more element to be popped!\00", align 1
@format.9 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@string_tmp_.10 = private unnamed_addr constant [28 x i8] c"[Error]: The stack is full!\00", align 1
@format.11 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %element = alloca double, align 8
  %option = alloca i32, align 4
  %index = alloca i32, align 4
  %stack = alloca { i32, [1000 x double] }, align 8
  %record_access_tmp_ = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %stack, i32 0, i32 0
  store i32 0, i32* %record_access_tmp_, align 4
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([41 x i8], [41 x i8]* @string_tmp_, i32 0, i32 0))
  br label %loop

loop:                                             ; preds = %after2, %main_entry
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.2, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @string_tmp_.1, i32 0, i32 0))
  %2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.3, i32 0, i32 0), i32* %option)
  %option1 = load i32, i32* %option, align 4
  %ieq_tmp_ = icmp eq i32 %option1, 0
  br i1 %ieq_tmp_, label %if, label %else

after:                                            ; preds = %after2
  ret void

if:                                               ; preds = %loop
  %3 = call double ({ i32, [1000 x double] }*, ...) @pop({ i32, [1000 x double] }* %stack)
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @format.4, i32 0, i32 0), double %3)
  br label %after2

else:                                             ; preds = %loop
  %option3 = load i32, i32* %option, align 4
  %ieq_tmp_4 = icmp eq i32 %option3, 1
  br i1 %ieq_tmp_4, label %if5, label %else6

after2:                                           ; preds = %after7, %if
  %option9 = load i32, i32* %option, align 4
  %ieq_tmp_10 = icmp eq i32 %option9, 2
  br i1 %ieq_tmp_10, label %after, label %loop

if5:                                              ; preds = %else
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.6, i32 0, i32 0), i8* getelementptr inbounds ([44 x i8], [44 x i8]* @string_tmp_.5, i32 0, i32 0))
  %6 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.7, i32 0, i32 0), double* %element)
  %element8 = load double, double* %element, align 8
  call void (double, { i32, [1000 x double] }*, ...) @push(double %element8, { i32, [1000 x double] }* %stack)
  br label %after7

else6:                                            ; preds = %else
  store i32 2, i32* %option, align 4
  br label %after7

after7:                                           ; preds = %else6, %if5
  br label %after2
}

define internal void @set(double %0, [1000 x double]* %1, i32 %2, ...) {
set:
  %element = alloca double, align 8
  store double %0, double* %element, align 8
  %index = alloca i32, align 4
  store i32 %2, i32* %index, align 4
  %index1 = load i32, i32* %index, align 4
  %3 = getelementptr [1000 x double], [1000 x double]* %1, i32 0, i32 %index1
  %element2 = load double, double* %element, align 8
  store double %element2, double* %3, align 8
  ret void
}

define internal double @pop({ i32, [1000 x double] }* %0, ...) {
pop:
  %pop1 = alloca double, align 8
  %record_access_tmp_ = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %0, i32 0, i32 0
  %1 = load i32, i32* %record_access_tmp_, align 4
  %igt_tmp_ = icmp sgt i32 %1, 0
  br i1 %igt_tmp_, label %if, label %else

if:                                               ; preds = %pop
  %record_access_tmp_2 = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %0, i32 0, i32 1
  %2 = load [1000 x double], [1000 x double]* %record_access_tmp_2, align 8
  %record_access_tmp_3 = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %0, i32 0, i32 0
  %3 = load i32, i32* %record_access_tmp_3, align 4
  %4 = call double ([1000 x double], i32, ...) @get([1000 x double] %2, i32 %3)
  store double %4, double* %pop1, align 8
  %record_access_tmp_4 = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %0, i32 0, i32 0
  %record_access_tmp_5 = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %0, i32 0, i32 0
  %5 = load i32, i32* %record_access_tmp_5, align 4
  %isub_tmp_ = sub i32 %5, 1
  store i32 %isub_tmp_, i32* %record_access_tmp_4, align 4
  br label %after

else:                                             ; preds = %pop
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.9, i32 0, i32 0), i8* getelementptr inbounds ([39 x i8], [39 x i8]* @string_tmp_.8, i32 0, i32 0))
  br label %after

after:                                            ; preds = %else, %if
  %7 = load double, double* %pop1, align 8
  ret double %7
}

define internal double @get([1000 x double] %0, i32 %1, ...) {
get:
  %list = alloca [1000 x double], align 8
  store [1000 x double] %0, [1000 x double]* %list, align 8
  %index = alloca i32, align 4
  store i32 %1, i32* %index, align 4
  %get1 = alloca double, align 8
  %index2 = load i32, i32* %index, align 4
  %2 = getelementptr [1000 x double], [1000 x double]* %list, i32 0, i32 %index2
  %3 = load double, double* %2, align 8
  store double %3, double* %get1, align 8
  %4 = load double, double* %get1, align 8
  ret double %4
}

define internal void @push(double %0, { i32, [1000 x double] }* %1, ...) {
push:
  %element = alloca double, align 8
  store double %0, double* %element, align 8
  %record_access_tmp_ = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %1, i32 0, i32 0
  %2 = load i32, i32* %record_access_tmp_, align 4
  %ilt_tmp_ = icmp slt i32 %2, 1000
  br i1 %ilt_tmp_, label %if, label %else

if:                                               ; preds = %push
  %record_access_tmp_1 = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %1, i32 0, i32 0
  %record_access_tmp_2 = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %1, i32 0, i32 0
  %3 = load i32, i32* %record_access_tmp_2, align 4
  %iadd_tmp_ = add i32 %3, 1
  store i32 %iadd_tmp_, i32* %record_access_tmp_1, align 4
  %element3 = load double, double* %element, align 8
  %record_access_tmp_4 = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %1, i32 0, i32 1
  %record_access_tmp_5 = getelementptr inbounds { i32, [1000 x double] }, { i32, [1000 x double] }* %1, i32 0, i32 0
  %4 = load i32, i32* %record_access_tmp_5, align 4
  call void (double, [1000 x double]*, i32, ...) @set(double %element3, [1000 x double]* %record_access_tmp_4, i32 %4)
  br label %after

else:                                             ; preds = %push
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.11, i32 0, i32 0), i8* getelementptr inbounds ([28 x i8], [28 x i8]* @string_tmp_.10, i32 0, i32 0))
  br label %after

after:                                            ; preds = %else, %if
  ret void
}
