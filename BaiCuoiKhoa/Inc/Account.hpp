#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>
#include <vector>

using namespace std;

class Account {
    private:
        string username;    /**< Tên tài khoản */
        string password;    /**< Mật khẩu */
    
    public:
        /* Khởi tạo constructer mặc định */
        Account();

        /* Khởi tạo constructer có tham số truyền vào */
        Account(const string& username,const string& password); 

        //Getter và Setter cho từng thuộc tính
        string getUsername() const;
        string getPassword() const;
        void setPassword(const string& password);

        /* Kiểm tra tài khoản nếu tồn tại*/
        static bool accountExists(const vector<Account>& accountList, const string& username);

        /* Phương thức static để đăng ký và đăng nhập */
        static bool registerAccount(vector<Account>& accountList, const string& username, const string& password);
        static bool login(const vector<Account>& accountList, const string& username, const string& password);
};

extern vector<Account> accountList;

#endif //ACCOUNT_HPP