#include <iostream>
#include <string>

using namespace std;

class Xe
{
    protected:
        string model;
        int namSanXuat;

    public:
        Xe(string m, int nam): model(m), namSanXuat(nam){}

        virtual void hienThiThongTin() = 0;
};

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

class Honda : public Xe
{
    private:
        string mauSac;

    public:
        Honda(string m, int nam, string mau): Xe(m,nam), mauSac(mau){}

        void hienThiThongTin() override {
            cout << "Hang xe: Honda\n";
            cout << "Model: " << model << "\n";
            cout << "Nam san xuat: " << namSanXuat << "\n";
            cout << "Mau sac: " << mauSac << "\n";
        }
};

class Mazda : public Xe
{
    private:
        string loaiDanDong;

    public:
        Mazda(string m, int nam, string loaiDanDong): Xe(m,nam), loaiDanDong(loaiDanDong){}

        void hienThiThongTin() override {
            cout << "Hang xe: Mazda\n";
            cout << "Model: " << model << "\n";
            cout << "Nam san xuat: " << namSanXuat << "\n";
            cout << "Loai dan dong: " << loaiDanDong << "\n";
        }
};

int main(int argc, char const *argv[])
{
    Xe *xe1;
    // Toyota to;
    // Honda ho;
    // Mazda mz;
    // Xe *xe;

    // xe = &to;
    // xe->hienThiThongTin();
   
    Mazda cx3("CX-3", 2019, "Dan dong 4 banh"); // stack

    // Toyota toyota1("campry", 2020, "V6");   // 0x01

    Xe *ptr[] = {new Toyota("campry", 2020, "V6"),  // toyota("campry", 2020, "V6") // 0x01
                 new Honda("civic", 2019, "do"),
                 new Mazda("CX-5", 2021, "Dan dong 4 banh"),
                 new Toyota("corolla", 2018, "I4 1.8L"),
                 new Honda("accord", 2020, "den"),
                 &cx3};
   
    for (int i=0; i<6; i++)
    {
        ptr[i]->hienThiThongTin();
        cout << "--------------" << endl;
        delete ptr[i];
    }
    return 0;
}

