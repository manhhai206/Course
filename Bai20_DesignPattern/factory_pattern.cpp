#include <iostream>
#include <string>

using namespace std;

// Lớp cơ sở (Product)
class Sensor{
    public:
    /*
     * Dùng virtual function để xác định gọi method ở class nào mà
     * đối tượng nó trỏ đến chứ không phải nó tạo ra
     *  Pure virtual có định nghĩa bằng 0
     */
        virtual void readData() = 0;
};

/* Concrete Product: Các lớp con cụ thể được tạo ra từ Factory */
class TemperatureSensor : public Sensor{
    public:
        void readData() override {
            cout<<"reading temp data: "<<endl;
        }
};

/* Concrete Product: Các lớp con cụ thể được tạo ra từ Factory */
class HumiditySensor : public Sensor{
    public:
        void readData() override {
            cout<<"reading humidity data: "<<endl;
        }
};

/* Factory: Một class hoặc hàm đảm nhiệm việc tạo ra các đối tượng. */
class SensorFactory{
    public:
        static Sensor* createSensor(const string& sensorType){
            if(sensorType == "temp"){
                return new TemperatureSensor();     // trả về đối tượng TemperatureSensor
            }
            else if (sensorType == "humi"){
                return new HumiditySensor();        // trả về đối tượng PressureSensor
            }
            else{
                return nullptr;                     // trả về con trỏ null
            }
        }
};


int main(int argc, char const *argv[])
{
    Sensor* sensor = SensorFactory::createSensor("humi");
    /***************************************************************
     * Thay vì khởi tạo trực tiếp các đối tượng, 
     * Factory Pattern sử dụng một phương thức hoặc một lớp trung gian (Factory)
     * để quyết định loại đối tượng nào sẽ được khởi tạo 
     * dựa trên tham số đầu vào hoặc logic cụ thể.
     *************************************************************** */
    sensor->readData();
    return 0;
}

