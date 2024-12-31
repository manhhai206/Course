
# Design Patterns

Design Patterns là các giải pháp tổng quát cho các vấn đề phổ biến trong phát triển phần mềm. Chúng là một dạng "công thức" giúp các lập trình viên xử lý các tình huống thường gặp trong quá trình thiết kế.

Design Patterns được chua thành các loại sau:
- Creational Patterns (Mẫu khởi tạo): Quản lý việc khởi tạo đối tượng (VD: Singleton, Factory).
- Structural Patterns (Mẫu cấu trúc): Tổ chức cấu trúc của các lớp và đối tượng (VD: Decorator)
- Behavoiral Patterns (Mẫu hành vi): Xác định cách các đối tượng tương tác với nhau(VD: Obersever, MVP)

# Singleton Patterns
Singleton là một mẫu thiết kế thuộc nhóm Creational, nó đảm bảo rằng một lớp chỉ có một đối tượng duy nhất được tạo ra, và cung cấp một phương thức để truy cập đến đối tượng đó từ bất kỳ đâu trong chương trình.

Các thành phần chính của Singleton:
- Private Constructor: Đảm bảo rằng không ai có thể khởi tạo đối tượng từ bên ngoài lớp.
- Static Instance: Đây là đối tượng tĩnh duy nhất của lớp đó. Không thể tạo ra nhiều hơn một đối tượng của lớp Singleton.
- Static Method: Phương thức để truy cập đến đối tượng Singleton duy nhất từ mọi nơi trong chương trình.

```c
class UART
{
    private:
        /********************************************
         * Con trỏ static duy nhất của lớp UART
         * Khai báo static property thì tất cả các object 
         *      đều được sử dụng chung biến static này
         * Phải cấp phát địa trỉ cho nó mới sử dụng được.
         ******************************************* */
        static UART* intance;
```
- Con trỏ này lưu trữ địa chỉ của đối tượng UART duy nhất và đảm bảo rằng đối tượng này chỉ được tạo ra một lần duy nhất.
- Khi bạn gọi UART::getInstance(), con trỏ static sẽ được kiểm tra, và nếu nó chưa được cấp phát, đối tượng sẽ được tạo ra. Điều này giúp duy trì tính duy nhất của đối tượng trong toàn bộ chương trình.

```c
        UART()
        {
            initUART();
        }

        void initUART()
        {
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

            USART_InitTypeDef UART_InitStruct;
            UART_InitStruct.USART_BaudRate = 9600;
            UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
            UART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
            UART_InitStruct.USART_Parity = USART_Parity_No;
            UART_InitStruct.USART_StopBits = USART_StopBits_1;
            UART_InitStruct.USART_WordLength = USART_WordLength_8b;

            USART_Init(USART1, &UART_InitStruct);
            USART_Cmd(USART1, ENABLE);
        }
```       
- UART() được khai báo là private để ngăn ngừa việc khởi tạo đối tượng từ bên ngoài lớp UART.
- Không có cách nào khác ngoài việc gọi getInstance() để tạo ra đối tượng UART. Đây là điểm quan trọng của mẫu thiết kế Singleton, giúp đảm bảo chỉ có một đối tượng UART duy nhất trong suốt vòng đời của chương trình.

```c
UART* UART::instance = nullptr;
```
- Cấp phát địa chỉ cho con trỏ static instance và khởi tạo nó với giá trị nullptr. Điều này đảm bảo rằng khi gọi lần đầu tiên vào getInstance(), con trỏ này sẽ có giá trị nullptr, và đối tượng sẽ được cấp phát bộ nhớ.

```c
        /*******************************************
         * Static method: có thể truy cập bất kì đâu trong chương trình.
         * Chỉ thao tác với mỗi static property.
         * Nằm ở vị trí public.
         * Dùng để khởi tạo đối tượng duy nhất
         ****************************************** */
        static UART* getIntance()
        {
            if(intance == nullptr)
            {
                /* Khởi tạo 1 đối tượng mới thông qua cấp phát động */
                intance = new UART();
            }
            return intance;
        }
```
Method này cung cấp cơ chế để truy cập đối tượng Singleton duy nhất từ bất kỳ đâu trong chương trình.
- Lần đầu gọi getInstance(), nếu instance là nullptr, nó sẽ cấp phát bộ nhớ cho đối tượng UART bằng **new** UART().
- Sau đó, khi gọi phương thức này  các lần tiếp theo, nó sẽ chỉ trả về con trỏ instance mà không cần phải cấp phát lại bộ nhớ, đảm bảo rằng chỉ có một đối tượng duy nhất tồn tại.

