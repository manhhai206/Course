#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <stdarg.h>

typedef enum {
    LIGHT,              // ON/OFF 
    AIR_CONDITIONER,    // ON/OFF + SET_TEMPERATURE + SET_MODE
    FINGERPRINT_LOCK,   // UNLOCK/LOCK
    MUSIC_PLAYER        // ON/OFF + INCREASE_VOLUME/DECREASE_VOLUME + CHANGE_TRACK
} DeviceType;

typedef enum {
    ON,
    OFF,
    SET_TEMPERATURE,
    SET_MODE,
    UNLOCK,
    LOCK,
    INCREASE_VOLUME,
    DECREASE_VOLUME,
    CHANGE_TRACK
} CommandType;

void controlDevice(DeviceType device, ...)
{
    va_list args;
    va_start(args, device);
    CommandType command = va_arg(args, CommandType);

    switch (device) {
        case LIGHT:
            switch (command) {
                case ON:
                    printf("Light is turned ON.\n");
                    break;
                case OFF:
                    printf("Light is turned OFF.\n");
                    break;
                default:
                    printf("The input information for LIGHT is invalid.\n");
                    break;
            }
            break;

        case AIR_CONDITIONER:
            switch (command) {
                case ON:
                    {
                        CommandType more_command = va_arg(args, CommandType);
                        switch (more_command) {
                            case SET_TEMPERATURE:
                                {
                                    float temperature = va_arg(args, double);
                                    printf("Air Conditioner is turned ON and temperature is set to %.2f degrees.\n", temperature);
                                }
                                break;
                            case SET_MODE:
                                {
                                    char* mode = va_arg(args, char*);
                                    printf("Air Conditioner is turned ON and mode is set to %s.\n", mode);
                                }
                                break;
                            default:
                                printf("Invalid command for AIR_CONDITIONER while ON.\n");
                                break;
                        }
                    }
                    break;
                case OFF:
                    printf("Air Conditioner is turned OFF.\n");
                    break;
                default:
                    printf("The input information for AIR_CONDITIONER is invalid.\n");
                    break;
            }
            break;

        case FINGERPRINT_LOCK:
            switch (command) {
                case LOCK:
                    printf("Fingerprint lock is LOCKED.\n");
                    break;
                case UNLOCK:
                    printf("Fingerprint lock is UNLOCKED.\n");
                    break;
                default:
                    printf("The input information for FINGERPRINT_LOCK is invalid.\n");
                    break;
            }
            break;

        case MUSIC_PLAYER:
            switch (command) {
                case ON:
                    {
                        CommandType more_command = va_arg(args, CommandType);
                        switch (more_command) {
                            case INCREASE_VOLUME:
                                {
                                    int volume = va_arg(args, int);
                                    printf("Music player is turned ON and volume is increased by %d.\n", volume);
                                }
                                break;
                            case DECREASE_VOLUME:
                                {
                                    int volume = va_arg(args, int);
                                    printf("Music player is turned ON and volume is decreased by %d.\n", volume);
                                }
                                break;
                            case CHANGE_TRACK:
                                {
                                    char* new_track = va_arg(args, char*);
                                    printf("Music player is turned ON and track is changed to %s.\n", new_track);                        
                                }
                                break;
                            default:
                                printf("Invalid command for MUSIC_PLAYER while ON.\n");
                                break;
                        }
                    }
                    break;
                case OFF:
                    printf("Music player is turned OFF.\n");
                    break;
                default:
                    printf("The input information for MUSIC_PLAYER is invalid.\n");
                    break;
            }
            break;

        default:
            printf("The input information is invalid. Please re-enter.\n"); 
            break;
    }

    va_end(args);
}

#endif
