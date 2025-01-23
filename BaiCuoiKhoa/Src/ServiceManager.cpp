#include "ServiceManager.hpp"
#include "UI.hpp"

using namespace std;

void ServiceManager::addService(const string& name, const string& description, const string& price){
    if(name.empty() || description.empty() || price.empty()) {
        UI::showMessage("All fields are required. ");
        return;
    }

    for(const auto& service : servicelist) {
        if (service.getName() == name) {
            UI::showMessage("Service " + name + "already rent");
            return;
        }
    }

    Service newService(name,description,price);
    servicelist.push_back(newService);
    UI::showMessage("Service " + name + " added to the service list. ");
}


void ServiceManager::editService(const string& name,const string& newName, const string& newDescription, const string& newPrice){
    for(auto& service : servicelist)
    {
        if(service.getName() == name )
        {
            service.setName(newName);
            service.setDescription(newDescription);
            service.setPrice(newPrice);
            UI::showMessage("Service updated successfully. ");
        }
    }
    UI::showMessage("Service not found. ");
}

void ServiceManager::deleteService(const string& name)
{
    for (auto it = servicelist.begin(); it != servicelist.end(); ++it)
    {
        if (it->getName() == name)
        {
            servicelist.erase(it);  // Xóa dịch vụ
            UI::showMessage("Service deleted successfully.");
            return;  // Thoát hàm sau khi xóa
        }
    }
    // Thông báo nếu không tìm thấy dịch vụ
    UI::showMessage("Service not found.");
}

void ServiceManager::listServices() const
{
    if (servicelist.empty())
    {
        UI::showMessage("No services available.");
        return;
    }

    // Duyệt qua danh sách và in thông tin từng dịch vụ
    for (const auto& service : servicelist)
    {
        UI::showMessage("Service Name: " + service.getName() +
                        ", Description: " + service.getDescription() +
                        ", Price: " + service.getPrice());
    }
}
