
# Virtual Function

![](https://camo.githubusercontent.com/90641c46938397e9bc2a0dd2ee0c0365fab8f16a4bc8347b73c9569c8a6fc5e9/68747470733a2f2f73332d73676e30392e667074636c6f75642e636f6d2f636f64656c6561726e73746f726167652f4d656469612f44656661756c742f55736572732f4461745472616e6e2f4f4f502f6370702d706f6c796d6f72706869736d2e706e67)
- Hàm ảo là một thành viên trong lớp cha, được khai báo với từ khóa virtual.
- Một đối tượng gọi 1 method ra thì gọi method ở class nào dựa trên đối tượng thực tế mà con trỏ/ tham chiếu trỏ đến, chứ không dựa vào kiểu của con trỏ/ tham chiếu.
```c
class Car {
public:
    string Model;
    int Date;

public:
    Car(string m, int d) : Model(m), Date(d) {}

    virtual void Display(){
        cout << "Model: " << Model << endl;
        cout << "Date: " << Date << endl; 
    }
};

```

## Tính đa hình Run-time
Tính đa hình runtime cho phép chương trình quyết định gọi hàm nào trong thời điểm chạy, dựa vào kiểu thực tế của đối tượng.

Điều kiện:
- Hàm phải được khai báo là virtual trong lớp cha.
- Sử dụng con trỏ hoặc tham chiếu tới lớp cha để gọi hàm.
```c
Car *myCar; // Con trỏ lớp cha
Toyota toyotaCar("Camry", 2023, "Hybrid");
myCar = &toyotaCar;
myCar->Display(); // Gọi hàm Display() của Toyota
```
Kết quả 
```c
Brand Toyota:
Model: Camry
Date: 2023
Engine: Hybrid
```

## Pure Virtual Function
- Pure Virtual Function là hàm ảo không có nội dung và khai báo = 0. 
- Đối với class có hàm ảo thuần túy thì class con kế thừa thì phải định nghĩa lại hàm ảo.
```c
class Xe
{
    protected:
        string model;
        int namSanXuat;

    public:
        Xe(string m, int nam): model(m), namSanXuat(nam){}

        virtual void hienThiThongTin() = 0;
};
```

Class con kế thừa thì phải định ngĩa lại:
```c
class Toyota : public Xe
{
    private:
        string dongCo;

    public:
        Toyota(string m, int nam, string dongCo): Xe(m,nam), dongCo(dongCo){}

        void hienThiThongTin() override
        {
            cout << "Hang xe: Toyota\n";
            cout << "Model: " << model << "\n";
            cout << "Nam san xuat: " << namSanXuat << "\n";
            cout << "Dong co: " << dongCo << "\n";
        }
};
```
## Kế thừa ảo
- Kế thừa ảo giúp tránh vấn đề diamond problem trong đa kế thừa.
- Chỉ có một bản sao duy nhất của lớp cơ sở chung được kế thừa
```c
class A {
    public:
        A(){ cout << "Constructor A\n"; }

        void hienThiA(){ cout << "Day la lop A\n"; }
};

class B : virtual public A{
    public:
        B(){ cout << "Constructor B\n"; }

        void hienThiB(){ cout << "Day la lop B\n"; }
};

int main() {
    D d;

    d.hienThiA();
}
```
