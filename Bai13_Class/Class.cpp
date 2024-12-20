#include <iostream>
#include <string>
using namespace std;

class Student {

    public:
        string name;  //tên sinh viên
        int id;       //mã sinh viên
        static int count;  //số lượng

        void display() {
            cout << "Student Name: " << name << ", ID: " << id << endl;
        }

        Student(string name, int id) { // Constructor
            this->name = name;
            this->id = id;
            count++;  
        }

        ~Student() { // Destructor
            count--; 
        }

        static int getCount() { //static method
            return count;
        }
};

int Student::count = 0; // cấp pháp địa chỉ cho count

int main() {
    Student s1("Hai", 206);  
    s1.display();
    cout << "Total students: " << Student::getCount() << endl;

    Student s2("Ha", 207);   
    s2.display();
    cout << "Total students: " << Student::getCount() << endl;

    {
        Student s3("Ly", 100); 
        s3.display();
        cout << "Total students: " << Student::getCount() << endl;
    }  

    cout << "The last total st: " << Student::getCount() << endl;

    return 0;
}
