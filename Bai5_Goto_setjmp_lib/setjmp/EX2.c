#include <stdio.h>
#include <setjmp.h>

enum ErrorCodes { NO_ERROR, FILE_ERROR, NETWORK_ERROR, CALCULATION_ERROR };
enum ErrorCodes error_code;

char *error_message = NULL;
jmp_buf buf;

#define TRY if ((result = setjmp(buf)) == NO_ERROR)
#define CATCH(x) else if(result == x)
#define THROW(code, msg) error_code = code; \
                         error_message = msg; \
                         longjmp(buf, code)
#define failed 1

void readFile(int checkfail)
{
    printf("Reading File.....\n");
    if(checkfail == failed)
    {
        THROW(FILE_ERROR, "Failed to read file!");\
    } else {
        printf("Reading File.....\n");
    }
    
}

void networkOperation(int checkfail)
{
    printf("Connecting...\n");
    if(checkfail == failed)
    {
        THROW(NETWORK_ERROR, "Failed to connect to the network!");
    } else {
        printf("Connecting...\n");
    }
}

void calculateData(int checkfail)
{
    printf("Calculating....\n");
    if(checkfail == failed)
    {
        THROW(CALCULATION_ERROR, "Failed to calculate data.");
    } else {
        printf("Calculating....\n");
    }
}

int main()
{
    int result;
    TRY {
        readFile(0);
        networkOperation(failed);
        calculateData(0);
    }
    CATCH(FILE_ERROR) {
        printf("%s\n", error_message);
    }
    CATCH(NETWORK_ERROR) {
        printf("%s\n", error_message);
    }
    CATCH(CALCULATION_ERROR) {
        printf("%s\n", error_message);
    }

    printf("End Program \n");
    return 0; 
}
