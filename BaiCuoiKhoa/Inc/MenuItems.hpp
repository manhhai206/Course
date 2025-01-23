#ifndef MENUITEMS_HPP
#define MENUITEMS_HPP

#include <functional>
#include <string>
using namespace std;

class MenuItem
{
    private:
        int choice_;
        string description_;
        function<void()> action_;

    public:
        MenuItem(int choice, const string& description, function<void()>action)
            :choice_(choice), description_(description), action_(action) {}

        int getChoice() const { return choice_; }
        string getDescription() const { return description_; }
        void executeAction() const { action_(); }

};


#endif //MENUITEMS_HPP