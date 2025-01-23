#ifndef EMPLOYEEMANAGER_HPP
#define EMPLOYEEMANAGER_HPP

#include "Account.hpp"
#include "Employee.hpp"
#include <vector>
#include <string>
using namespace std;

class EmployeeManager {
    private:
        vector<Employee> Employee_;
        int employeeCounter = 0;    /**< Biến đếm số lượng nhân viên */

        /* Tạo ID cho nhân viên */
        string generateEmployeeID(const string& position);

        /* Tìm nhân viên theo tên ID */
        Employee* findEmployeeByID(const string& id);

    public:
        /* Thêm nhân viên với ID tự động */
        void addEmployee(vector<Account>& accountList, const string& name, const string& phoneNumber, const string& position);

        /* Sửa thông tin nhân viên dựa theo ID */
        void editEmployeeById(const string& id, const string& newName, const string& newPosition);
    
        /* Xóa nhân viên dựa trên ID */
        void deleteEmployeeById(const string& id);
    
        /* Set ca làm việc cho nhân viên */
        void setWorkShift(const string& id, const string& shift);
    
        /* Xem danh sách thông tin của tất cả nhân viên */
        void listEmployees() const;
};

#endif //EMPLOYEEMANAGER_HPP