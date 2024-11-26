
# Class

Class được sử dụng để định nghĩa 1 lớp, là 1 cấu trúc dữ liệu tuwjd định nghĩa có thể chứa dữ liệu và các hàm liên quan.

Các biến được khai báo trong Class được gọi là **thuộc tính(property)**, còn các hàm trong Class thì được gọi là **phương thức(method)**

Biến được khai báo từ Class được gọi là **object**

```c
class HinhChuNhat {

    public:
        double chieudai;    //property
        double chieurong;   //property

        void dientich(){    //method
            cout << " Dien tich hcn " << chieudai * chieurong <<endl;
        }
};


int main(){
    HinhChuNhat hcn; //object
}
```

## Constructer
Được coi là một hàm khởi tạo giá trị cho các property, có tên trùng với tên class, tự động khởi tạo giá trị cụ thể được set.
```c
class HinhChuNhat {

    public:
        double chieudai;    //property
        double chieurong;   //property

        void dientich(){    //method
            cout << " Dien tich hcn " << chieudai * chieurong <<endl;
        }
        HinhChuNhat(){  // Contruster
           chieudai = 10;
           chieurong = 20 
        }
};
```
## Destructer
Được coi là một hàm hủy đối tượng, trước khi bị thu hồi ô nhớ thì nó sẽ thực hiện hàm Destructer.
```c
class HinhChuNhat {

    public:
        double chieudai;    //property
        double chieurong;   //property

        void dientich(){    //method
            cout << " Dien tich hcn " << chieudai * chieurong <<endl;
        }
        HinhChuNhat(){  // Contruster
           chieudai = 10;
           chieurong = 20 
        }
        ~HinhChuNhat(); // Destructer
};
```
## Static in Class
### Static property
Khi khai báo static cho property thì tất cả các object đều được sử dụng chung biến static này.

Biến static này sẽ được lưu ở vùng bss nếu chưa khai báo, phạm vi toàn cục.

Biến var chỉ khi được cấp phát vùng nhớ khi được khai báo bằng **<type>Classname::namestatic**
```c
class HinhChuNhat {

    public:
        double chieudai;
        double chieurong;
        static int var;

        void display(){
            cout << "static : " <<endl;
            var = 20;
        }
};

int HinhChuNhat::var; // Cap phat dia chi

int main(){
    HinhChuNhat hcn1;
    HinhChuNhat hcn2;
    cout<< "Dia chi var hcn1:"<<&hcn1.var<<endl;
    cout<< "Dia chi var hcn2:"<<&hcn2.var<<endl;
}
```

Kết quả: là cả 2 object đều sử dụng chung biến var.
```c
Dia chi var hcn1:0x7ff65b6f90a0
Dia chi var hcn2:0x7ff65b6f90a0
```

### Static method
Gọi trực tiếp thông qua class mà không cần thông qua object. 

Chỉ có thể tương tác với static property.
```c
class HinhChuNhat {

    public:
        double chieudai;
        double chieurong;
        static int var;

        static void display(){
            cout << "static method : " <<endl;
            var = 20;
        }
};

int HinhChuNhat::var;

int main(){
    HinhChuNhat hcn1;
    HinhChuNhat::display();
    cout <<"var = " <<HinhChuNhat::var <<endl;
}
```