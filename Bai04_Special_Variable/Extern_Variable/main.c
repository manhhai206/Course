#include <stdio.h>
#include "sensor.h"
#include "motor.h"

int main() {
    //Read sensor value
    read_sensor();
    
    //Print sensor value
    printf("Sensor value: %d\n",sensor_value);

    //  Control motor depend on the sensor value
    control_motor(sensor_value);

    return 0;
}
