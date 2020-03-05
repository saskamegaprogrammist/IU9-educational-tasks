program test1;
const Sz = 100; // Размер массива
 
var 
  a: array [1 to Sz] of integer;
  mas : array[1..5, 1..10] of integer;
  N: integer; // Количество элементов в массиве
  i: integer;
 
begin
  write('Введите количество элементов в массиве: ');
  read(N);
  write('Введите элементы массива: ');
  for i:=1 to N do
    read(a[i]);
  write('Вывод элементов массива: ');
  for i:=1 to N do
    write(a[i],' ');
end.
