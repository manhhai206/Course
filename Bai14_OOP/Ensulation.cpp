#include <iostream>
using namespace std;

class DoiTuong 
{
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

int main() {
    SinhVien sv;
    sv.setName("Hai");
    sv.setId(206);
    sv.setMajor("Dien Tu");
    sv.display();

    cout << "-----------------------" << endl;

    HocSinh hs;
    hs.setName("Hung");
    hs.setId(4);
    hs.setClass("12A4");
    hs.display();

    cout << "-----------------------" << endl;

    GiaoVien gv;
    gv.setName("Duy");
    gv.setId(7);
    gv.setSubject("Embedded System");
    gv.display();

    return 0;
}
