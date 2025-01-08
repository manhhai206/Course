#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Observer */
class Observer 
{
    public:
        virtual void update(int speed, float temperature) = 0;
        virtual ~Observer() {}
};

/* Subject */
class Engine
{
    public:
        virtual void addObserver(Observer* observer) = 0;
        virtual void removeObserver(Observer* observer) = 0;
        virtual void notifyObservers() = 0;
        virtual void setEngineState(int speed, float temperature) = 0;
        virtual void getState() = 0;
        virtual ~Engine() {}
};

class SensorDataManager : public Engine
{
    private:
        int speed;
        float temperature;
        vector<Observer*> observers;

    public:
        SensorDataManager() : speed(0), temperature(0.0f) {}

        void addObserver(Observer* observer) override
        {
            observers.push_back(observer);
        }

        void removeObserver(Observer* observer) override
        {
            observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
        }

        void notifyObservers() override
        {
            for (auto observer : observers)
            {
                observer->update(speed, temperature);
            }
        }

        void setEngineState(int speed, float temperature) override
        {
            this->speed = speed;
            this->temperature = temperature;
            notifyObservers();
        }

        void getState() override
        {
            cout << "Engine State: Speed = " << speed << " RPM, Temperature = " << temperature << " C\n";
        }
};

class CoolingSystem : public Observer
{
    public:
        void update(int speed, float temperature) override
        {
            if (temperature > 90)
            {
                cout << "CoolingSystem: Activating cooling system, temperature = " << temperature << " C\n";
            }
            else
            {
                cout << "CoolingSystem: No action needed. Speed = " << speed << " RPM, Temperature = " << temperature << " C\n";
            }
        }
};

class WarningSystem : public Observer
{
    public:
        void update(int speed, float temperature) override
        {
            if (temperature > 100)
            {
                cout << "WarningSystem: Critical! Overheating detected. Temperature = " << temperature << " C\n";
            }
            else if (speed > 6000)
            {
                cout << "WarningSystem: Warning! Speed exceeds 6000 RPM. Speed = " << speed << " RPM\n";
            }
            else
            {
                cout << "WarningSystem: Operating within safe limits. Speed = " << speed << " RPM, Temperature = " << temperature << " C\n";
            }
        }
};

class EngineControlUnit : public Observer
{   
    private:
        float fuelInjectionRate;

    public:
        EngineControlUnit() : fuelInjectionRate(5.0f) {}

        void update(int speed, float temperature) override
        {
            if (speed > 6000 || temperature > 100)
            {
                fuelInjectionRate -= 0.5f; // Reduce fuel injection rate
                cout << "EngineControlUnit: Adjusting performance. Reducing fuel injection rate to " 
                     << fuelInjectionRate << " L/h\n";
            }
            else if (speed < 2000 && temperature < 80)
            {
                fuelInjectionRate += 0.5f; // Increase fuel injection rate
                cout << "EngineControlUnit: Optimizing performance. Increasing fuel injection rate to " 
                     << fuelInjectionRate << " L/h\n";
            }
            else
            {
                cout << "EngineControlUnit: Maintaining fuel injection rate at " 
                     << fuelInjectionRate << " L/h\n";
            }
        }
};

class DashBoardDisplay : public Observer
{
    public:
        void update(int speed, float temperature) override
        {
            if(temperature > 100){
                cout << " DashBoardDisplay: Temperature is over 100 C\n";
                temperature -= 10;
            } else {}
        }
};

int main()
{
    SensorDataManager manager;

    CoolingSystem coolingSystem;
    WarningSystem warningSystem;
    EngineControlUnit engineControlUnit;
    DashBoardDisplay dashBoardDisplay;

    manager.addObserver(&coolingSystem);
    manager.addObserver(&warningSystem);
    manager.addObserver(&engineControlUnit);
    manager.addObserver(&dashBoardDisplay);

    cout << "\n--- Setting engine state: Speed = 1500 RPM, Temperature = 70 C ---\n";
    manager.setEngineState(1500, 70);

    cout << "\n--- Setting engine state: Speed = 4000 RPM, Temperature = 85 C ---\n";
    manager.setEngineState(4000, 85);

    cout << "\n--- Setting engine state: Speed = 6500 RPM, Temperature = 110 C ---\n";
    manager.setEngineState(6500, 110);

    cout << "\n--- Setting engine state: Speed = 2000 RPM, Temperature = 75 C ---\n";
    manager.setEngineState(2000, 75);

    // Hiển thị trạng thái động cơ
    cout << "\n--- Current Engine State ---\n";
    manager.getState();

    return 0;
}