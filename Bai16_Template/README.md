
# Template

Function templates là một tính năng giúp viết các function hoặc class chung có thể được sử dụng cho nhiều kiểu dữ liệu khác nhau mà không cần phải triển khai nhiều phiên bản của cùng một function hoặc class.

Trong quá trình biên dịch, khi sử dụng template trong C++, trình biên dịch sẽ suy luận hai kiểu dữ liệu: một cho tham số kiểu **T** và một cho **ParamType**. Các kiểu này thường khác nhau, vì ParamType thường có thêm các đặc tính như const hoặc các chỉ thị tham chiếu (& hoặc &&).
```
 template<typename T>
 void f(const T& param);  // param là tham chiếu const
```   
Và được gọi:
```
 int x = 0;
 f(x);                   // T được suy luận là 'int', ParamType là 'const int&'
 ```
Ở đây, T là int, nhưng vì tham số param là const T&, ParamType sẽ là const int&.

T được suy luận từ kiểu của đối số truyền vào, nhưng ParamType là kiểu tham số trong hàm và được xác định bởi cách khai báo tham số.

## Các trường hợp template
### ParamType là kiểu con trỏ hoặc tham chiếu
Tham chiếu
```c
template <typename T>
void f(T& param) { 
    cout << "Reference: " << param << endl;
}


int main() {
    int x = 10;
    const int cx = x;      
    const int &rx = x;

    f(x);  // T = int, paramType là int&
    f(cx); // T = const int, paramType là const int&
    f(rx); // T = const int, paramType là const int&

    return 0;
}
```

Con trỏ:
```c
template <typename T>
void f(T* param) { //aram is now a pointer
    cout << "Reference: " << *param << endl;
}


int main() {
    int x = 10;     
    const int *rx = &x;

    f(&x);  // T = int, kiểu tham số là int&
    f(rx); // T = const int, kiểu tham số là const int&

    return 0;
}
```
### ParamType là tham chiếu tổng quát( Universal Reference)
Tham chiếu tổng quát là một tham chiếu có thể gắn với cả lvalue và rvalue. Nó được khai báo dưới dạng T&& trong một hàm template, trong đó T là paramType.
```c
template<typename T>
void f(T&& param) {
    cout << "param type: " << param << endl;
}

int main() {
    int x = 27;             
    const int cx = x;       
    const int& rx = x;       

    f(x);           // x là lvalue, kiểu tham số suy luận là int&
    f(cx);          // cx là lvalue, kiểu tham số suy luận là const int&
    f(rx);          // rx là lvalue, kiểu tham số suy luận là const int&
    f(27);          // 27 là rvalue, kiểu tham số suy luận là int&&

    return 0;
}
```

## Class template
- Class templates là một khái niệm tương tự như function templates, nhưng được áp dụng cho class thay vì function.'
- Class templates cho phép bạn viết một lớp chung mà có thể được sử dụng với nhiều kiểu dữ liệu khác nhau.
```c
template<typename T1, typename T2>
class Sensor
{
    private:
        T1 value1;
        T2 value2;

    public:
        Sensor(T1 init1, T2 init2): value1(init1), value2(init2){}

        T1 getValue1(){
            return value1;
        }

        T2 getValue2(){
            return value2;
        }

        void display(){
            cout << "Sensor Value 1 :" << getValue1() << endl;
            cout << "Sensor Value 2 :" << getValue2() << endl; 
        }
};
```
