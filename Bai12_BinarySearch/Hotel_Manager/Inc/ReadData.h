#ifndef _READDATA_H
#define _READDATA_H

#include "User.h"

// Đọc dữ liệu từ file CSV và thêm vào cây nhị phân
void readCSV(const char* filename, Node** head, int (*cmp)(User, User));

// Ghi dữ liệu của người dùng vào file CSV
void addToCSV(const char* filename, User user);

// Thêm người dùng mới vào hệ thống
void addUser(const char* filename, User newUser);

#endif