# MVP Patterns
MVP (Model - View - Presenter) là một mẫu thiết kế thuộc nhóm Behavioral, phổ biến trong lập trình giao diện người dùng (UI) và phát triển ứng dụng. MVP tách biệt các thành phần của ứng dụng thành ba phần chính: Model, View, và Presenter. Cấu trúc này giúp dễ dàng quản lý, kiểm thử, và bảo trì mã nguồn.
- Model: Chứa logic liên quan đến dữ liệu của ứng dụng, bao gồm các đối tượng, cơ sở dữ liệu, và giao tiếp với các API khác.
- View: Hiển thị giao diện (Interface) và nhận tương tác từ người dùng (như nhập liệu, bấm nút). 
- Presenter: Là cầu nối giữa Model và View, chịu trách nhiệm xử lý logic, điều phối dữ liệu từ Model đến View và ngược lại.biết

Đặc điểm của MVP Patterns:
- Tách biệt logic và giao diện: Presenter chứa logic của ứng dụng , giúp View chỉ tập trung vào hiển thị.
- Presenter không biêt đến giao diện cụ thể:  Presenter chỉ tương tác với View thông qua một interface, giúp việc kiểm thử và thay đổi giao diện trở nên dễ dàng.
- Thích hợp cho ứng dụng có giao diện phức tạp: MVP rất hữu ích khi giao diện cần tương tác với nhiều dữ liệu và các thành phần phức tạp.

Ví dụ:
```c
class SinhVienModel{
    private:
        string name;
        int age;
        string studentId;

    public:
        SinhVienModel(const string& name, int age, const string& studentId): name(name), age(age), studentId(studentId){}

        // setter method
        void setName(const string& newName){
            name = newName;
        }

        void setAge(int newAge){
            age = newAge;
        }

        void setStudentId(const string& newStudentId){
            studentId = newStudentId;
        }

        // getter method
        string getName() const{
            return name;
        }

        int getAge() const{
            return age;
        }

        string getStudentId() const{
            return studentId;
        }
};
```
- Model: Lưu trữ dữ liệu và xử lý logic liên quan đến dữ liệu. Lớp SinhVienModel lưu trữ thông tin sinh viên như tên, tuổi và mã số sinh viên.

```c
class SinhVienView{
    public:
        void displayStudentInfo(const string& name, int age, const string& studentId){
            cout << "Thong tin sinh vien:" << endl;
            cout << "Ten: " << name << endl;
            cout << "Tuoi: " << age << endl;
            cout << "Ma so sinh vien: " << studentId << endl;
        }

        void inputStudentInfo(string& name, int& age, string& studentId){
            cout << "Nhap thong tin sinh vien:" << endl;

            cout << "Ten: ";
            getline(cin, name);

            cout << "Tuoi: ";
            cin >> age;
            cin.ignore();  // Bo qua ky tu newline trong buffer

            cout << "Ma so sinh vien: ";
            getline(cin, studentId);
        }
};
```
- View: Chịu trách nhiệm hiển thị dữ liệu cho người dùng và nhận đầu vào từ người dùng. Lớp SinhVienView hiển thị hoặc yêu cầu thông tin sinh viên.

```c
class SinhVienPresenter{
    private:
        SinhVienModel& model;
        SinhVienView&  view;

    public:
        SinhVienPresenter(SinhVienModel& m, SinhVienView& v): model(m), view(v){}

        void updateStudentInfo(){
            string name;
            int age;
            string studentId;
           
            view.inputStudentInfo(name, age, studentId);
            model.setName(name);
            model.setAge(age);
            model.setStudentId(studentId);
        }

        void showStudentInfo(){
            view.displayStudentInfo(model.getName(), model.getAge(), model.getStudentId());
        }
};
```
- Presenter: Là cầu nối giữa Model và View. Nó xử lý logic ứng dụng và cập nhật dữ liệu từ View đến Model, hoặc lấy dữ liệu từ Model để hiển thị trên View.
- updateStudentInfo: Thu thập thông tin từ View và cập nhật vào Model.
- showStudentInfo: Lấy thông tin từ Model và hiển thị qua View.

**Luồng hoạt động của MVP Patterns**

1. Người dùng tương tác với giao diện người dùng (View)
2. View chuyển sự kiện này cho Presenter
3. Presenter xử lý yêu cầu bằng cahcs lấy dữ liệu từ Model.
4. Model xử lý dữ liệu và trả về kết quả cho Presenter
5. Presenter tiếp tục cập nhật View với dữ liệu đã xử lý ở model

# Observer
Observer là một mẫu thiết kế thuộc nhóm Behavioral (mẫu hành vi), nó định nghĩa một mối quan hệ phụ thuộc one-to-many giữa các đối tượng, nghĩa là khi một đối tượng thay đổi trạng thái (Subject), tất cả các đối tượng phụ thuộc (Observers) vào nó sẽ được tự động thông báo và cập nhật.

Các thành phần chính:

