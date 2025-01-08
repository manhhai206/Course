#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************** 
 * @class EngineControlUnit
 * @brief Singleton Pattern dùng để quản lý tham số động cơ
 *         như nhiệt độ và tốc độ động cơ.
 ************************************************************** */
class EngineControlUnit 
{
    private:
        static EngineControlUnit* instance; /**< Static instance của EngineControlUnit class */
        int speed;                          /**< Tốc độ động cơ hiện tại (RPM) */
        float temperature;                  /**< Nhiệt độ động cơ hiện tại (°C) */
        float FuelInjectionRate;            /**< Mức nhiên liệu bơm vào động cơ */
        vector<int> historySpeed;           /**< Lịch sử tốc độ động cơ (RPM) */
        vector<float> historyTemp;          /**< Lịch sử nhiệt độ động cơ (°C) */

        /**
         * @brief Private constructor để ngăn chặn việc khởi tạo đối tượng từ bên ngoài.
         */
        EngineControlUnit() : speed(0), temperature(0.0f) 
        {
            cout << "===EngineControlUnit Initialized===\n";
        }

    public:
        /**
         * @brief Destructor để hủy đối tượng khởi tạo.
         */
        ~EngineControlUnit()
        {
            cout << "===EngineControlUnit Destroyed===\n";
        }
        
        /**
         * @brief Lấy instance duy nhất của lớp EngineControlUnit.
         * @return Con trỏ tới instance duy nhất.
         */
        static EngineControlUnit* getInstance() {
            if (instance == nullptr)
            {
                instance = new EngineControlUnit();
            }
            return instance;
        }

         /**
         * @brief Thiết lập tốc độ động cơ, kiểm tra giới hạn hợp lệ trước khi cập nhật.
         * @param speed Tốc độ động cơ (RPM), từ 0 đến 6000 RPM.
         * @return void
         */
        void setEngineSpeed(int speed)
        {
            if (speed >= 0 && speed <= 6000) {
                this->speed = speed;
                historySpeed.push_back(speed);
                cout << "Speed: " << speed << " RPM\n";
                setFuelInjectionRate();
            } else {
                cout << "Warning: Invalid speed! Must be between 0 and 6000 RPM.\n";
            }
        }

        /**
         * @brief Lấy tốc độ động cơ hiện tại.
         * @return int Tốc độ động cơ hiện tại (RPM).
         */
        int getEngineSpeed() const {
            return speed;
        }

        /**
         * @brief Thiết lập nhiệt độ động cơ, kiểm tra giới hạn hợp lệ trước khi cập nhật.
         * @param temperature Nhiệt độ động cơ (°C), từ -20 đến 120 °C.
         * @return void
         */
        void setEngineTemperature(float temperature)
        {
            if (temperature >= -20 && temperature <= 120) {
                this->temperature = temperature;
                historyTemp.push_back(temperature);
                cout << "Temperature: " << temperature << " C\n";
                setFuelInjectionRate();
            } else {
                cout << "Warning: Invalid temperature! Must be between -20 and 120 C.\n";
            }
        }

        /**
         * @brief Lấy nhiệt độ động cơ hiện tại.
         * @return float Nhiệt độ động cơ hiện tại (°C).
         */
        float getEngineTemperature() const {
            return temperature;
        }

        /**
         * @brief Hàm điều chỉnh mức nhiên liệu động cơ
         * @return void
         */
        void setFuelInjectionRate()
        {
            if(temperature > 100){
                FuelInjectionRate = 0.0f; /**<Dừng bơm nhiên liệu khi nhiệt độ quá mức */
                cout << "Warning: FuelInjectionRate reducted to 0.0 L/h.\n";
            } else {
                if(speed <= 1000){
                    FuelInjectionRate = 1.0f;
                } else if(speed <= 3000){
                    FuelInjectionRate = 3.0f;
                } else {
                    FuelInjectionRate = 5.0f;
                }
                cout << "Fuel Injection Rate: "<<FuelInjectionRate << "L/h.\n";
            }
        }

        /**
         * @brief Hàm giảm tốc độ động cơ bằng phanh
         * @return void
         */
        void brakeControlInteraction(){
            if(speed > 0 )
            {
                historySpeed.pop_back();
                speed -= 1000;
                historySpeed.push_back(speed);
            } else if( speed < 0)
            {
                historySpeed.pop_back();
                speed = 0;
                historySpeed.push_back(speed);
            }
             cout << "Brake Activated: Speed reduced to " << speed << " RPM\n";
        }

        /**
         * @brief Hiển thị thông tin chuẩn đoán về động cơ.
         * @return void
         */
        
        void diagnostics() const
        {
            cout << "\n=== Engine Diagnostics ===\n";
            cout << "Current Speed: " << speed << " RPM\n";
            cout << "Current Temperature: " << temperature << " C\n";

            /* Cảnh báo nếu nhiệt độ vượt ngưỡng an toàn */
            if (temperature > 100) 
            {
                cout << "Warning: Overheating! Temperature exceeds 100 C.\n";
            } 
            else 
            {
                cout << "Engine is operating within safe limits.\n";
            }

            /* Lịch sử tốc độ động cơ */
            cout << "\n--- Speed History ---\n";
            for (auto item : historySpeed)
            {
                cout << "Speed: " << item << " RPM\n";
            }

            /* Lịch sử nhiệt độ động cơ */
            cout << "\n--- Temperature History ---\n";
            for (auto item : historyTemp)
            {
                cout << "Temperature: " << item << " C\n";
            }
        }
};

/* @brief Static member initialization. */
EngineControlUnit* EngineControlUnit::instance = nullptr;

int main()
{
    EngineControlUnit* ecu = EngineControlUnit::getInstance();

    ecu->setEngineSpeed(1000);
    ecu->setEngineTemperature(80);

    ecu->setEngineSpeed(4000);
    ecu->setEngineTemperature(90);
    ecu->brakeControlInteraction(); /* Đạp phanh */

    ecu->setEngineSpeed(5000);
    ecu->setEngineTemperature(100);

    // Mo phỏng với giá trị  không hợp lệ
    ecu->setEngineSpeed(7000); // Invalid
    ecu->setEngineTemperature(130); // Invalid

    ecu->diagnostics();

    return 0;
}
