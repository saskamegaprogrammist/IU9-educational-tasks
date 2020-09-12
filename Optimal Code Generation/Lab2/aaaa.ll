define i64 @main() {
main:
  %a = alloca i64
  store i64 2, i64* %a
  %b = alloca i64
  store i64 3, i64* %b
  %a1 = load i64, i64* %a
  %b2 = load i64, i64* %b
  %addv = add i64 %a1, %b2
  %c = alloca i64
  store i64 %addv, i64* %c
  %c3 = load i64, i64* %c
  ret i64 %c3
}