#ifndef MENU_HPP
#define MENU_HPP

#include "MenuItems.hpp"
#include "UI.hpp"
#include <vector>
#include <string>
#include <initializer_list>

using namespace std;

class Menu
{
    private:
        string title_;                
        vector<MenuItem> items_;     

    public:
        /* Constructor để khởi tạo Menu */
        Menu(const string& title, initializer_list<MenuItem> items)
            : title_(title), items_(items) {}

        /* Hiển thi menu và lựa chọn */
        void showMenu()
        {
            int choice;
            do
            {
                /* Hiển thị tiêu đề Menu */
                UI::showMessage("\n====== " + title_ + " ======");

                /* Hiển thị từng mục tiêu */
                for(const auto& item : items_)
                {
                    UI::showMessage(to_string(item.getChoice()) + ". " + item.getDescription());
                }

                /* Lấy lựa chọn từ người dùng */
                choice = UI::getUserChoice("Please chooce a fearture: ");
                
                /* Thực hiện hành động cho lựa chọn */
                bool validChoice = false;
                for(const auto& item : items_) 
                {
                    if(item.getChoice() == choice) 
                    {
                        item.executeAction(); //Thực hiện hành động
                        validChoice =  true;
                        break;
                    }
                }

                /* Thông báo lựa chọn không hợp lệ */
                if(!validChoice){
                    UI::showMessage("Invalid choose, please try again. ");
                }
                
            } while(choice != 0);
        }
};

#endif //MENU_HPP