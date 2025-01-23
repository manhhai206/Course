#ifndef SERVICEMANAGER_HPP
#define SERVICEMANAGER_HPP

#include <vector>
#include <string>

using namespace std;

class Service
{
private:
    string name_;                /**< Tên dịch vụ */
    string description_;         /**< Mô tả dịch vụ */
    string price_;               /**< Giá dịch vụ */

public:
    /* Constructor */
    Service(const string& name, const string& description, const string& price)
        : name_(name), description_(description), price_(price) {}

    // Getters
    string getName() const { return name_; }
    string getDescription() const { return description_; }
    string getPrice() const { return price_; }

    // Setters
    void setName(const string& newName) { name_ = newName; }
    void setDescription(const string& newDescription) { description_ = newDescription; }
    void setPrice(const string& newPrice) { price_ = newPrice; }
};


class ServiceManager
{
    private:
        vector<Service> servicelist;

    public:
        /* Thêm dịch vụ */
        void addService(const string& name, const string& description, const string& price);

        /* Sửa thông tin dịch vụ */
        void editService(const string& name, const string& newName, const string& newDescription, const string& newPrice);

        /* Xóa dịch vụ */
        void deleteService(const string& name);
        
        /* Liệt kê danh sách dịch vụ */
        void listServices() const;       

};

#endif //SERVICEMANAGER