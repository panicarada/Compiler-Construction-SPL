; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [22 x i8] c"Please enter your n: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@string_tmp_.2 = private unnamed_addr constant [6 x i8] c"fibo(\00", align 1
@string_tmp_.3 = private unnamed_addr constant [5 x i8] c") = \00", align 1
@format.4 = private unnamed_addr constant [10 x i8] c"%s%d%s%d\0A\00", align 1
@string_tmp_.5 = private unnamed_addr constant [7 x i8] c"using \00", align 1
@string_tmp_.6 = private unnamed_addr constant [7 x i8] c" steps\00", align 1
@format.7 = private unnamed_addr constant [8 x i8] c"%s%d%s\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %info = alloca { i32, i32 }, align 8
  %n = alloca i32, align 4
  %member_tmp_ = getelementptr inbounds { i32, i32 }, { i32, i32 }* %info, i32 0, i32 1
  store i32 0, i32* %member_tmp_, align 4
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %n)
  %n1 = load i32, i32* %n, align 4
  %n2 = load i32, i32* %n, align 4
  %2 = call i32 (i32, { i32, i32 }*, ...) @fibo(i32 %n2, { i32, i32 }* %info)
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @format.4, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @string_tmp_.2, i32 0, i32 0), i32 %n1, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @string_tmp_.3, i32 0, i32 0), i32 %2)
  %member_tmp_3 = getelementptr inbounds { i32, i32 }, { i32, i32 }* %info, i32 0, i32 1
  %4 = load i32, i32* %member_tmp_3, align 4
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @format.7, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.5, i32 0, i32 0), i32 %4, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.6, i32 0, i32 0))
  ret void
}

define internal i32 @fibo(i32 %0, { i32, i32 }* %1, ...) {
fibo:
  %n = alloca i32, align 4
  store i32 %0, i32* %n, align 4
  %fibo1 = alloca i32, align 4
  %member_tmp_ = getelementptr inbounds { i32, i32 }, { i32, i32 }* %1, i32 0, i32 1
  %member_tmp_2 = getelementptr inbounds { i32, i32 }, { i32, i32 }* %1, i32 0, i32 1
  %2 = load i32, i32* %member_tmp_2, align 4
  %iadd_tmp_ = add i32 %2, 1
  store i32 %iadd_tmp_, i32* %member_tmp_, align 4
  %n3 = load i32, i32* %n, align 4
  %ile_tmp_ = icmp sle i32 %n3, 1
  br i1 %ile_tmp_, label %if, label %else

if:                                               ; preds = %fibo
  %n4 = load i32, i32* %n, align 4
  store i32 %n4, i32* %fibo1, align 4
  %member_tmp_5 = getelementptr inbounds { i32, i32 }, { i32, i32 }* %1, i32 0, i32 0
  %fibo6 = load i32, i32* %fibo1, align 4
  store i32 %fibo6, i32* %member_tmp_5, align 4
  br label %after

else:                                             ; preds = %fibo
  %n7 = load i32, i32* %n, align 4
  %isub_tmp_ = sub i32 %n7, 1
  %3 = call i32 (i32, { i32, i32 }*, ...) @fibo(i32 %isub_tmp_, { i32, i32 }* %1)
  %n8 = load i32, i32* %n, align 4
  %isub_tmp_9 = sub i32 %n8, 2
  %4 = call i32 (i32, { i32, i32 }*, ...) @fibo(i32 %isub_tmp_9, { i32, i32 }* %1)
  %iadd_tmp_10 = add i32 %3, %4
  store i32 %iadd_tmp_10, i32* %fibo1, align 4
  %member_tmp_11 = getelementptr inbounds { i32, i32 }, { i32, i32 }* %1, i32 0, i32 0
  %fibo12 = load i32, i32* %fibo1, align 4
  store i32 %fibo12, i32* %member_tmp_11, align 4
  br label %after

after:                                            ; preds = %else, %if
  %5 = load i32, i32* %fibo1, align 4
  ret i32 %5
}
