; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [23 x i8] c"Hello World: %d, %.5f\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %index = alloca i32, align 4
  store i32 15, i32* %index, align 4
  %index1 = load i32, i32* %index, align 4
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @0, i32 0, i32 0), i32 %index1, double 0x400921FB4D12D84A)
  ret void
}
