// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>

// // Interface for observers (display, logger, etc.)
// class Observer {
//     public:
//         /***************************************************************
//          * Pure virtual function thì không cung cấp cách triển khai
//          * Các lớp kế thừa bắt buộc ghi đè lại
//          * Bắt buộc các lớp con phải triển khai lại
//          ************************************************************** */
//         virtual void update(float temperature, float humidity, float light) = 0;
// };

// // Subject (SensorManager) holds the state and notifies observers
// class SensorManager 
// {
//     float temperature;
//     float humidity;
//     float light;

//     /* Lưu các observer đã đăng ký vào vector */
//     std::vector<Observer*> observers;

//     public:
//         /* Lưu các observer vào mảng động bằng push_back */
//         void registerObserver(Observer* observer) {
//             observers.push_back(observer);
//         }

//         /* Xóa */
//         void removeObserver(Observer* observer) {
//             observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
//         }

//         /* Thông báo và chạy vòng loop để duyệt hết phần tử trong vector và gọi method update */
//         void notifyObservers() {
//             for (auto observer : observers) {
//                 observer->update(temperature, humidity, light);
//             }
//         }

//         void setMeasurements(float temp, float hum, float lightLvl) {
//             temperature = temp;
//             humidity = hum;
//             light = lightLvl;
//             notifyObservers();
//         }
// };

// // Display component (an observer)
// class Display : public Observer 
// {
//     public:
//         void update(float temperature, float humidity, float light) override {
//             std::cout << "Display: Temperature: " << temperature
//                     << ", Humidity: " << humidity
//                     << ", Light: " << light << std::endl;
//         }
// };

// // Logger component (an observer)
// class Logger : public Observer 
// {
//     public:
//         void update(float temperature, float humidity, float light) override {
//             std::cout << "Logging data... Temp: " << temperature
//                     << ", Humidity: " << humidity
//                     << ", Light: " << light << std::endl;
//         }
// };

// int main() {
//     //Tạo subject
//     SensorManager sensorManager;

//     //Tạo các observer
//     Display display;
//     Logger logger;

//     //Đăng ký Observer với Subject
//     sensorManager.registerObserver(&display);
//     sensorManager.registerObserver(&logger);

//     //Cập nhật lần 1
//     sensorManager.setMeasurements(25.0, 60.0, 700.0); // Simulate sensor data update

//     //Cập nhật lần 2
//     sensorManager.setMeasurements(26.0, 65.0, 800.0); // Another sensor update

//     return 0;
// }


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Observer
{
    public:
        virtual void update(float throttle, float speed) = 0;
        virtual ~Observer() = default;
};

class Subject
{
    public:
        virtual void registerObserver(Observer *observer) = 0;
        virtual void removeObserver(Observer *observer) = 0;
        virtual void notifyObservers() = 0;
        virtual ~Subject() = default;
};

class SensorDataManager : public Subject
{
    private:
        float throttle;     // cảm biến bàn đạp ga
        float speed;        // cảm biến tốc độ
        vector<Observer*> observers;

    public:
        void registerObserver(Observer* observer)
        {
            observers.push_back(observer);
        }

        void removeObserver(Observer* observer)
        {
            observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
        }

        void notifyObservers()
        {
            for (auto observer : observers)
            {
                observer->update(throttle, speed);
            }
        }

        void setSensorData(float throttleValue, float speedValue)
        {
            throttle = throttleValue;
            speed = speedValue;
            notifyObservers(); // Thông báo khi dữ liệu cảm biến thay đổi
        }
};

// Concrete Observer: Dashboard
class DashBoardDisplay : public Observer
{
    public:
        void update(float throttle, float speed) override
        {
            cout << "Dashboard: Current speed = " << speed << " km/h, Throttle = " << throttle << "%" << endl;
        }
};

// Concrete Observer: Engine Controller
class EngineController : public Observer
{
    public:
        void update(float throttle, float speed) override
        {
            cout << "Engine Controller: Adjusting engine power based on throttle = " << throttle << "%" << endl;
        }
};

// Concrete Observer: ABS Controller
class ABSController : public Observer
{
    public:
        void update(float throttle, float speed) override
        {
            if (speed > 100){
                cout << "ABS Controller: Speed is high (" << speed << " km/h), monitoring for possible skidding." << endl;
            } else {
                cout << "ABS Controller: Speed is safe." << endl;
            }
        }
};

int main(int argc, char const *argv[])
{
    // Tạo Subject (Sensor Data Manager)
    SensorDataManager sensorDataManager;

    // Tạo các Observers
    DashBoardDisplay dashboard;
    EngineController engineController;
    ABSController    absController;

    // Đăng ký Observers với Subject
    sensorDataManager.registerObserver(&dashboard);
    sensorDataManager.registerObserver(&engineController);
    sensorDataManager.registerObserver(&absController);

    // Cập nhật dữ liệu cảm biến lần 1
    sensorDataManager.setSensorData(30, 80);

    // Cập nhật dữ liệu cảm biến lần 2
    sensorDataManager.setSensorData(60, 120);

    // Gỡ bỏ Dashboard
    sensorDataManager.removeObserver(&dashboard);

    // Cập nhật dữ liệu cảm biến lần 3
    sensorDataManager.setSensorData(50, 100);
    return 0;
}


