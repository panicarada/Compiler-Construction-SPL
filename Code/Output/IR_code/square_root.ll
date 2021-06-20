; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [46 x i8] c"Please enter the number you want to compute: \00", align 1
@format = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.1 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@string_tmp_.2 = private unnamed_addr constant [23 x i8] c"Please enter the EPS: \00", align 1
@format.3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@format.4 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@string_tmp_.5 = private unnamed_addr constant [6 x i8] c"sqrt(\00", align 1
@string_tmp_.6 = private unnamed_addr constant [5 x i8] c") = \00", align 1
@format.7 = private unnamed_addr constant [12 x i8] c"%s%lf%s%lf\0A\00", align 1
@string_tmp_.8 = private unnamed_addr constant [7 x i8] c"eps = \00", align 1
@format.9 = private unnamed_addr constant [7 x i8] c"%s%lf\0A\00", align 1
@string_tmp_.10 = private unnamed_addr constant [12 x i8] c"systemSqrt(\00", align 1
@string_tmp_.11 = private unnamed_addr constant [5 x i8] c") = \00", align 1
@format.12 = private unnamed_addr constant [12 x i8] c"%s%lf%s%lf\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %eps = alloca double, align 8
  %x = alloca double, align 8
  %EPS = alloca double, align 8
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([46 x i8], [46 x i8]* @string_tmp_, i32 0, i32 0))
  %1 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.1, i32 0, i32 0), double* %x)
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.3, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @string_tmp_.2, i32 0, i32 0))
  %3 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format.4, i32 0, i32 0), double* %EPS)
  %x1 = load double, double* %x, align 8
  %x2 = load double, double* %x, align 8
  %EPS3 = load double, double* %EPS, align 8
  %4 = call double (double, double*, double, ...) @mySquareRoot(double %x2, double* %eps, double %EPS3)
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @format.7, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @string_tmp_.5, i32 0, i32 0), double %x1, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @string_tmp_.6, i32 0, i32 0), double %4)
  %eps4 = load double, double* %eps, align 8
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @format.9, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_.8, i32 0, i32 0), double %eps4)
  %x5 = load double, double* %x, align 8
  %x6 = load double, double* %x, align 8
  %7 = call double (double, ...) @sqrt(double %x6)
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @format.12, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @string_tmp_.10, i32 0, i32 0), double %x5, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @string_tmp_.11, i32 0, i32 0), double %7)
  ret void
}

define internal double @mySquareRoot(double %0, double* %1, double %2, ...) {
mySquareRoot:
  %x = alloca double, align 8
  store double %0, double* %x, align 8
  %EPS = alloca double, align 8
  store double %2, double* %EPS, align 8
  %mySquareRoot1 = alloca double, align 8
  %x2 = load double, double* %x, align 8
  store double %x2, double* %mySquareRoot1, align 8
  br label %loop

loop:                                             ; preds = %loop, %mySquareRoot
  %mySquareRoot3 = load double, double* %mySquareRoot1, align 8
  %x4 = load double, double* %x, align 8
  %mySquareRoot5 = load double, double* %mySquareRoot1, align 8
  %fdiv_tmp_ = fdiv double %x4, %mySquareRoot5
  %fadd_tmp_ = fadd double %mySquareRoot3, %fdiv_tmp_
  %fdiv_tmp_6 = fdiv double %fadd_tmp_, 2.000000e+00
  store double %fdiv_tmp_6, double* %mySquareRoot1, align 8
  %mySquareRoot7 = load double, double* %mySquareRoot1, align 8
  %3 = call double (double, ...) @fsqr(double %mySquareRoot7)
  %x8 = load double, double* %x, align 8
  %fsub_tmp_ = fsub double %3, %x8
  store double %fsub_tmp_, double* %1, align 8
  %eps = load double, double* %1, align 8
  %EPS9 = load double, double* %EPS, align 8
  %fle_tmp_ = fcmp ole double %eps, %EPS9
  br i1 %fle_tmp_, label %after, label %loop

after:                                            ; preds = %loop
  %4 = load double, double* %mySquareRoot1, align 8
  ret double %4
}

define double @fabs(double %0, ...) {
fabs:
  %fle_tmp_ = fcmp olt double %0, 0.000000e+00
  br i1 %fle_tmp_, label %if_lt_0_, label %after_

if_lt_0_:                                         ; preds = %fabs
  %fneg_tmp_ = fneg double %0
  ret double %fneg_tmp_

after_:                                           ; preds = %fabs
  ret double %0
}

define double @sqrt(double %0, ...) {
sqrt:
  %ret_ = alloca double, align 8
  store double %0, double* %ret_, align 8
  %1 = load double, double* %ret_, align 8
  br label %loop_

loop_:                                            ; preds = %loop_, %sqrt
  %fdiv_tmp_ = fdiv double %1, %0
  %fadd_tmp_ = fadd double %1, %fdiv_tmp_
  %2 = fdiv double %fadd_tmp_, 2.000000e+00
  store double %2, double* %ret_, align 8
  %3 = load double, double* %ret_, align 8
  %fmul_tmp_ = fmul double %3, %3
  %fsub_tmp_ = fsub double %fmul_tmp_, %0
  %4 = call double (double, ...) @fabs(double %fsub_tmp_)
  %fle_tmp_ = fcmp ole double %4, 1.000000e-05
  br i1 %fle_tmp_, label %loop_, label %after_

after_:                                           ; preds = %loop_
  ret double %3
}

define double @fsqr(double %0, ...) {
fsqr:
  %fmul_tmp_ = fmul double %0, %0
  ret double %fmul_tmp_
}
