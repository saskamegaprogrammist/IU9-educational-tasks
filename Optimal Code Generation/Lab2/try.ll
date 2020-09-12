; ModuleID = 'try.c'
source_filename = "try.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 {
main:
  %b = alloca i32
  store i32 5, i32* %b
  %0 = load i32, i32* %b
  %a = alloca i32
  store i32 5, i32* %a
  %1 = load i32, i32* %a
  br label %loop

loop:                                             ; preds = %ifcont, %main
  %b1 = load i32, i32* %b
  %cmpv = icmp ugt i32 %b1, 4
  br i1 %cmpv, label %then, label %else

then:                                             ; preds = %loop
  store i32 2, i32* %a
  %2 = load i32, i32* %a
  br label %ifcont

else:                                             ; preds = %loop
  %a2 = load i32, i32* %a
  %addv = sub i32 %a2, 1
  store i32 %addv, i32* %a
  %3 = load i32, i32* %a
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %iftmp = phi i32 [ %2, %then ], [ %3, %else ]
  %a3 = load i32, i32* %a
  %cmpv4 = icmp ugt i32 %a3, 3
  br i1 %cmpv4, label %loop, label %afterloop

afterloop:                                        ; preds = %ifcont
  %c = alloca i32
  store i32 2, i32* %c
  %4 = load i32, i32* %c
  %a5 = load i32, i32* %a
  %b6 = load i32, i32* %b
  %c7 = load i32, i32* %c
  %mulv = mul i32 %b6, %c7
  %addv8 = add i32 %a5, %mulv
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32 %addv8)
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.0-1ubuntu2 (tags/RELEASE_600/final)"}
