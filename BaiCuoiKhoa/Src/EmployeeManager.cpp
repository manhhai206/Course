#include "EmployeeManager.hpp"
#include "UI.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

string EmployeeManager::generateEmployeeID(const string& position)
{
    employeeCounter++; // Tăng bộ đếm nhân viên
    std::stringstream ss;

    /* Tạo tiền tố ID theo chức vụ */
    if (position == "Waiter") {
        ss << "WT";
    } else if (position == "Security") {
        ss << "SE";
    } else if (position == "Receiptionist") {
        ss << "RE";
    } else {
        ss << "ST"; 
    }

    /**
     * Tạo số thứ tự ID và đảm bảo có 3 chữ số
     * setw(3) để đảm bảo số thứ tự có độ dài tối thiểu là 3 chữ số.
     * setfill('0') để thêm các số 0 vào bên trái nếu số chưa đủ độ dài.
     * */
    ss << setw(3) << setfill('0') << employeeCounter; 
    return ss.str(); // Trả về ID đã tạo
}

/* Thêm nhân viên mới với ID và tự động đăng ký tài khoản */
void EmployeeManager::addEmployee(vector<Account>& accountList, const string& name, const string& phoneNumber, const string& position)
{
    /* Kiểm tra nếu có số điện thoại tồn tại */
    if(Account::accountExists(accountList,phoneNumber))
    {
       UI::showMessage("This phone number is already registed ");
       return; 
    }

    /* Tạo ID tự động cho nhân viên mới */
    string id = generateEmployeeID(position);

    /* Thêm nhân viên mới vào danh sách */
    Employee_.emplace_back(id, name, phoneNumber, position);
    UI::showMessage("Employee " + name + " with ID - " + id +" was added successfully ! ");

    /* Tự động đăng ký tài khoản cho nhân viên với mật khẩu mặc định */
    Account::registerAccount(accountList, phoneNumber, "123456");
    UI::showMessage("Account for employee was registed with the defaul password ! ");
}

/* Sửa thông tin nhân viên dựa vào ID */
void EmployeeManager::editEmployeeById(const string& id, const string& newName, const string& newPosition)
{
    // Tìm nhân viên dựa trên ID
    Employee* employee = findEmployeeByID(id);

    // Nếu tìm thấy nhân viên
    if (employee) {
        // Kiểm tra thông tin mới trước khi cập nhật
        if (newName.empty() || newPosition.empty()) {
            UI::showMessage("Invalid name or position. Please provide valid information.");
            return;
        }

        // Cập nhật thông tin
        employee->setName(newName);
        employee->setPosition(newPosition);

        // Hiển thị thông báo thành công
        UI::showMessage("The employee information has been successfully updated.");
    } else {
        // Không tìm thấy nhân viên
        UI::showMessage("Employee with the given ID was not found.");
    }
}

/* Xóa nhân viên dựa trên ID */
void EmployeeManager::deleteEmployeeById(const string& id)
{
    // Sử dụng std::remove_if để tìm và xóa nhân viên có ID khớp
    auto it = remove_if(Employee_.begin(), Employee_.end(), [&id](const Employee& emp) {
        return emp.getID() == id;
    });

    if(it != Employee_.end()) {
        Employee_.erase(it,Employee_.end());
        UI::showMessage("The employee with the ID" + id + "has been deleted. ");
    } else {
        UI::showMessage("The employee with given ID was not found. ");
    }
}

/* Đặt ca làm việc cho nhân viên */
void EmployeeManager::setWorkShift(const string& id, const string& shift)
{
    // Tìm nhân viên theo ID
    Employee* employee = findEmployeeByID(id);

    if(employee == nullptr) {
        // Hiển thị thông báo nếu không tìm thấy nhân viên
        UI::showMessage("The employee with given ID " + id + " was not found.");
        return;
    }

    // Đặt ca làm việc
    employee->setWorkShift(shift);
    
    UI::showMessage("Our shift of employee " + employee->getName() + "has been successfully updated " + shift);
};

/* Xem danh sách thông tin của tất cả nhân viên */
void EmployeeManager::listEmployees() const 
{
    if (Employee_.empty()) {
        UI::showMessage("No employees found.");
    } else {
        for (const auto& employee : Employee_) {
            UI::showMessage("ID: " + employee.getID() + 
                            ", Name: " + employee.getName() + 
                            ", Phone Number: " + employee.getPhoneNumber() + 
                            ", Position: " + employee.getPosition() +
                            ", Work Shift: " + employee.getWorkShift());
        }
    }
}

/* Tìm nhân viên theo ID */
Employee* EmployeeManager::findEmployeeByID(const string& id)
{
    for(auto& employee : Employee_) {
        if(employee.getID() == id) {
            return &employee;
        }
    }
    
    return nullptr;
}
