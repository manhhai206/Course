#include "motor.h"
#include <stdio.h>

void control_motor(int value_sensor){
    if(value_sensor > 30){
        printf("Motor ON\n");
    }
    else {
        printf("Motor OFF\n");
    }
}