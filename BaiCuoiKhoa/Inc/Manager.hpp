#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Menu.hpp"
#include "UI.hpp"
#include "EmployeeManager.hpp"
#include "RoomManager.hpp"
#include "ServiceManager.hpp"

using namespace std;

class Manager 
{
    public:
        /* Hiển thị menu quản lý nhân viên chính */
        void showManagementMenu();

    private:

        EmployeeManager employeeManager;
        RoomManager roomManager;
        ServiceManager serviceManager;

        /* Các phương thức dùng để quản lý nhân viên */
        void manageEmployees();     /**< Quản lý nhân viên */
        void manageRooms();         /**< Quản lý phòng */
        void manageServices();      /**< Quản lý dịch vụ */

        /* Các phương thức cụ thể cho từng hành động quản lý nhân viên */
        void addEmployee();         /**< Thêm nhân viên vào hệ thống */
        void editEmployee();        /**< Sửa thông tin nhân viên */
        void deleteEmployee();      /**< Xóa nhân viên khỏi hệ thống */
        void listEmployees();       /**< Liệt kê danh sách nhân viên */

        /* Các phương thức cụ thể cho việc quản lý phòng */
        void addRoom();             /**< Thêm phòng mới */
        void editRoom();            /**< Sửa thông tin phòng */
        void deleteRoom();          /**< Xóa phòng khỏi hệ thống */
        void listRooms();           /**< Liệt kê danh sách phòng */

        /* Các phương thức cụ thể cho việc quản lý dịch vụ */
        void addService();          /**< Thêm dịch vụ mới */
        void editService();         /**< Sửa thông tin dịch vụ */
        void deleteService();       /**< Xóa dịch vụ khỏi hệ thống */
        void listServices();        /**< Liệt kê danh sách dịch vụ */
};

#endif //MANAGER_HPP
