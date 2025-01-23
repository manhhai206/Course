#include "Manager.hpp"

using namespace std;

/* Hiển thị menu chính cho quản lý khách sạn */
void Manager::showManagementMenu()
{
    // Khởi tạo Menu chính với các lựa chọn
    Menu mainMenu("Hotel Manager",  // Tiêu đề của Menu
    {
        // Lựa chọn 1: Quản lý nhân viên
        {1, "Manage Employee", [this]() { manageEmployees(); }}, 

        // Lựa chọn 2: Quản lý phòng
        {2, "Manage Room", [this]() { manageRooms(); }}, 

        // Lựa chọn 3: Quản lý dịch vụ
        {3, "Manage Service", [this]() { manageServices(); }}, 

        // Lựa chọn 0: Quay lại menu trước
        {0, "Back", [this]() { UI::showMessage("Back to the main Menu..."); }}  
    });

    // Hiển thị menu và xử lý lựa chọn người dùng
    mainMenu.showMenu();  /**< Hiển thị menu chính */
}

/* Quản lý nhân viên */
void Manager::manageEmployees()
{
    // Khởi tạo menu quản lý nhân viên
    Menu employeeMenu("Manage Employee",
    {
        // Lựa chọn 1: Thêm nhân viên
        {1, "Add an Employee ", [this]() { addEmployee(); }}, 

        // Lựa chọn 2: Sửa thông tin nhân viên
        {2, "Edit the Employee Information ", [this]() { editEmployee(); }}, 

        // Lựa chọn 3: Xóa thông tin nhân viên
        {3, "Delete the Employee Information ", [this]() { deleteEmployee(); }}, 

        // Lựa chọn 4: Xem danh sách nhân viên
        {4, "Watch the employee List ", [this]() { listEmployees(); }},

        // Lựa chọn 0: Quay lại menu trước
        {0, "Back", [this]() { UI::showMessage("Back to the main Menu..."); }}  
    });

    // Hiển thị menu quản lý nhân viên
    employeeMenu.showMenu();  /**< Hiển thị menu quản lý nhân viên */
}

/* Thêm nhân viên */
void Manager::addEmployee() 
{   
    while (true) 
    {
        UI::showMessage("=== Add The employee ===");

        // Nhập thông tin từ người dùng
        string name = UI::getInputString("Enter employee name: ");
        string phoneNumber = UI::getInputString("Enter phone number (ID): ");
        string position = UI::getInputString("Enter job position: ");

        // Thêm nhân viên mới vào danh sách
        employeeManager.addEmployee(accountList, name, phoneNumber, position);

        // Thêm nhân viên mới vào danh sách
        UI::showMessage("The employee " + name + " has been addded successfully. ");

        // Tự động đăng ký tài khoản cho nhân viên với mật khẩu mặc định
        UI::showMessage("The account of the Employee was registed successfully with defalul password '123456'.");

        // Hiển thị tùy chọn để thêm nhân viên khác
        int choice = UI::getUserChoice("Add another employee (1) or Back (0): ");
        
        if (choice == 0) {
            break;  // Quay lại nếu người dùng chọn 0
        }
    }
}

void Manager::editEmployee() 
{
    UI::showMessage("Edit the Employee Information...");
    // Hiển thị danh sách nhân viên
    employeeManager.listEmployees();

    UI::showMessage("Please input the ID of the employee you want to edit:");

    // Nhập ID của nhân viên cần chỉnh sửa
    string id = UI::getInputString("Input ID: ");
    // Nhập tên mới của nhân viên cần chỉnh sửa
    string newName = UI::getInputString("Input new Name: ");
    // Nhập vị trí mới của nhân viên cần chỉnh sửa
    string newPosition  = UI::getInputString("Input new Position: ");

    employeeManager.editEmployeeById(id,newName,newPosition);
    UI::showMessage("Employee information updated successfully.");
}

void Manager::deleteEmployee()
{
    UI::showMessage("Permanently delete employee...");
    // Hiển thị danh sách nhân viên
    employeeManager.listEmployees();

    UI::showMessage("Please input the name or ID of the employee to delete:");

    //Nhập tên ID cần xóa
    string id = UI::getInputString("Input ID or name: ");

    employeeManager.deleteEmployeeById(id);
    UI::showMessage("Employee deleted successfully.");
}

void Manager::listEmployees() {
    UI::showMessage("=== The employee List ===");

    employeeManager.listEmployees();

    UI::showMessage("------------------");
}

