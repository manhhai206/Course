#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdbool.h"
#include "ctype.h"

typedef enum {
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JSON_Type;

typedef struct JSON_Value {
    JSON_Type type;
    union {
        int boolean;
        double number;
        char *string;
        struct {
            struct JSON_Value *values;
            size_t count;
        } array;
        struct {
            char **keys;
            struct JSON_Value *values;
            size_t count;
        } object;
    } value;
} JSON_Value;

int main() {

    JSON_Value *json_value = (JSON_Value*)malloc(sizeof(JSON_Value));
    json_value->type = JSON_OBJECT;
    json_value->value.object.count = 5;

    json_value->value.object.keys = (char **)malloc(json_value->value.object.count * sizeof(char *));
    json_value->value.object.values = (JSON_Value *)malloc(json_value->value.object.count * sizeof(JSON_Value));

    json_value->value.object.keys[0] = strdup("name");
    json_value->value.object.values[0].type = JSON_STRING;
    json_value->value.object.values[0].value.string = strdup("Hai");

    json_value->value.object.keys[1] = strdup("age");
    json_value->value.object.values[1].type = JSON_NUMBER;
    json_value->value.object.values[1].value.number = 22;

    json_value->value.object.keys[2] = strdup("city");
    json_value->value.object.values[2].type = JSON_STRING;
    json_value->value.object.values[2].value.string = strdup("HCMCity");

    json_value->value.object.keys[3] = strdup("isStudent");
    json_value->value.object.values[3].type = JSON_BOOLEAN;
    json_value->value.object.values[3].value.boolean = true;

    json_value->value.object.keys[4] = strdup("grades");
    json_value->value.object.values[4].type = JSON_ARRAY;
    json_value->value.object.values[4].value.array.count = 3;
    json_value->value.object.values[4].value.array.values = (JSON_Value *)malloc(3 * sizeof(JSON_Value));

    json_value->value.object.values[4].value.array.values[0].type = JSON_NUMBER;
    json_value->value.object.values[4].value.array.values[0].value.number = 12;

    json_value->value.object.values[4].value.array.values[1].type = JSON_NUMBER;
    json_value->value.object.values[4].value.array.values[1].value.number = 11;

    json_value->value.object.values[4].value.array.values[2].type = JSON_NUMBER;
    json_value->value.object.values[4].value.array.values[2].value.number = 10;

    free(json_value->value.object.keys);
    free(json_value->value.object.values);
    free(json_value);

    return 0;
}
