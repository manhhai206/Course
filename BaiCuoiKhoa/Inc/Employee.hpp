#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

class Employee
{
    private:
        string id_;
        string name_;
        string phoneNumber_;
        string position_;
        string workShift_;
        string workingHours_;

    public:
        /* Constructor */
        Employee(const string& id, const string& name, const string& phoneNumber, const string& position)
            : id_(id), name_(name), phoneNumber_(phoneNumber), position_(position), workingHours_("Chua set up") {}

        /* Setter và Getter */
        string getID() const { return id_; }
        string getName() const { return name_; }
        string getPhoneNumber() const { return phoneNumber_; }
        string getPosition() const { return position_; }
        string getWorkShift() const { return workShift_; }
        string getWorkShiftHours() const { return workingHours_; }

        void setName(const string& name) { name_ = name; }
        void setPosition(const string& position) {position_ = position; }
        void setWorkShift(const string& shift) { workShift_= shift; }
        void setWorkShiftHours(const string& hours) { workingHours_=hours; }

};

#endif //EMPLOYEE_H