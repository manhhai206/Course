#include <stdio.h>
#include <stdarg.h>
#include "controller.h"

int main() {
    controlDevice(LIGHT,OFF); 
    controlDevice(AIR_CONDITIONER, ON, SET_TEMPERATURE, 19.0);
    controlDevice(FINGERPRINT_LOCK, LOCK); 
    controlDevice(MUSIC_PLAYER, ON, CHANGE_TRACK,"Price tag");
    return 0;
}