#include <stdio.h>
#include <stdlib.h>

#define FILE_CREATE_FAILED -1

#define DataBate_Path "..\\BINARY_SEARCH\\DataBase.csv"

int main()
{   
    /* Mở file ở chế độ ghi */
    FILE *file = fopen(DataBate_Path, "w");

    if (file == NULL) {
        printf("Cannot open file for writing\n");
        return FILE_CREATE_FAILED;
    }

    /* Ghi dòng tiêu đề vào file CSV */
    fprintf(file, "Name,Age,Address,Phone-Number\n");

    /* Ghi các thông tin vào file CSV */
    fprintf(file, "Hai,20,Binh Duong,023-476\n");
    fprintf(file, "Nam,21,Thu Duc,067-444\n");
    fprintf(file, "Ne,22,Dong Nai,033-630\n");
    fprintf(file, "An,23,Vung Tau,013-006\n");

    /* Đóng file CSV */
    fclose(file);
    printf("File written successfully.\n");

    /* Mở file ở chế độ đọc */
    file = fopen(DataBate_Path, "r");

    if (file == NULL) {
        printf("Cannot open file for reading\n");
        return FILE_CREATE_FAILED;
    }

    char line[100]; /* Bộ nhớ đệm dùng để lưu trữ dòng CSV */

    /* Bỏ qua dòng tiêu đề */
    fgets(line, sizeof(line), file); // "Name,Age,Address,Phone-Number"

    /* In ra tiêu đề */
    printf("%-20s %-5s %-20s %-15s\n", "Name", "Age", "Address", "Phone Number");

    /* Đọc từng dòng dữ liệu từ file CSV */
    while (fgets(line, sizeof(line), file)) {
        char name[20], address[20], phone[15];
        int age;

        /* Tách dữ liệu từ dòng CSV và in ra */
        sscanf(line, "%[^,],%d,%[^,],%s", name, &age, address, phone);
        printf("%-20s %-5d %-20s %-15s\n", name, age, address, phone);
    }

    /* Đóng file CSV */
    fclose(file);

    return 0;
}