/* Quản lý phòng */
void Manager::manageRooms() {
    Menu roomMenu("Room Management", 
    {  
        // Lựa chọn 1: Thêm phòng
        {1, "Add Room", [this]() { addRoom(); }},  
        // Lựa chọn 2: Sửa thông tin phòng
        {2, "Edit Room Information", [this]() { editRoom(); }},  
        // Lựa chọn 3: Xóa phòng
        {3, "Delete Room", [this]() { deleteRoom(); }},  
        // Lựa chọn 4: Xem danh sách phòng
        {4, "List Rooms", [this]() { listRooms(); }},  
        // Lựa chọn 0: Quay lại menu quản lý
        {0, "Back", []() { UI::showMessage("Back to the management menu..."); }}  
    });

    roomMenu.showMenu();  // Hiển thị menu quản lý phòng
}

void Manager::addRoom() 
{
    UI::showMessage("Adding Room...");  // Hiển thị thông báo bắt đầu thêm phòng

    while (true) {
        // Thu thập thông tin phòng từ người dùng
        string roomNumber = UI::getInputString("Enter room number: ");
        string roomType = UI::getInputString("Enter room type: ");
        string bedCount = UI::getInputString("Enter bed count: ");
        string price = UI::getInputString("Enter price: ");

        // Thêm phòng vào hệ thống
        roomManager.addRoom(roomNumber, roomType, bedCount, price);

        // Thông báo thành công
        UI::showMessage("Room " + roomNumber + " added successfully.");

        int choice = UI::getUserChoice("Add another room (1) or Back (0): ");
        if (choice == 0) {
            break; 
        }
    }
}


void Manager::editRoom() {
    UI::showMessage("Editing Room Information...");  // Hiển thị thông báo sửa phòng
    
    // Hiển thị danh sách các phòng
    roomManager.listRooms();

    UI::showMessage("Please input the Room you want to edit:");
    
    string roomNumber = UI::getInputString("Enter room number: ");
    string newRoomType = UI::getInputString("Enter new Type: ");
    string newBedCount = UI::getInputString("Enter new Bed Count: ");
    string newPrice = UI::getInputString("Enter new Price: ");

    // Sửa thông tin phòng
    roomManager.editRoom(roomNumber, newRoomType, newBedCount, newPrice);
    UI::showMessage("Room information updated successfully.");
}

void Manager::deleteRoom() 
{
    UI::showMessage("Permanently delete Room...");
    
    // Hiển thị danh sách phòng hiện có
    roomManager.listRooms();
    
    UI::showMessage("Please input the room number to delete:");

    // Nhập số phòng cần xóa
    string roomNumber = UI::getInputString("Input Room Number: ");
    
    // Xóa phòng
    roomManager.deleteRoom(roomNumber);
    UI::showMessage("Room " + roomNumber + " deleted successfully.");
}


void Manager::listRooms() {
    UI::showMessage("=== The Room List ===");

    // Liệt kê tất cả phòng
    roomManager.listRooms();

    UI::showMessage("------------------");
}


/* Quản lý dịch vụ */
void Manager::manageServices() {
    Menu serviceMenu("Service Management", {  // Menu quản lý dịch vụ
        {1, "Add Service", [this]() { addService(); }},  // Lựa chọn 1: Thêm dịch vụ
        {2, "Edit Service Information", [this]() { editService(); }},  // Lựa chọn 2: Sửa thông tin dịch vụ
        {3, "Delete Service", [this]() { deleteService(); }},  // Lựa chọn 3: Xóa dịch vụ
        {4, "List Services", [this]() { listServices(); }},  // Lựa chọn 4: Xem danh sách dịch vụ
        {0, "Back", []() { UI::showMessage("Back to the management menu..."); }}  // Lựa chọn 0: Quay lại menu quản lý
    });

    serviceMenu.showMenu();  // Hiển thị menu quản lý dịch vụ
}

void Manager::addService() {
    UI::showMessage("Adding Service...");  // Hiển thị thông báo thêm dịch vụ
    // Thêm logic thêm dịch vụ ở đây
}

void Manager::editService() {
    UI::showMessage("Editing Service Information...");  // Hiển thị thông báo sửa dịch vụ
    // Thêm logic sửa dịch vụ ở đây
}

void Manager::deleteService() {
    UI::showMessage("Deleting Service...");  // Hiển thị thông báo xóa dịch vụ
    // Thêm logic xóa dịch vụ ở đây
}

void Manager::listServices() {
    UI::showMessage("Listing Services...");  // Hiển thị thông báo liệt kê dịch vụ
    // Thêm logic liệt kê dịch vụ ở đây
}
