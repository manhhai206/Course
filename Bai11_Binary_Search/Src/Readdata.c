#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "User.h"

void readCSV(const char* filename, Node** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file\n");
        return;
    }
    printf("Open file\n");
    char line[100];

    fgets(line, sizeof(line), file); 

    while (fgets(line, sizeof(line), file)) {
        User user;

        char* token = strtok(line, ",");
        if (token != NULL) {
            user.name = strdup(token);
        }


        token = strtok(NULL, ",");
        if (token != NULL) {
            user.age = atoi(token);
        }


        token = strtok(NULL, ",");
        if (token != NULL) {
            user.addr = strdup(token);
        }


        token = strtok(NULL, ",");
        if (token != NULL) {
            token[strcspn(token, "\n")] = '\0';  
            user.phone_number = strdup(token);
        } else {
            user.phone_number = strdup("");
        }

        addNode(head, user);
    }

    fclose(file);
}

void appendUserToCSV(const char* filename, User user) {
    FILE* file = fopen(filename, "a"); 

    fprintf(file, "%s,%d,%s,%s\n", user.name, user.age, user.addr, user.phone_number);

    fclose(file);
}

void addUser(const char* filename,User newUser){
        newUser.name = (char*)malloc(10 * sizeof(char));
        newUser.addr = (char*)malloc(10 * sizeof(char));
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

        appendUserToCSV(filename, newUser);

        free(newUser.name);
        free(newUser.addr);
        free(newUser.phone_number);

        printf("New user added successfully.\n");
}