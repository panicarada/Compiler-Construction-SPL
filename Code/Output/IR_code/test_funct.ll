; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [24 x i8] c"Hello World: %d!p\83\C0a\BD\7F\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @scanf(i8*, ...)

define internal void @main() {
main_entry:
  %tmp = alloca i32, align 4
  %0 = call i32 (i32, ...) @print(i32 10)
  store i32 %0, i32* %tmp, align 4
  ret void
}

define internal i32 @print(i32 %0, ...) {
print:
  %id = alloca i32, align 4
  store i32 %0, i32* %id, align 4
  %print1 = alloca i32, align 4
  %id2 = load i32, i32* %id, align 4
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @0, i32 0, i32 0), i32 %id2)
  %id3 = load i32, i32* %id, align 4
  store i32 %id3, i32* %print1, align 4
  %2 = load i32, i32* %print1, align 4
  ret i32 %2
}
