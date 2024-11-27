
# OOP

## Encapsolution (Tính đóng gói)
Tính đóng gói là ẩn đi các proterty. Thì sẽ khai báo nó ở dạng private, không thể truy cập trực tiếp proterty thông qua object.

Con muốn truy cập proterty đọc hay ghi thì phải thông qua các method setter hay getter ở dạng public.

```c
class SinhVien{
    private:
            string name;
        int id;
        string major;

    public:
        SinhVien()
        {
            static int newID = 1;
            id = newID;
            newID++;
        }

        void setName(string name){
            //kiem tra cac dieu kien
            this->name = name;
        }

        void setMajor(string major){
            //kiem tra cac dieu kien
            this->major = major;
        }

        string getName()
        {
            return name;
        }

        string getMajor()
        {
            return major;
        }

        void display(){
            cout << "name: " <<name <<endl;
            cout << "ID: "<<id<<endl;
            cout<< "major "<<major<<endl;
        }
};

int main(){
    SinhVien sv1;
    sv1.setName("Hai");
    sv1.setMajor("Embedded");
    cout << sv1.getName()<<endl;
    cout << sv1.getMajor()<<endl;

}
```
## Inheritance ( Tính kế thừa)
Tính kế thừa là sử dụng lại các proterty và method của một class trong class khác.

Ngoài sử dụng lại các property và method nó còn có cơ chế ghi đè(**override**) để thêm các tính năng mới.

Thì class cha chứa các method và các proterty và class con sẽ kế thừa những cái đó từ lớp cha. Và để kế thừa thì xài dấu ":".

### Kế thừa public
Khi mà 1 class kế thừa 1 class khác được kế thừa theo kiểu public thì giữ nguyên nhưng member có thể kế thừa được như public hay protected còn private thì không kế thừa được

```c
class DoiTuong {
protected:
    string name; 
    int id;

public:
    void setName(const string& name) { 
        this->name = name; 
    }
    void setId(int id) { 
        this->id = id; 
    }

    void display() {
        cout << "name: " << name << endl;
        cout << "Id: " << id << endl;
    }
};

class SinhVien : public DoiTuong {
private:
    string chuyenNganh;

public:
    void setMajor(const string& chuyenNganh) {
        this->chuyenNganh = chuyenNganh;
    }

    void display() { 
        cout << "name: " << name << endl;
        cout << "Id: " << id << endl;
        cout << "Major: " << chuyenNganh << endl;
    }
};

class HocSinh : public DoiTuong {
private:
    string lop;

public:
    void setClass(const string& lop) {
        this->lop = lop;
    }

    void display() { 
        cout << "name: " << name << endl;
        cout << "Id: " << id << endl;
        cout << "Class: " << lop << endl;
    }
};

class GiaoVien : public DoiTuong {
private:
    string mon;

public:
    void setSubject(const string& mon) {
        this->mon = mon;
    }

    void display() { 
        cout << "name: " << name << endl;
        cout << "Id: " << id << endl;
        cout << "Subject: " << mon << endl;
    }
};
```

### Kế thừa protected và private

- Khi kế thừa **protected** thì các member public, protected của class cha sẽ là protected trong class con.
- Khi kế thừa **private** thì các member public, protected của class cha sẽ là protected trong class con.

### This pointer
- Con trỏ this nằm trong class
- Con trỏ this dùng để tham chiếu đến các property hiện tại của class.
- Nó dùng để phân biệt biến cục bộ truyền vào method với property
- Con trỏ this là const pointer

## Polymorphism (Tính đa hình)
Tính đa hình có nghĩa là có nhiều hình thái khác nhau và nó xảy ra khi chúng ta có nhiều class có liên quan với nhau thông qua kế thừa.

Tính đa hình chia ra làm 2 loại:
- Compile time Polymorphism : Đa hình ở thời điểm biên dịch
- Runtime Polymorphism : Đa hình ở thời điểm chạy
![](https://s3-sgn09.fptcloud.com/codelearnstorage/Media/Default/Users/DatTrann/OOP/cpp-polymorphism.png)

### Compile time Polymorphism
Tính đa hình này sủ dụng bằng cách nạp chống hàm hoặc nạp chồng toán thừa

**Function Overloading (Nạp chồng hàm)**
Cho phép sử dụng cùng 1 tên gọi cho các hàm giống nhau, nhưng lại khác nhau về kiểu dữ liệu tham số hoặc số lượng tham số.
```c
class TinhToan{
    private:
        int a;
        int b;
    public:
        int tong(int a, int b){
            return a+b;
        }
        double tong(int a, int b, int c, double d){
            return (double)a+b+c+d;
        }
        double tong(int a, double b){
            return (double)a+b;
        }
};

int main(int argc, char const *argv[]){

    TinhToan th, th1, th2;
    cout << th.tong(2, 5) << endl;
    cout << th1.tong(2, 5, 7, 6.7) << endl;
    cout << th2.tong(2, 3.5) << endl;

    return 0;
}
```

**Operator Overloading (Nạp chồng toán tử)**
Được dùng để định nghĩa toán tử cho có sẵn trong c++ phục vụ cho dữ liệu riêng.

Giả sử có lớp PhanSo và có các phương thức tính toán như Cong, Tru, Nhan, Chia.
Nếu gặp một biểu thức phức tạp, số lượng phép tính nhiều thì việc sử dụng các phương thức trên khá khó khăn. Vì thế ta sẽ nạp chồng lại các toán tử để có thể tạo một cái nhìn trực quan vào code, giảm thiểu các lỗi sai không đáng có.
```c
class Phanso
{
    private: 
        int num;
        int den;
    
    public:
        Phanso(int num = 0,int den =1){
            this->num = num;
            this->den = den;
        }

        Phanso operator + (Phanso &other)
        {
            Phanso ketqua;
            ketqua.num = this->num * other.den + this->den * other.num;
            ketqua.den = this->den * other.den;
            return ketqua;
        } 

        Phanso operator * (Phanso const &other)
        {
            Phanso ketqua;
            ketqua.num = this->num * other.num;
            ketqua.den = this->den * other.den;
            return ketqua;
        }

        bool operator == (Phanso const &other){
            return (this->num == other.num && this->den == other.den);
        }

        void display()
        {
            cout << "Tu so: " << num <<"   Mau so: "<<den<<endl;

        }
};
```


