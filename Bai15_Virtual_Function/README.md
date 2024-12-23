
# Virtual Function
- Hàm ảo là một thành viên trong lớp cha, được khai báo với từ khóa virtual.
- Khi một lớp con ghi đè hàm ảo, phiên bản của lớp con sẽ được gọi ngay cả khi sử dụng con trỏ hoặc tham chiếu của lớp cha để trỏ đến đối tượng lớp con.
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

## Override và tính đa hình Run-time
Override là hành động ghi đè hàm ảo ở lớp con.. Khi một hàm ảo được ghi đè, hành vi của nó sẽ phụ thuộc vào đối tượng chứ không phải là con trỏ hoặc là tham chiếu.

Tính đa hình runtime đưa ra quyết định trong gọi hàm nào trong thời điểm chạy, không phải lúc biên dịch giúp mở rộng chức nằng. Điều này giúp chương trình linh hoạt, cho phép mở rộng mã nguồn mà không cần chỉnh sửa nhiều mã nguồn hiện tại.

```c
class Toyota : public Car {
public:
    Toyota(string m, int d, string e) : Car(m, d), Engine(e) {}

    void Display() override { 
        cout << "Brand Toyota:\n";
        cout << "Model: " << Model << endl;
        cout << "Date: " << Date << endl;
        cout << "Engine: " << Engine << endl;
    }
};
```
### Tính đa hình runtime
- Là khả năng chương trình quyết định hàm nào sẽ được gọi tại thời điểm chạy (runtime) dựa trên kiểu thực sự của đối tượng.
- Khi dùng từ khóa virtual, hành vi hàm sẽ phụ thuộc vào đối tượng thực tế chứ không phải kiểu con trỏ/ tham chiếu.
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