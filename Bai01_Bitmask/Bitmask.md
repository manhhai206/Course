
# Bitmask

Bitmask là kỹ thuật sử dụng các bit để lưu trữ các trạng thái hoặc flag. Sử dụng Bitmask thường dùng để set, delete hay check status của các bit  chẳng hạn như các bit trong thanh ghi của các MCU.

## Các toán tử bitwise

### AND (&)

Dùng phép AND giữa từng cặp bit của 2 số và trả về kết quả là 1 khi 2 bit thực hiện phép AND đều là 1 , còn lại thì trả về 0.

```c
int kq = a & b;
```
Nếu a và b đều bằng 1 thì kq sẽ trả về là 1. Còn các trường hợp còn lại sẽ bằng 0.
```
1011 AND
0001
----
0001
```


### OR (|)

Dùng phép OR giữa từng cặp bit của 2 số và trả về kết quả là 1 khi chỉ cần 1 trong 2 bit thực hiện phép OR là 1 , còn lại thì trả về 0 khi cả 2 bit đều là 0.

```c
int kq = a | b;
```
```
1011 OR
0001
----
1011
```

### XOR (^)
Dùng phép XOR giữa từng cặp bit của 2 số và trả về kết quả là 1 khi chỉ có 1 bit thực hiện phép XOR  là 1 , còn lại thì trả về 0 khi cả 2 bit đều là 0 hoặc là 1.
```c
int kq = a ^ b;
```
```
1011 XOR
0001
----
1010
```

### NOT

Dùng để thực hiện phép NOT bitwise trên từng bit của một số. Kết quả là bit đảo ngược của số đó.

```c
int kq = ~a;
```
```
1011 NOT
----
0100
```

## Phép dịch bit

Trong trường hợp <<, các bit ở bên phải sẽ được dịch sang trái, và các bit trái cùng sẽ được đặt giá trị 0.

Trong trường hợp >>, các bit ở bên trái sẽ được dịch sang phải, và các bit phải cùng sẽ được đặt giá trị 0 hoặc 1 tùy thuộc vào giá trị của bit cao nhất (bit dấu).

```c
int b = 5;         // b = 0000 0101 (dạng nhị phân)
int kq = b << 1;   // kq = 0000 1010 (dịch trái 1 bit)

int a = -8;        // a = 1111 1000 (dạng nhị phân với bit dấu)
int kq = a >> 1;   // kq = 1111 1100 (dịch phải 1 bit)

```
