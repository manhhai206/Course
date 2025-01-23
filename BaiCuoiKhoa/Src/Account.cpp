#include "Account.hpp"
using namespace std;

/* Biến lưu trữ danh sách account */
vector<Account> accountList;    /**< Chỉ định toàn cục*/

/* Constructor mặc định */
Account::Account() : username(""), password("") {}

/* Constructor có tham số truyền vào */
Account::Account(const string& username, const string& password)
 : username(username), password(password) {}

/* Getter cho username */
string Account::getUsername() const {
    return username;
}

/* Getter cho password */
string Account::getPassword() const {
    return password;
}

/* Setter cho password */
void Account::setPassword(const string& password){
    this->password = password;
}

/* Kiểm tra nếu tài khoản đã tồn tại trong danh sách */
bool Account::accountExists(const vector<Account>& accountList, const string& username){
    for(const auto& account : accountList) {
        if(account.getUsername() == username) {
            return true;
        }
    }
    return false;
}

/* Đăng kí tài khoản */
bool Account::registerAccount(vector<Account>& accountList, const string& username, const string& password){
    for(const auto& acc : accountList){
        if(acc.getUsername() == username){
            return false;   /* Tên tài khoản đã tồn tại */
        }
    }

    Account newAccount(username, password);
    accountList.push_back(newAccount);
    return true; /* Tạo thành công */
}

/* Đăng nhập */
bool Account::login(const vector<Account>& accountList, const string& username, const string& password) {
    for (const auto& acc : accountList) {
        if (acc.getUsername() == username && acc.getPassword() == password) {
            return true; // Đăng nhập thành công
        }
    }
    return false; // Đăng nhập thất bại
}