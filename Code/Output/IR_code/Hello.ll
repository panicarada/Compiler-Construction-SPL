; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [12 x i8] c"Hello Wolrd\00", align 1
@format = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @string_tmp_, i32 0, i32 0))
  ret void
}
