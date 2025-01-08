#include "ReadData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************************************************************
 * @brief Đọc dữ liệu từ file CSV và thêm vào cây nhị phân
 * @details Hàm này mở file CSV và đọc từng dòng dữ liệu. Các trường thông tin 
 *          của mỗi người dùng sẽ được tách ra từ từng dòng, bao gồm: tên, tuổi, 
 *          địa chỉ và số điện thoại. Sau đó, dữ liệu sẽ được thêm vào danh sách 
 *          liên kết.
 * @param[in] filename Đường dẫn tới file CSV cần đọc.
 * @param[in] head Con trỏ tới đầu danh sách liên kết, nơi lưu trữ dữ liệu người dùng.
 * @param[in] int (*cmp)(User, User) Con trỏ hàm dùng để truyền hàm cần thao tác
 *               Thao tác tìm kiếm theo tên: Call function Seach Name
 *               Thao tác tìm kiếm theo tên: Call function Seach Phone-Number
 ************************************************************************************ */
void readCSV(const char* filename, Node** head, int (*cmp)(User, User)) 
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file\n");
        return;
    }   

    char line[200];
    fgets(line, sizeof(line), file); // Bỏ qua dòng đầu tiên

    while (fgets(line, sizeof(line), file)) 
    {
        User user;
        char* token = strtok(line, ",");
        
        user.name = strdup(token);
        
        token = strtok(NULL, ",");
        user.age = atoi(token);

        token = strtok(NULL, ",");
        user.addr = strdup(token);

        token = strtok(NULL, ",");
        token[strcspn(token, "\n")] = '\0';  
        user.phone_number = strdup(token);

        *head = AddNode(*head, user, cmp); // Thêm vào cây nhị phân
    }

    fclose(file);
}

/**************************************************************************************
 * @brief Ghi dữ liệu của người dùng vào file CSV
 * @details Hàm này mở file CSV và ghi thông tin của người dùng vào cuối file. 
 *          Dữ liệu được ghi theo định dạng: tên, tuổi, địa chỉ và số điện thoại.
 * @param[in] filename Đường dẫn tới file CSV cần ghi.
 * @param[in] user Thông tin người dùng cần ghi vào file.
 ************************************************************************************ */
void addToCSV(const char* filename, User user) 
{
    FILE* file = fopen(filename, "a");
    fprintf(file, "%s,%d,%s,%s\n", user.name, user.age, user.addr, user.phone_number);
    fclose(file);
}


/**************************************************************************************
 * @brief Thêm người dùng mới vào hệ thống và lưu vào file CSV
 * @details Hàm này yêu cầu người dùng nhập thông tin, bao gồm tên, tuổi, địa chỉ và 
 *          số điện thoại. Sau đó, thông tin người dùng sẽ được lưu vào file CSV.
 *          Hàm cũng cấp phát bộ nhớ cho các trường dữ liệu và giải phóng bộ nhớ khi
 *          việc thêm người dùng hoàn tất.
 * @param[in] filename Đường dẫn tới file CSV để lưu thông tin người dùng mới.
 * @param[in] newUser Thông tin người dùng mới.
 ************************************************************************************ */
void addUser(const char* filename, User newUser) 
{
    newUser.name = (char*)malloc(10 * sizeof(char));
    newUser.addr = (char*)malloc(100 * sizeof(char));
    newUser.phone_number = (char*)malloc(15 * sizeof(char));

    printf("Enter name: ");
    fgets(newUser.name, 10, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0';

    printf("Enter age: ");
    scanf("%d", &newUser.age);
    getchar(); 

    printf("Enter address: ");
    fgets(newUser.addr, 100, stdin);
    newUser.addr[strcspn(newUser.addr, "\n")] = '\0';

    printf("Enter phone number: ");
    fgets(newUser.phone_number, 15, stdin);
    newUser.phone_number[strcspn(newUser.phone_number, "\n")] = '\0';

    addToCSV(filename, newUser);

    free(newUser.name);
    free(newUser.addr);
    free(newUser.phone_number);

    printf("New user added successfully.\n");
}

