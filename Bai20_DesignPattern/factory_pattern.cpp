#include <iostream>
#include <string>

using namespace std;

// Abstract class
class Sensor{
    public:
        virtual void readData() = 0;
};

// Temperature class
class TemperatureSensor : public Sensor{
    public:
        void readData() override {
            cout<<"reading temp data: "<<endl;
        }
};

// Humidity class
class HumiditySensor : public Sensor{
    public:
        void readData() override {
            cout<<"reading humidity data: "<<endl;
        }
};

// Factory class (Creator)
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
    sensor->readData();
    return 0;
}

