// #include <iostream>
// #include "stm32f10x.h"


// // đặc điểm: Singleton
// // 1.Private Contructor : Đảm bảo rằng không có 1 ai có thể khởi tại ở bên ngoài lớp.
// // 2.Static Intance: con trỏ tĩnh duy nhất dùng để quản lý đối tượng duy nhất được tạo ra.
// // 3.Static Method:  cung cấp cơ chế tạo ra đối tượng duy nhất.

// class UART
// {
//     private:
//         /********************************************
//          * Con trỏ static duy nhất của lớp UART
//          * Khai báo static property thì tất cả các object 
//          *      đều được sử dụng chung biến static này
//          * Phải cấp phát địa trỉ cho nó mới sử dụng được.
//          ******************************************* */
//         static UART* intance;
//         /* Tự động khởi tạo initUART */
//         UART()
//         {
//             initUART();
//         }

//         void initUART()
//         {
//             RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

//             USART_InitTypeDef UART_InitStruct;
//             UART_InitStruct.USART_BaudRate = 9600;
//             UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//             UART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//             UART_InitStruct.USART_Parity = USART_Parity_No;
//             UART_InitStruct.USART_StopBits = USART_StopBits_1;
//             UART_InitStruct.USART_WordLength = USART_WordLength_8b;

//             USART_Init(USART1, &UART_InitStruct);
//             USART_Cmd(USART1, ENABLE);
//         }

//     public:
//         /*******************************************
//          * Static method: có thể truy cập bất kì đâu trong chương trình.
//          * Chỉ thao tác với mỗi static property.
//          * Nằm ở vị trí public.
//          * Dùng để khởi tạo đối tượng duy nhất
//          ****************************************** */
//         static UART* getIntance()
//         {
//             if(intance == nullptr)
//             {
//                 /* Khởi tạo 1 đối tượng mới thông qua cấp phát động */
//                 intance = new UART();
//             }
//             return intance;
//         }   

//             // Hàm gửi dữ liệu qua UART
//         void sendData(uint8_t data) {
//             while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // Chờ UART sẵn sàng
//             USART_SendData(USART1, data); // Gửi dữ liệu
//         }       

//         // Hàm nhận dữ liệu qua UART
//         uint8_t receiveData() {
//             while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET); // Chờ dữ liệu đến
//             return USART_ReceiveData(USART1); // Nhận dữ liệu
//         }       
// }

// UART* UART::instance = nullptr;

// int main()
// {
//     UART* uart = UART::getInstance();

//     // Gửi một ký tự qua UART
//     uart->sendData('H');

//     // Nhận một ký tự từ UART
//     uint8_t received = uart->receiveData();

//     while (1) {
//         // Thực hiện công việc liên quan khác
//     }
// }


#include <iostream>
#include <string>

using namespace std;

class Singleton {
private:
    static Singleton* instance;
    string message; 

    Singleton() {
        cout << "Singleton Initialized" << endl;
        message = "Default message";  
    }

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    void setMessage(const string& newMessage) {
        message = newMessage;
    }

    void displayMessage() const {
        cout << "Message: " << message << endl;
    }
};

Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* singleton = Singleton::getInstance();

    // Hiển thị thông điệp mặc định
    singleton->displayMessage();

    Singleton* singleton2 = Singleton::getInstance();
    // Thay đổi thông điệp
    singleton2->setMessage("New Message");
    
    // Hiển thị thông điệp đã thay đổi
    singleton2->displayMessage();

    return 0;
}

