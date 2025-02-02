#include "Account.hpp"
#include "Manager.hpp"
#include "EmployeeManager.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(){ 

    Account adminAccount("admin", "1");  // Tài khoản admin
    Account employeeAccount("receiptionist", "1"); // Tài khoản lễ tân
    accountList.push_back(adminAccount);
    accountList.push_back(employeeAccount);

    string account, password;

    cout << "\n---- Enter the ID name ----" << endl;
    
    // Nhập tài khoản (có thể là số điện thoại hoặc account)
    cout << "Enter the ID (Account/Phone number): ";
    cin >> account;

    // Nhập mật khẩu
    cout << "Enter the password: ";
    cin >> password;

    // Kiểm tra đăng nhập
    if (Account::login(accountList, account, password)) {
        cout << "Login sucessfully !" << endl;

        // Kiểm tra nếu tài khoản là "admin"
        if (account == "admin") {
            cout << "Hello Manager !" << endl;
            Manager manager;
            manager.showManagementMenu();  // Hiển thị menu quản lý
        } else if(account == "receiptionist"){
            cout << "Hello Receiptionist !" << endl;
            
        }

    } else {
        cout << "Login Failse! The ID or password is not correct." << endl;
    }

    return 0;
}
