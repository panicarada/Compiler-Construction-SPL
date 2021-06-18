; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [14 x i8] c"Hello World!\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @0, i32 0, i32 0))
  ret void
}
