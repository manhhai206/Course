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

        addUser(head, user);
    }

    fclose(file);
}

