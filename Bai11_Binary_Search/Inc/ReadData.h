#ifndef _READDATA_H
#define _READDATA_H
#include "User.h"

void readCSV(const char* filename, Node** head);
void addToCSV(const char* filename, User user);
void addUser(const char* filename,User user);
#endif
