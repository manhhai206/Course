#include <iostream>
using namespace std;

// Component: Giao diện chung
class Sensor {
public:
    virtual void readData() = 0;
    virtual ~Sensor() = default;
};

// Concrete Component: Cảm biến nhiệt độ
class TemperatureSensor : public Sensor {
public:
    void readData() override {
        cout << "Reading temperature data..." << endl;
    }
};

// Decorator: Lớp cơ sở cho các Decorator
class SensorDecorator : public Sensor {
protected:
    Sensor* wrappedSensor;

public:
    SensorDecorator(Sensor* sensor) : wrappedSensor(sensor) {}
    virtual void readData() override {
        wrappedSensor->readData();  // Chuyển tiếp lời gọi
    }
};

// Concrete Decorator: Thêm tính năng ghi log
class LoggingSensor : public SensorDecorator {
public:
    LoggingSensor(Sensor* sensor) : SensorDecorator(sensor) {}

    void readData() override {
        cout << "LOG: sensor data" << endl;
        SensorDecorator::readData();  // Gọi phương thức của lớp cha
    }
};

// Concrete Decorator: Thêm tính năng cảnh báo
class AlertingSensor : public SensorDecorator {
public:
    AlertingSensor(Sensor* sensor) : SensorDecorator(sensor) {}

    void readData() override {
        SensorDecorator::readData();  // Gọi phương thức của lớp cha
        cout << "ALERT: Data exceeds threshold!" << endl;
    }
};

int main() {
    // Tạo cảm biến nhiệt độ gốc
    Sensor* tempSensor = new TemperatureSensor();

    // Bọc cảm biến với tính năng ghi log
    tempSensor = new LoggingSensor(tempSensor);

    // Bọc thêm tính năng cảnh báo
    tempSensor = new AlertingSensor(tempSensor);

    // Gọi phương thức đọc dữ liệu
    tempSensor->readData();

    // Giải phóng bộ nhớ
    delete tempSensor;

    return 0;
}
