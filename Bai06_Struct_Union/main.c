#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ID_SIZE 2
#define DATA_SIZE 4
#define CHECKSUM_SIZE 2
#define FRAME_SIZE (ID_SIZE + DATA_SIZE + CHECKSUM_SIZE)

typedef union {
    struct {
        uint8_t id[ID_SIZE];        
        uint8_t data[DATA_SIZE];  
        uint8_t check_sum[CHECKSUM_SIZE];
    } data;

    uint8_t frame[FRAME_SIZE];     
} Data_Frame;

int main() {
    Data_Frame transmitter_data;  
    Data_Frame receiver_data;     

    memcpy(transmitter_data.data.id, "01", ID_SIZE);
    memcpy(transmitter_data.data.data, "1234", DATA_SIZE);
    memcpy(transmitter_data.data.check_sum, "70", CHECKSUM_SIZE);

    memcpy(receiver_data.frame, transmitter_data.frame, FRAME_SIZE);

    printf("Transmitter Data Frame:\n");
    for (int i = 0; i < FRAME_SIZE; i++) {
        printf("Byte %d: %x\n", i, transmitter_data.frame[i]);
    }

    printf("\nReceiver Data Frame:\n");
    for (int i = 0; i < FRAME_SIZE; i++) {
        printf("Byte %d: %x\n", i, receiver_data.frame[i]);
    }

    if (memcmp(transmitter_data.frame, receiver_data.frame, FRAME_SIZE) == 0) {
        printf("\nData successfully copied from transmitter to receiver.\n");
    } else {
        printf("\nData mismatch between transmitter and receiver.\n");
    }

    return 0;
}
