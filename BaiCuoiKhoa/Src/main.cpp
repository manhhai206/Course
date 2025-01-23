#include "Account.hpp"
#include "Manager.hpp"
#include "EmployeeManager.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(){ 

    Account adminAccount("admin", "123456");  // Tài khoản admin
    Account employeeAccount("user", "123456"); // Tài khoản người dùng
    accountList.push_back(adminAccount);
    accountList.push_back(employeeAccount);

    std::string account, password;

    std::cout << "\n---- Enter the ID name ----" << std::endl;
    
    // Nhập tài khoản (có thể là số điện thoại hoặc account)
    std::cout << "Enter the ID (Account/Phone number): ";
    std::cin >> account;

    // Nhập mật khẩu
    std::cout << "Enter the password: ";
    std::cin >> password;

    // Kiểm tra đăng nhập
    if (Account::login(accountList, account, password)) {
        std::cout << "Login sucessfully !" << std::endl;

        // Kiểm tra nếu tài khoản là "admin"
        if (account == "admin") {
            std::cout << "Hello Manager!" << std::endl;
            Manager manager;
            manager.showManagementMenu();  // Hiển thị menu quản lý
        } else {
            std::cout << "Hello user!" << std::endl;
            // Gọi menu người dùng (nếu cần thêm chức năng cho người dùng bình thường)
        }

    } else {
        std::cout << "Login Failse! The ID or password is not correct." << std::endl;
    }

    return 0;
}