**Subject**:  Đối tượng giữ trạng thái và chịu trách nhiệm thông báo cho các Observer về sự thay đổi.
- registerObserver(Observer* observer): Đăng ký một Observer vào danh sách.
- removeObserver(Observer* observer): Gỡ bỏ một Observer khỏi danh sách.
- notifyObservers(): Thông báo tất cả các Observer về sự thay đổi của trạng thái
```c
class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};
```

**Observer** Được thông báo khi có sự thay đổi từ Subject. Nó thực hiện hành động dựa trên thông báo này.
```c
class Observer {
public:
    virtual void update(float throttle, float speed) = 0;
    virtual ~Observer() = default;
};
```
**Concrete Observer** : Là các lớp kế thừa từ lớp Observer và triển khai phương thức update().
- Các lớp như DashBoardDisplay, EngineController, và ABSController là các Concrete Observer. 
- Mỗi lớp này thực hiện phương thức update() để xử lý thông tin từ Subject (SensorDataManager) và thực hiện hành động cụ thể như hiển thị thông tin, điều chỉnh công suất động cơ, hoặc giám sát hệ thống ABS.
```c
// Concrete Observer: DashBoardDisplay
class DashBoardDisplay : public Observer
{
public:
    void update(float throttle, float speed) override
    {
        cout << "Dashboard: Current speed = " << speed << " km/h, Throttle = " << throttle << "%" << endl;
    }
};

// Concrete Observer: EngineController
class EngineController : public Observer
{
public:
    void update(float throttle, float speed) override
    {
        cout << "Engine Controller: Adjusting engine power based on throttle = " << throttle << "%" << endl;
    }
};

// Concrete Observer: ABSController
class ABSController : public Observer
{
public:
    void update(float throttle, float speed) override
    {
        if (speed > 100) {
            cout << "ABS Controller: Speed is high (" << speed << " km/h), monitoring for possible skidding." << endl;
        } else {
            cout << "ABS Controller: Speed is safe." << endl;
        }
    }
};
```

**Concrete Subject**: Là lớp kế thừa từ lớp Subject và triển khai cụ thể các phương thức để quản lý danh sách các Observer và quản lý trạng thái của Subject.
- Cung cấp các phương thức như registerObserver(), removeObserver(), và notifyObservers() để đăng ký, gỡ bỏ, và thông báo các Observer khi trạng thái của Subject thay đổi.
```c
class SensorDataManager : public Subject
{
private:
    float throttle;  // Cảm biến bàn đạp ga
    float speed;     // Cảm biến tốc độ
    vector<Observer*> observers;  // Danh sách các Observer

public:
    void registerObserver(Observer* observer)
    {
        observers.push_back(observer);  // Thêm Observer vào danh sách
    }

    void removeObserver(Observer* observer)
    {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());  // Xóa Observer khỏi danh sách
    }

    void notifyObservers()
    {
        for (auto observer : observers)  // Duyệt qua danh sách và gọi phương thức update()
        {
            observer->update(throttle, speed);
        }
    }

    // Cập nhật dữ liệu cảm biến và thông báo cho Observer
    void setSensorData(float throttleValue, float speedValue)
    {
        throttle = throttleValue;
        speed = speedValue;
        notifyObservers();  // Thông báo cho tất cả Observer về sự thay đổi
    }
};
```
Đặc điểm chính của Observer Pattern:
- Mối quan hệ giữa Subject và Observer: Subject giữ một danh sách các Observer. Các Observer đăng ký nhận thông báo từ Subject khi có sự thay đổi trạng thái. Observer có thể thêm, xóa hoặc cập nhật trong danh sách này.
- Tự động thông báo (Push Notification): Khi trạng thái của Subject thay đổi, nó sẽ tự động thông báo cho tất cả các Observer đã đăng ký. Các Observer không cần chủ động kiểm tra trạng thái của Subject mà sẽ nhận thông báo ngay khi có thay đổi.
- Tính linh hoạt và mở rộng: Observer Pattern cho phép dễ dàng thêm hoặc xóa các Observer mà không cần thay đổi Subject hoặc Observer có thể dễ dàng ngừng nhận thông báo từ Subject bằng cách hủy đăng ký, giúp kiểm soát tốt hơn việc quản lý tài nguyên và sự kiện trong hệ thống.
- Nhiều Observer có thể theo dõi một hoặc nhiều Subject: Nhiều Observer có thể cùng theo dõi một Subject. Điều này cho phép cùng một sự kiện trong Subject có thể ảnh hưởng đến nhiều đối tượng khác nhau. Một Observer có thể đăng ký để nhận thông báo từ nhiều Subject khác nhau, và mỗi Subject sẽ thông báo cho Observer khi có sự thay đổi liên quan.

# Decorator Pattern
