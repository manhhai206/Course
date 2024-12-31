#include <iostream>
#include <string>

using namespace std;

class SinhVienModel{
    private:
        string name;
        int age;
        string studentId;

    public:
        SinhVienModel(const string& name, int age, const string& studentId): name(name), age(age), studentId(studentId){}

        // setter method
        void setName(const string& newName){
            name = newName;
        }

        void setAge(int newAge){
            age = newAge;
        }

        void setStudentId(const string& newStudentId){
            studentId = newStudentId;
        }

        // getter method
        string getName() const{
            return name;
        }

        int getAge() const{
            return age;
        }

        string getStudentId() const{
            return studentId;
        }
};

class SinhVienView{
    public:
        void displayStudentInfo(const string& name, int age, const string& studentId){
            cout << "Thong tin sinh vien:" << endl;
            cout << "Ten: " << name << endl;
            cout << "Tuoi: " << age << endl;
            cout << "Ma so sinh vien: " << studentId << endl;
        }

        void inputStudentInfo(string& name, int& age, string& studentId){
            cout << "Nhap thong tin sinh vien:" << endl;

            cout << "Ten: ";
            getline(cin, name);

            cout << "Tuoi: ";
            cin >> age;
            cin.ignore();  // Bo qua ky tu newline trong buffer

            cout << "Ma so sinh vien: ";
            getline(cin, studentId);
        }
};

class SinhVienPresenter{
    private:
        SinhVienModel& model;
        SinhVienView&  view;

    public:
        SinhVienPresenter(SinhVienModel& m, SinhVienView& v): model(m), view(v){}

        void updateStudentInfo(){
            string name;
            int age;
            string studentId;
           
            view.inputStudentInfo(name, age, studentId);
            model.setName(name);
            model.setAge(age);
            model.setStudentId(studentId);
        }

        void showStudentInfo(){
            view.displayStudentInfo(model.getName(), model.getAge(), model.getStudentId());
        }
};

int main()
{
    // Tao model, view va presenter
    SinhVienModel model("Tuan", 20, "HTN123");
    SinhVienView view;
    SinhVienPresenter presenter(model, view);

    int choice;
    do{
        cout << "\n1. Hien thi thong tin sinh vien" << std::endl;
        cout << "2. Cap nhat thong tin sinh vien" << std::endl;
        cout << "3. Thoat" << std::endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore(); // Bo qua ky tu newline trong buffer
       
        switch (choice){
            case 1:
                presenter.showStudentInfo();
                break;
               
            case 2:
                presenter.updateStudentInfo();
                break;

            case 3:
                cout << "Thoat chuong trinh." << endl;
                break;

            default:
                cout << "Lua chon khong hop le!" << endl;
        }

    } while (choice != 3);

    return 0;
}
