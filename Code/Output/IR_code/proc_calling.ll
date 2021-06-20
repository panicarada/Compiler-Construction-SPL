; ModuleID = 'main'
source_filename = "main"

@string_tmp_ = private unnamed_addr constant [7 x i8] c"Zephyr\00", align 1
@string_tmp_.1 = private unnamed_addr constant [8 x i8] c"hello! \00", align 1
@format = private unnamed_addr constant [6 x i8] c"%s%s\0A\00", align 1
@string_tmp_.2 = private unnamed_addr constant [12 x i8] c"Your id is \00", align 1
@format.3 = private unnamed_addr constant [6 x i8] c"%s%d\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define void @main() {
main_entry:
  %name = alloca i8*, align 8
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @string_tmp_, i32 0, i32 0), i8** %name, align 8
  call void (i8**, i32, ...) @greeting(i8** %name, i32 13)
  ret void
}

define internal void @greeting(i8** %0, i32 %1, ...) {
greeting:
  %id = alloca i32, align 4
  store i32 %1, i32* %id, align 4
  %name = load i8*, i8** %0, align 8
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @format, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @string_tmp_.1, i32 0, i32 0), i8* %name)
  %id1 = load i32, i32* %id, align 4
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @format.3, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @string_tmp_.2, i32 0, i32 0), i32 %id1)
  ret void
}
