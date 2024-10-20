#include <stdio.h>
#include <setjmp.h>

enum ErrorCodes { NO_ERROR, FILE_ERROR, NETWORK_ERROR, CALCULATION_ERROR };
enum ErrorCodes error_code;

char *error_message = NULL;
jmp_buf buf;

#define TRY if ((result = setjmp(buf)) == NO_ERROR)
#define CATCH(x) else if(result == x)
#define THROW(code, msg) do { error_code = code; error_message = msg; longjmp(buf, code); } while(0)

void readFile()
{
    printf("Reading File.....\n");
    THROW(FILE_ERROR, "Failed to read file!\n");
}

void networkOperation()
{
    printf("Connecting...\n");
    THROW(NETWORK_ERROR, "Failed to connect to the network!\n");
}

void calculateData()
{
    printf("Calculating....\n");
    THROW(CALCULATION_ERROR, "Failed to calculate data.\n");
}

int main()
{
    int result;
    TRY {
        readFile();
        networkOperation();
        calculateData();
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
